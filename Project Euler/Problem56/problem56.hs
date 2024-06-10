
pairs :: [(Integer, Integer)]
pairs = [(a,b) | a<-[1..100], b<-[1..100]]

readDigit :: Char -> Integer
readDigit c = read (c:[]) :: Integer

f :: (Integer, Integer) -> Integer -> Integer
f (a, b) m = max m (sum $ map readDigit $ show (a^b))

solution :: Integer
solution = foldr f 0 pairs
