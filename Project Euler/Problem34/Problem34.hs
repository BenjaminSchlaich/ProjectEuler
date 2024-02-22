
import Data.Char (digitToInt)

-- fact n computes n!
fact :: Integral a => a -> a
fact n  | n == 0 = 1
        | otherwise = n * fact (n-1)

-- f computes the sum of the factorial of the digits of n
f :: Int -> Int
f = sum.(map (fact.digitToInt)).show

-- upper bound for f(n):
-- f(n) <= 9! * log10(n) = 362'880 * log10(n) <! n <=> 362'880 < n / log10(n)
-- => this holds for all n >= 3'000'000
-- this limit is far too high, apparently. 1000000 works, too.
limit = 1000000

-- starting at 3, as given by the task
-- speed could be increased by a lot by caching the factorials!!
solution = sum $ filter (\n -> n == f n) [3..limit]
