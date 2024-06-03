
import Useful
import Data.List (partition, sort)

-- helper method for equivalence classes
splitOffFirstGroup :: (a -> a -> Bool) -> [a] -> ([a],[a])
splitOffFirstGroup equal xs@(x:_) = partition (equal x) xs
splitOffFirstGroup _     []       = ([],[])

-- find equivalence classes for a given equivalence relation <equal> on a list/set <xs>
equivalenceClasses _     [] = []
equivalenceClasses equal xs = let (fg,rst) = splitOffFirstGroup equal xs
                              in fg : equivalenceClasses equal rst

questionable = filter isPrime [1000..9999]

-- permutation checking for numbers instead of strings
isPerm :: Int -> Int -> Bool
isPerm n1 n2 = isPermutation (show n1) (show n2)

possibleGroups = map sort $ filter (\g -> length g >= 3) $ equivalenceClasses isPerm questionable

-- constIncrease k l: is there a subsequence l(i_1),...,l(i_n) where l(i_j+1) - l(i_j) == 3330 for all j in [1..n-1]
constIncrease :: Int -> [Int] -> Bool
constIncrease 1 _ = True
constIncrease _ [] = False
constIncrease k [n] = False
constIncrease k (n:ns) = ((head ns) - n == 3330 && constIncrease (k-1) ns) || constIncrease k (n:(tail ns)) || constIncrease k ns

-- returns the longest subsequence of the given sequence, s.t. the difference between neighbors is the same constant
longestConstSequence :: [Int] -> Int
longestConstSequence [] = 0
longestConstSequence [n] = 0
longestConstSequence (n:ns) = max (1 + (lcs (head ns - n) ns)) $ max (longestConstSequence (n:tail ns)) (longestConstSequence ns)
    where   lcs d [n] = 0
            lcs d (n:ns)    | head ns - n < d = lcs d (n : tail ns)
                            | head ns - n == d = 1 + lcs d ns
                            | otherwise = 0

solutions = filter (\l -> longestConstSequence l >= 2) possibleGroups
