
fibonacci :: [Integer]
fibonacci = extend (0, 1)
    where extend (a, b) = a : extend (b, a+b)

solution = length $ takeWhile ((< 1000).length.show) fibonacci
