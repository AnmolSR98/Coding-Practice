processNestedList:: [[Int]] -> [Int]
processNestedList = map (\x -> x*x) . filter (even) . nestedHelper

nestedHelper :: [[Int]] -> [Int]
nestedHelper [] = []
nestedHelper (x:xs) = x ++ nestedHelper xs


matrixAddition:: [[Int]] -> [[Int]] -> [[Int]]
matrixAddition = zipWith (\x y -> addHelper x y)

addHelper :: [Int] -> [Int] -> [Int]
addHelper [] [] = []
addHelper (x:xs) (y:ys) = [x+y] ++ addHelper xs ys

scalarMultiply :: Int -> [[Int]] -> [[Int]]
scalarMultiply v = map (\list -> multHelper v list) 

multHelper :: Int -> [Int] -> [Int]
multHelper v [] = []
multHelper v (x:xs) = [v * x] ++ multHelper v xs

matrixTrace :: [[Int]] -> Int
matrixTrace = foldl (+) (0) . traceHelper 0

traceHelper :: Int -> [[Int]] -> [Int]
traceHelper index [] = []
traceHelper index (x:xs) = [x !! index] ++ traceHelper (index+1) (xs)


