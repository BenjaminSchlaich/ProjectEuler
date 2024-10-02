
import Data.List (nub, filter, intersect, delete)

baseFractions :: [(Integer, Integer)]
baseFractions = [ (a, b) | b<-[1..9], a<-[1..b-1]]

extendFraction :: (Integer, Integer) -> [(Integer, Integer)]
extendFraction (a, b) = dropWhile large $ takeWhile small [(a*k, b*k) | k<-[1..]]
    where   small (a, b) = a < 100 && b < 100
            large (a, b) = a < 10 || b < 10

nonTrivial :: [(Integer, Integer)] -> [(Integer, Integer)]
nonTrivial = filter (\(a, b) -> a `mod` 10 /= 0 || b `mod` 10 /= 0)

curiousPair (a, b) (a', b') = (not.null) [c | c<-letters, (delete c $ show a') == (show a) && (delete c $ show b') == (show b)]
    where letters = nub $ intersect (show a') (show b')

curious :: (Integer, Integer) -> [(Integer, Integer)] -> [(Integer, Integer)]
curious (a, b) = filter (curiousPair (a, b))
    where   

curiousFractions = zipWith curious baseFractions (map (nonTrivial.extendFraction) baseFractions)

-- what a shitshow...
