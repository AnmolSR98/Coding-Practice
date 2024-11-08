-- Anmol Ratol, 30231177

-- Question 1

-- Takes each of the list elements and converts it into a list of the squares of all the numbers, before filtering it down to even numbers
-- as the square of an odd number is odd, and the square of an even number is even
processNestedList:: [[Int]] -> [Int]
processNestedList = filter (even) . foldr (\x z -> square (x) ++ z) []

-- function to return a list of squares
square :: [Int] -> [Int]
square [] = []
square (x:xs) = [x*x] ++ square(xs)


-- uncurry converts (x, y) to two inputs, which are fed to the lambda function and the first is selected
fst' :: (a, b) -> a
fst' = uncurry(\x y -> x)
 
-- identical, but the second gets chosen instead
snd' :: (a, b) -> b
snd' = uncurry(\x y -> y)

-- Question 2

-- uses zipWith to feed matrix rows to addHelper
matrixAddition:: [[Int]] -> [[Int]] -> [[Int]]
matrixAddition = zipWith (\x y -> addHelper x y)

-- simple function to add each row elements from the two lists together
addHelper :: [Int] -> [Int] -> [Int]
addHelper [] [] = []
addHelper (x:xs) (y:ys) = [x+y] ++ addHelper xs ys

-- maps the multiplication helper onto each row from the matrix 
scalarMultiply :: Int -> [[Int]] -> [[Int]]
scalarMultiply v = map (\list -> multHelper v list) 

-- takes the row and times' it by the input scalar
multHelper :: Int -> [Int] -> [Int]
multHelper v [] = []
multHelper v (x:xs) = [v * x] ++ multHelper v xs

-- function that uses foldl to sum the value of all the elements along the diagonal (retrieved using traceHelper)
matrixTrace :: [[Int]] -> Int
matrixTrace = foldl (+) (0) . traceHelper 0

-- grabs the index from each element, with a recursive call incrementing the index for the next row
-- so that only diagonal elements are selected (provided that the initial value of index was 0)
-- and returns a list of those elements
traceHelper :: Int -> [[Int]] -> [Int]
traceHelper index [] = []
traceHelper index (x:xs) = [x !! index] ++ traceHelper (index+1) (xs)

-- Question 3

class Shape a where
    area :: a -> Double

data Circle = Circle Double
data Rectangle = Rectangle Double Double

-- function that simply gets the area of a circle
instance Shape Circle where
    area (Circle r) = pi * r * r

-- function that gets area of a rectangle
instance Shape Rectangle where
    area (Rectangle x y) = x * y

-- Question 4

-- Tree can be empty, or have a node with left and right child
data AVLTree a = Empty | Node a (AVLTree a) (AVLTree a)

-- getting the height of the tree
heightAVL :: AVLTree a -> Int
heightAVL Empty = -1                                            -- by convention
heightAVL (Node a Empty Empty) = 0                              -- height of a single node is zero
heightAVL (Node a l r) = 1 + max (heightAVL l) (heightAVL r)    -- the height will be one plus the height of the taller subtree

-- getting whether the tree is ordered or not
isOrdered :: (Ord a) => AVLTree a -> Bool
-- base cases for empty and singleton
isOrdered Empty = True                                          
isOrdered (Node a Empty Empty) = True
-- if node has no left child, check that the node is smaller than the right child and then recursively check the right
isOrdered (Node a Empty (Node r sl sr)) = (a < r) && isOrdered (Node r sl sr) 
-- if no right child, check that node is larger than the left child and recursively check the left
isOrdered (Node a (Node l sl sr) Empty) = (a > l) && isOrdered (Node l sl sr)
-- if both children, check left < node < right, and then recursively check both subtrees
isOrdered (Node a (Node l ll lr) (Node r rl rr)) = (a < r) && (a > l) && isOrdered (Node l ll lr) && isOrdered (Node r rl rr)

-- function to check balance
isBalanced:: AVLTree a -> Bool
isBalanced Empty = True -- base case
-- check that the height difference between the two subtrees is less than 1, and then exhaustively check the subtrees
-- which ensures that all the leafs are on the last two levels
isBalanced (Node a l r) = (abs(heightAVL l - heightAVL r) <= 1) && isBalanced (l) && isBalanced (r) 

