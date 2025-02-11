
s :: Int -> Int -> Int
s m n = ((m^2 + m) * (n^2 + n)) `div` 4

m1 :: Int -> Double
m1 n = sqrt (1 + (8*10^6)/(x^2 + x)) - 0.5
    where x = fromIntegral n :: Double

fmin :: [Int] -> Int
fmin = foldl min (maxBound :: Int)

solution :: (Int, Int)
solution = (\(a, b, v) -> (a, b)) $ argMin candidates
    where   candidates = map (\(m, n) -> (m, n, s m n)) [(round (m1 n) :: Int, n) | n<-[1..2000]]
            argMin = foldl (\(a, b, v1) (c, d, v2) -> if compare v1 v2 then (a, b, v1) else (c, d, v2)) (0, 0, maxBound :: Int)
            compare v1 v2 = abs (v1 - 2*10^6) < abs (v2 - 2*10^6)
