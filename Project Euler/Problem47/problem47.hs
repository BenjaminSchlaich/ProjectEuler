
import Data.List (group)

-- take an integer and return a list of prime factors
factorize :: Int -> [Int]
factorize n = 1 : factor n 2
    where factor n k    | n < 2 || n < k = []
                        | n `mod` k == 0 = k : factor (n `div` k) k
                        | otherwise = factor n (k+1)

-- take an integer and return a list of (prime factor, exponent) pairs
factorization :: Int -> [(Int, Int)]
factorization = map (\g -> (head g, length g)) . group . tail . factorize

-- find the first element of the first k consecutive elements of list l to which the predicate p applies, if such exist
firstK :: Int -> (a -> Bool) -> [a] -> Maybe a
firstK k p l = findK k k p l []
    where   findK left k p l found  | left == 0 = Just $ last found
                                    | null l = Nothing
                                    | p (head l) = findK (left - 1) k p (tail l) ((head l):found)
                                    | otherwise = findK k k p (tail l) []

result = firstK 4 ((>= 4).length.factorization) [1..]
