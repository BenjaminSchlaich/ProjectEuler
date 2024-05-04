
firstWhere :: [a] -> (a -> Bool) -> Maybe a
firstWhere [] _ = Nothing
firstWhere l@(x:xs) p   | p x = Just x
                        | otherwise = firstWhere xs p

hex :: Integer -> Integer
hex i = i * (2*i - 1)

isTri :: Integer -> Bool
isTri n = t == n
    where   t = i * (i + 1) `div` 2
            i = round(sqrt(0.25 + 2 * (toFract n)) - 0.5) :: Integer
            toFract x = fromIntegral x :: Float

isPen :: Integer -> Bool
isPen n = p == n
    where   p = i * (3 * i - 1) `div` 2
            i = round((0.5 + sqrt(0.25 + 6* (toFract n))) / 3) :: Integer
            toFract x = fromIntegral x :: Float

solution :: [Integer] -> Maybe Integer
solution l = firstWhere (map hex l) (\n -> isTri n && isPen n)

-- solution [200...] gives the correct solution.
