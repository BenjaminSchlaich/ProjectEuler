
import Data.List(find)
import Useful

isValid :: Int -> Bool
isValid n = all (isPermutation $ show n) [show (k*n) | k<-[2..5]]

solution = find isValid [1..]
