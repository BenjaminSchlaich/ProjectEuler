
import Useful

isLychrel :: Integer -> Bool
isLychrel n = check 50 n
    where   check it n = if it == 0 then True else ((not.isPalindrome) (next n)) && check (it-1) (next n)
            next n = n + (read $ reverse $ show n)

solution = length [n | n<-[0..10^4 - 1], isLychrel n]
