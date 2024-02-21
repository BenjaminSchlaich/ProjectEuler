
factorial n | n == 0 = 1
            | otherwise = n * factorial (n-1)

quersumme n = sum $ map ctoi $ show n
    where ctoi c = read [c]

solution = quersumme $ factorial 100
