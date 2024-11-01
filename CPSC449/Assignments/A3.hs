-- Question 1

processNestedList:: [[Int]] -> [Int]
processNestedList = filter (even) . foldr (\x z -> square (x) ++ z) []

square :: [Int] -> [Int]
square [] = []
square (x:xs) = [x*x] ++ square(xs)

nestedHelper :: [[Int]] -> [Int]
nestedHelper [] = []
nestedHelper (x:xs) = x ++ nestedHelper xs

-- change to use two input lambda function FIX []
fst' :: (a, b) -> a
fst' = (\(x, y) -> x)
 
snd' :: (a, b) -> b
snd' = (\(x, y) -> y)

-- Question 2

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

-- Question 3

class Shape a where
    area :: a -> Double

data Circle = Circle Double
data Rectangle = Rectangle Double Double

instance Shape Circle where
    area (Circle r) = pi * r * r

instance Shape Rectangle where
    area (Rectangle x y) = x * y

-- Question 4

data AVLTree a = Empty | Node a (AVLTree a) (AVLTree a)

-- getting the height of the tree
heightAVL :: AVLTree a -> Int
heightAVL Empty = -1
heightAVL (Node a Empty Empty) = 0
heightAVL (Node a l r) = 1 + max (heightAVL l) (heightAVL r) 

-- getting some sort of error with regards to comparison on this one [FIXED]
isOrdered :: (Ord a) => AVLTree a -> Bool
isOrdered Empty = True
isOrdered (Node a Empty Empty) = True
isOrdered (Node a Empty (Node r sl sr)) = (a < r) && isOrdered (Node r sl sr)
isOrdered (Node a (Node l sl sr) Empty) = (a > l) && isOrdered (Node l sl sr)
isOrdered (Node a (Node l ll lr) (Node r rl rr)) = (a < r) && (a > l) && isOrdered (Node l ll lr) && isOrdered (Node r rl rr)

-- need to check that it is balanced
isBalanced:: AVLTree a -> Bool
isBalanced Empty = True
isBalanced (Node a l r) = (abs(heightAVL l - heightAVL r) <= 1)  


