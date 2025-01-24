
{-
 3. Binary Trees & Basic Operations

In order to represent a binary tree in haskell, we can use a recursive algebraic type. 
Below we see a recursive algebraic type, whereby there are two cases, firstly, an empty node
secondly, an integer value for your node, and a recursive left / right binary tree. 
-}

data BinaryTree a = Empty | Node a (BinaryTree a) (BinaryTree a)

-- Implement a function to calculate the depth of the tree
treeDepth :: BinaryTree a -> Int
treeDepth Empty = -1
treeDepth (Node a Empty Empty) = 0
treeDepth (Node a l r) | (treeDepth l > treeDepth r) = 1 + treeDepth l
                       | otherwise = 1 + treeDepth r

-- Implement a function to perform an in-order traversal of the tree and returns a list of the values.
inOrder :: BinaryTree a -> [a]
inOrder Empty = [] 
inOrder (Node a Empty Empty) = [a]
inOrder (Node a l Empty) = inOrder l ++ [a]
inOrder (Node a l r) = inOrder l ++ a:(inOrder r)

-- Write a function to find the sum of all left leaves in a binary tree.
sumLeftLeaves :: Num a => BinaryTree a -> a
sumLeftLeaves Empty = 0
sumLeftLeaves (Node a l r) = sum(inOrder l) 

-- Implement a function to check if two binary trees are identical.
areIdentical :: Eq a => BinaryTree a -> BinaryTree a -> Bool
areIdentical Empty Empty = True
areIdentical (Node l ll lr) (Node r rl rr) = (l == r) && areIdentical ll rl && areIdentical lr rr

-- Implement a function which checks whether or not a specific item is found in a binary tree and returns the level
contains :: Eq a => a -> BinaryTree a -> (Bool, Maybe Int)
contains elem tree = containsHelper elem 0 tree

containsHelper :: Eq a => a -> Int -> BinaryTree a -> (Bool, Maybe Int)
containsHelper elem index Empty = (False, Nothing)
containsHelper elem index (Node a l r) | (a == elem) = (True, Just index)
                                       | otherwise = containsHelper elem (index+1) l

-- Implement a function to determine whether a binary tree is balanced or not
isBalanced :: BinaryTree a -> Bool
isBalanced tree = undefined