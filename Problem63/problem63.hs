
{-
    Upper limit for the base is 10:
    10^k we have digits(10^k) = k+1 > k = power(10^k)
    We therefore have, however, that for all powers of 10, the property digits(10^k) == power(10^k)
    cannot be fullfilled (as k is general).
    Furthermore, for a base b, b > 10 we have b^k >= 10^k => digits(b^k) >= digits(10^k) == k+1 => digits(b^k) >= k+1 > k == power(b^k),
    so 10 is the upper limit (excluded).
-}

findPowers :: Integer -> [Integer]
findPowers base = map (\(a,b,c) -> b) $ takeWhile (\(a,b,c) -> a <= c) $ all
    where   all = [(k, base^k, digits (base^k)) | k<-[1..] :: [Integer]]
            digits n = (fromIntegral $ length $ show n) :: Integer

solution = length $ concatMap findPowers [1..9]
