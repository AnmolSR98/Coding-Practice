-- Question 1: Transpose a Matrix
transposeMatrix :: [[a]] -> [[a]]
transposeMatrix x = transposer (x) (0) 

transposer :: [[a]] -> Int -> [[a]]
transposer x y | (y == length(x !! 0)) = []
               | otherwise = [getArrayOfColumnN (x) (y)] ++ transposer (x) (y+1)

getArrayOfColumnN :: [[a]] -> Int -> [a]
getArrayOfColumnN [] y = []
getArrayOfColumnN (x:xs) y = [(x !! y)] ++ getArrayOfColumnN (xs) (y)

