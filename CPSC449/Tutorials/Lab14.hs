-- This file demonstrates the use of `curry`, `uncurry`, partial application, and `fold`
-- with a recursive data structure.

data Tree a = Leaf | Node a (Tree a) (Tree a)
    deriving (Show)

-- Example tree with each node contains of a tuple (a, a)
exampleTree :: Tree (Int,Int)
exampleTree = Node (3, 4) 
                   (Node (1, 2) Leaf Leaf) 
                   (Node (5, 6) (Node (7, 8) Leaf Leaf) Leaf)


-- Question 1: Calculate the sum of the product of each node’s tuple values.
sumProduct :: Tree (Int, Int)  -> Int
sumProduct Leaf = 0
sumProduct (Node (a, b) l r) = a*b + sumProduct l + sumProduct r 

-- Question 2: Map over a tree, applying a function to each tuple.
mapTree :: (a -> b) -> Tree a -> Tree b
mapTree f Leaf = Leaf
mapTree f (Node a l r) = Node (f a) (mapTree f l) (mapTree f r)

-- Question 3: apply a function that doubles each element in the tuple.
doubleValues :: (Int, Int) -> (Int, Int)
doubleValues (a, b) = (2 * a, 2 * b) 
-- Example: `mapTree doubleValues exampleTree` 

-- Question 4: use * and uncurry to multiply two elements of each pair in the tree
productUncurryTree :: Tree (Int, Int) -> Tree Int
productUncurryTree (Node (a, b) l r) = Node (a*b) (productUncurryTree l) (productUncurryTree r)


-- Question 5: Function to add a constant to both values in each node’s tuple.
addConstant :: Int -> Tree (Int, Int) -> Tree (Int, Int)
addConstant x Leaf = Leaf
addConstant 0 x = x
addConstant x (Node (a, b) l r) = Node (a + x, b + x) (addConstant x l) (addConstant x r)

-- Question 6: Partial application example: adding 10 to each node.
addTenToTree ::  Tree (Int, Int) -> Tree (Int, Int)
addTenToTree = addConstant 10 


-- Question 7: Function to count nodes based on a predicate applied to the tuple.
countNodes :: ((Int, Int) -> Bool) -> Tree (Int, Int) -> Int
countNodes f Leaf = 0
countNodes f (Node (a, b) l r) | (f (a, b)) = 1 + (countNodes f l) + (countNodes f r)
                               | otherwise = (countNodes f l) + (countNodes f r)

-- Question 8: Example: Using uncurry to apply a sum predicate.
sumGreaterThan :: Int -> (Int, Int) -> Bool
sumGreaterThan = undefined 

-- Example: `countNodes (sumGreaterThan 7) exampleTree`


-- Question 9: Define a fold function for the Tree data type
foldTree :: (a -> b -> b -> b) -> b -> Tree a -> b
foldTree = undefined

-- Question 10: Using foldTree to sum all tuple products in the tree
sumProductFold :: Tree (Int, Int) -> Int
sumProductFold = undefined


-- Question 11: Using foldTree to count all nodes with a tuple sum greater than a threshold
countGreaterThan :: Int -> Tree  (Int, Int) -> Int
countGreaterThan threshold = undefined

-- Example: `countGreaterThan 7 exampleTree` counts nodes where tuple sums exceed 7.

-- Question 12: Using foldTree to create a new Tree by applying a transformation function
mapTreeFold :: (a -> b) -> Tree a -> Tree b
mapTreeFold f = undefined

-- Example: `mapTreeFold doubleValues exampleTree` doubles each value in the tree tuples.
