
import Data.Ratio (numerator, denominator)

solution = fst $ foldl f (0, 3/2 :: Rational) [1..1000]                                 -- generate 1000 elements and count which fit.
    where   f (count, n) _ = (if fits n then count + 1 else count, 1 + 1 / (1 + n))     -- incr. counter and generate next seq. element
            fits r = (length $ show $ numerator r) > (length $ show $ denominator r)    -- is the enum. of r greater than the denom.
