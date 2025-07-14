
import Control.Exception (throw, ErrorCall(..))
import Data.Vector (Vector, toList, fromList)
import Data.Matrix (Matrix, fromLists, colVector, multStd2, inverse, getCol)
import Data.List (splitAt)

-- perform gauss elimination on matrix-vector pair (a, b) to find the solution
-- x, s.t. a*x = b. This is done using the matrix inverse function, which,
-- according to the documentation performs gauss elimination internally.
gauss :: Matrix Rational -> Vector Rational -> Either String (Vector Rational)
gauss a b = inverse a >>= \invA -> return (getCol 1 $ multStd2 invA (colVector b))

-- returns the coefficients of the polynomial of degree length pts - 1 that fits the given points.
-- the coefficients are returned in the order from high exponent to low exponent.
fitPoly :: [(Rational, Rational)] -> [Rational]
fitPoly pts = either (\msg -> throw (ErrorCall msg)) toList res
    where   res = gauss a (fromList $ map snd pts)
            a = fromLists $ map (\x -> map (\i -> x^i) (reverse [0..length pts - 1])) xs
            xs = map fst pts

-- evaluate the polynomial with coefficients as (from high to low exponent) at x
evalPoly :: [Rational] -> Rational -> Rational
evalPoly as x = foldr (\(a, i) s -> s + a*x^i) 0 (zip as (reverse [0.. length as - 1]))

mat0 :: Matrix Rational
mat0 = fromLists    [
    [1, 1, 1],
    [4, 2, 1],
    [9, 3, 1]]

-- gen_deg = 3 :: Int
-- gen n = n^3
gen_deg = 10 :: Int
gen n = 1 - n + n^2 - n^3 + n^4 - n^5 + n^6 - n^7 + n^8 - n^9 + n^10

u = map gen [1..gen_deg + 1]

ratl :: [Int] -> [Rational]
ratl = map (\i -> fromIntegral i :: Rational)

fit :: Int -> Rational
fit k = if null diff then 0 else fst (head diff)
    where   diff = dropWhile (uncurry (==)) $ zip op (drop k (ratl u))
            op = map (\x -> evalPoly opp x) (ratl [k+1..(length u)])
            opp = fitPoly (zip (ratl [1..k]) (ratl toK))
            (toK, fromK) = splitAt k u

solve = sum $ map fit [1..gen_deg]
