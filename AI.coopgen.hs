import Graphics.Rendering.Cairo
import Network.Wai.Handler.Warp
import System.FilePath.Posix
import Tasty.Images
import Text.Blaze.Html.Renderer.String (renderHtml)
import Text.Blaze.Html5 as H
import Text.Blaze.Html5.Attributes as A

data ArtSettings = ArtSettings {
  images :: [Image],
  width :: Int,
  height :: Int
}

data Slideshow = Slideshow [Image]

uploadImages :: [FilePath] -> IO (Maybe ArtSettings)
uploadImages paths = do
  maybeImages <- mapM readImage paths
  if all isJust maybeImages
    then do
      (width, height) <- imageDimensions $ head $ catMaybes maybeImages
      return $ Just ArtSettings (catMaybes maybeImages) width height
    else return Nothing

-- ... (rest of your functions here)

generateHtml :: Slideshow -> String
generateHtml (Slideshow images) = renderHtml $ do
  H.docTypeHtml $ do
    H.head $ do
      H.title "Generative Art"
    H.body $ do
      forM_ images $ \image -> do
        let src = "data:image/png;base64," ++ (encodeBase64 $ renderImage image)
        H.img ! A.src (H.toValue src)

main :: IO ()
main = do
  putStrLn "Welcome to Generative Art!"
  putStrLn "Upload your photos:"
  imagePaths <- lines <$> getContents
  maybeArtSettings <- uploadImages imagePaths
  case maybeArtSettings of
    Just artSettings -> do
      let images = [
            generateRandomArt artSettings,
            generateSpiralArt artSettings,
            generateKaleidoscopeArt artSettings,
            generateMandelbrotArt artSettings,
            generateCellularArt artSettings
          ]
      putStrLn $ generateHtml $ Slideshow images
    Nothing -> putStrLn "Invalid image files."

-- ... This version of the code reads multiple file paths from standard input (one per line), generates art from each image, and then outputs an HTML document with the generated images embedded as Base64-encoded data URLs. This should be more web-friendly and bandwidth-efficient than serving the images as separate files.
