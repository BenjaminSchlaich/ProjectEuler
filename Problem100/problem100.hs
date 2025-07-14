
isIntegral :: Double -> Bool
isIntegral x = x == fromIntegral (round x)

isSquare :: Integer -> Bool
isSquare n = n == (round (sqrt (fromIntegral n)))^2

intRoot
