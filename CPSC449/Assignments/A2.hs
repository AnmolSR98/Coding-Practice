-- Anmol Ratol, 30231177
-- Question 1: Transpose a Matrix
transposeMatrix :: [[a]] -> [[a]]
transposeMatrix x = transposer (x) (0) 

-- helper function that recursively uses the number of columns to determine when the process is done
transposer :: [[a]] -> Int -> [[a]]
transposer x y | (y == length(x !! 0)) = []
               | otherwise = [getArrayOfColumnN (x) (y)] ++ transposer (x) (y+1)

-- function that returns an array of the nth element of each column
getArrayOfColumnN :: [[a]] -> Int -> [a]
getArrayOfColumnN [] y = []
getArrayOfColumnN (x:xs) y = [(x !! y)] ++ getArrayOfColumnN (xs) (y)

