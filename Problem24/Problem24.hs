
import Data.List (permutations, sort)

solution = (sort $ permutations [0..9]) !! 999999
