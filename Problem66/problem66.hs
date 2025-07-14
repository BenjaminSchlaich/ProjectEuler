
{-
    Solve x^2 - D*y^2 = 1:

    x^2 = D * y^2 + 1

    -> Generate square numbers, check 
-}

import Data.List ()

findSmallestX :: Int -> Int
findSmallestX D = filter satisfies
