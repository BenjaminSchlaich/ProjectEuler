
-- pretty naive prime check for odd numbers. (ONLY FOR ODD NUMBERS!)
prime :: Int -> Bool
prime n = null $ filter (\k -> n `mod` k == 0) [3, 5.. limit]
    where limit = ceiling $ sqrt $ fromIntegral n

-- all odd composite numbers
oddComposites :: [Int]
oddComposites = filter (not.prime) [9, 11..]

-- twiceSquares up to the limit l
twiceSquare :: Int -> [Int]
twiceSquare l = takeWhile (< l) [2*n^2 | n<-[1..]]

-- check whether goldbach's other conjecture holds for the given number n
conjectureHolds :: Int -> Bool
conjectureHolds n = (not.null) [ts | ts<-twiceSquare n, prime (n - ts)]

-- find the first element in a list where a given predicate applies, or return nothing if none exist
findFirst :: [a] -> (a -> Bool) -> Maybe a
findFirst [] _ = Nothing
findFirst (x:xs) p  | p x = Just x
                    | otherwise = findFirst xs p

-- find the first odd composite number where the conjecture doesn't hold
result = findFirst oddComposites (not.conjectureHolds)
