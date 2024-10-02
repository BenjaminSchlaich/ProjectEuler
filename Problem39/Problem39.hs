
import Data.List (permutations, (\\), inits, sort)

isPandigital :: String -> Bool
isPandigital s = length s == 9 && null ("123456789" \\ s)

isPrime n   | n < 2 = False
            | n == 2 = True
            | n `mod` 2 == 0 = False
            | otherwise = (not.or) [ n `mod` k == 0 | k<-[3..(n-1)]]

pandigitals = tail $ concatMap permutations (inits "123456789")

solution = head (filter isPrime (map read (reverse $ sort pandigitals)))
