module Lib
    ( someFunc
    ) where

someFunc :: IO ()
someFunc = putStrLn $ sum $ map (strToInt.(:[])) $ show $ (2^1000)
