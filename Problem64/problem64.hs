
nextTerm :: Int -> Int -> Int -> (Int, Int, Int)
nextTerm root subt fact = (a, sub2, fac2)
    where fac2 = denominator (fac / (root - subt^2))
