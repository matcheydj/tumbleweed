-- Define the Morse code dictionary
morseCodeDict :: Map Char String
morseCodeDict = fromList [
  ('A', ".-"), ('B', "-..."), ('C', "-.-."),
  ('D', "-.."), ('E', "."), ('F', "..-.")
]

-- Define the Braille alphabet dictionary
brailleDict :: Map Char String
brailleDict = fromList [
  ('a', ".o"), ('b', "o."), ('c', "o.."),
  ('d', "o..o"), ('e', "o."), ('f', "o.o"),
  ('g', "--."), ('h', "...."), ('i', ".."),
  ('j', ".---"), ('k', "-.-"), ('l', ".-.."),
  ('m', "--"), ('n', "-."), ('o', "---"),
  ('p', ".--."), ('q', "--.-"), ('r', ".-."),
  ('s', "..."), ('t', "-"), ('u', "..-"),
  ('v', "...-"), ('w', ".--"), ('x', "-..-"),
  ('y', "-.--"), ('z', "--.."), (' ', ".")
]

-- Convert text to morse code
morseToText :: String -> String
morseToText text = concat [morseCodeDict ! c | c <- text]

-- Convert text to Braille
brailleToText :: String -> String
brailleToText text = concat [brailleDict ! c | c <- text]

-- Generate a random keyboard layout
generateRandomLayout :: Int -> String
generateRandomLayout size = take size (randomRIO ('a', 'z') ++ randomRIO ('A', 'Z') ++ randomRIO ('0', '9'))

-- Define conversion functions for different keyboard layouts
keyboardType :: String -> String -> String
keyboardType "Morse code" text = morseToText text
keyboardType "Braille" text = brailleToText text
keyboardType "Random" text = text
keyboardType _ text = text

-- Convert text to HTML table
convertToHtml :: String -> String -> String
convertToHtml text keyboardLayout =
  "<table><tr><th>Index</th><th>Character</th><th>Converted Text</th></tr>"
  ++ concat
    [ "<tr><td>" ++ show i ++ "</td><td>" ++ c ++ "</td><td>" ++ keyboardType keyboardLayout c ++ "</td></tr>"
      | (i, c) <- zip [1 ..] text
    ]
  ++ "</table>"

-- Test the function with different keyboard layouts
main :: IO ()
main = do
  let text = "Hello world!"
  forM_
    [ ("Morse code", morseToText text),
      ("Braille", brailleToText text),
      ("Random", generateRandomLayout 10),
      ("Keyboard", text)
    ]
    (\(layout, convertedText) -> putStrLn $ convertToHtml text layout)
