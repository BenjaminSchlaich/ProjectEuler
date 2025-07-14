
import qualified Data.MemoCombinators as Memo

ceil :: Double -> Int
ceil d  | fromIntegral (round d) < d = round d + 1
        | otherwise = round d

factorial :: Int -> Int
factorial n | n <= 1 = 1
            | otherwise = n * factorial (n-1)

zzz :: Int -> Int -> Int -> Int
zzz n k m   | n == 0 = if k == 0 then 1 else 0  -- cannot have empty sum other that no summands
            | n < 0 = 0                         -- no negative integers possible
            | k < 0 = 0                         -- cannot have negative amount of summands
            | n > k*m = 0                       -- cannot reach a high enough value
            | k > n = 0                         -- must have at least k*1 > n, so not possible either
            | n == k = if m >= 1 then 1 else 0  -- sequence of k 1's.
            | otherwise = sum [zzz (n-i) (k-1) i | i<-[1..m]]

zzz' :: Int -> Int -> Int -> Int
zzz' = Memo.memo3 Memo.integral Memo.integral Memo.integral zzz'

zz :: Int -> Int -> Int
zz n k = zzz' n k n

z :: Int -> Int
z n = sum [zz n k | k<-[2..n]]


