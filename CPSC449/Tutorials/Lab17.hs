
{-
 3. Binary Trees & Basic Operations

In order to represent a binary tree in haskell, we can use a recursive algebraic type. 
Below we see a recursive algebraic type, whereby there are two cases, firstly, an empty node
secondly, an integer value for your node, and a recursive left / right binary tree. 
-}

data BinaryTree a = Empty | Node a (BinaryTree a) (BinaryTree a)

-- Implement a function to calculate the depth of the tree
treeDepth :: BinaryTree a -> Int
treeDepth = undefined 

-- Implement a function to perform an in-order traversal of the tree and returns a list of the values.
inOrder :: BinaryTree a -> [a]
inOrder = undefined 

-- Write a function to find the sum of all left leaves in a binary tree.
sumLeftLeaves :: Num a => BinaryTree a -> a
sumLeftLeaves = undefined

-- Implement a function to check if two binary trees are identical.
areIdentical :: Eq a => BinaryTree a -> BinaryTree a -> Bool
areIdentical = undefined

-- Implement a function which checks whether or not a specific item is found in a binary tree and returns the level
contains :: Eq a => a -> BinaryTree a -> (Bool, Maybe Int)
contains = undefined

-- Implement a function to determine whether a binary tree is balanced or not
isBalanced :: BinaryTree a -> Bool
isBalanced tree = undefined