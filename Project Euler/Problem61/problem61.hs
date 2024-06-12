
import Useful

-- n ∈ [45, 140]
tri :: [Int]
tri = map (\n -> (n*(n+1)) `div` 2) [45..140]

sqr :: [Int]
sqr = map (\n -> n^2) [32..99]

-- n(3n-1)/2 = c <=> n(3n-1) = 2c <=> 3n^2 - n - 2c = 0 <=> n = (1 + sqrt(1 + 24c)) / 6
-- n ∈ [26, 81]
pen :: [Int]
pen = map (\n -> (n*(3*n-1)) `div` 2) [26..81]

-- n(2n-1) = c <=> 2n^2 - n - c = 0 <=> n = (1 + sqrt(1 + 8c)) / 4
hex :: [Int]
hex = map (\n -> n*(2*n-1)) [23..70]

-- n(5n-3)/2 = c <=> n(5n-3) = 2c <=> 5n^2 - 3n - 2c = 0 <=> n = (3 + sqrt(9 + 40*c)) / 10
hep :: [Int]
hep = map (\n -> (n*(5*n-3)) `div` 2) [21..63]

oct :: [Int]
oct = map (\n -> n*(3*n-2)) [19..57]

{-
    We construct an search through the following graph:
    start node  |   tri. nums.  |   sqr. nums.  |   ...
                -       1035    -   ...
                -       1081    -   ...
    "start"     -       1128    -   ...

    where start is connected to aall tri. nums, and the numbers from neighboring columns have
    an edge, if the first ends on the 2 digits that the next starts with.
    By finding the only traversal of the graph from tri to tri, we find the solution.
-}
nodes :: [[String]]
nodes = map (map show) [tri, sqr, pen, hex, hep, oct, tri]
