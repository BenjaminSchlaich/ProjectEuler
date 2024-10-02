
import Data.List ((\\))

isPandigital :: String -> Bool
isPandigital s = length s == 9 && null ("123456789" \\ s)

generatePandigital :: Int -> Int
generatePandigital n = findFirst 1 ""
    where findFirst i s | length (nis ++ s) > 9 = -1
                        | isPandigital (s ++ nis) = read (s ++ nis)
                        | otherwise = findFirst (i+1) (s ++ (show (n*i)))
                            where   nis = show (n*i)

findMax = foldl max (-1) (map generatePandigital (reverse [9..9876]))
