import Graphics.Rendering.Cairo
import Network.Wai.Handler.Warp
import System.FilePath.Posix
import Tasty.Images
import Text.Blaze.Html.Renderer.String (renderHtml)
import Text.Blaze.Html5 as H
import Text.Blaze.Html5.Attributes as A
import Data.List

data ArtSettings = ArtSettings {
  images :: [Image],
  width :: Int,
  height :: Int,
  randSeed :: Int,
  activeTechniques :: [String]
}

data Slideshow = Slideshow [Image]

data Technique = Randomness | Algorithm | Geometry | Fractal | CellularAutomata | Evolutionary | Mapping | Symmetry | Tiling

uploadImages :: [FilePath] -> IO (Maybe ArtSettings)
uploadImages paths = do
  maybeImages <- mapM readImage paths
  if all isJust maybeImages
    then do
      (width, height) <- imageDimensions $ head $ catMaybes maybeImages
      return $ Just ArtSettings (catMaybes maybeImages) width height 0 []
    else return Nothing

-- ... (rest of your functions here)

generateHtml :: Slideshow -> String
generateHtml (Slideshow images) = renderHtml $ do
  H.docTypeHtml $ do
    H.head $ do
      H.title "Interactive Generative Art"
      H.script $ H.toValue "function updateArt(technique) { ... }"
    H.body $ do
      H.div ! A.id "art-container" $ do
        forM_ images $ \image -> do
          let src = "data:image/png;base64," ++ (encodeBase64 $ renderImage image)
          H.img ! A.src (H.toValue src) ! A.id "image"
      H.div ! A.id "controls" $ do
        forM_ [Randomness, Algorithm, Geometry, Fractal, CellularAutomata, Evolutionary, Mapping, Symmetry, Tiling] $ \technique -> do
          H.button ! A.onClick (H.toValue $ "updateArt('" ++ show technique ++ "')") $ show technique

main :: IO ()
main = do
  putStrLn "Welcome to Interactive Generative Art!"
  putStrLn "Upload your photos:"
  imagePaths <- lines <$> getContents
  maybeArtSettings <- uploadImages imagePaths
  case maybeArtSettings of
    Just artSettings -> do
      let images = generateInteractiveArt artSettings
      putStrLn $ generateHtml $ Slideshow images
    Nothing -> putStrLn "Invalid image files."

generateInteractiveArt :: ArtSettings -> [Image]
generateInteractiveArt artSettings = do
  let activeTechniques = artSettings.activeTechniques
  mapM (\image -> applyTechniques image activeTechniques artSettings) artSettings.images
