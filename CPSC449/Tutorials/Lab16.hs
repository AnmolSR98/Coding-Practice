
{-
 1. Product Types
    Product types are a form of data type in haskell that has one or more values
    provided to their constructor.

    We will now build on what you have learnt about typeclasses and instances and use them in the context
    of a product type.

-}

-- 1.1 First, create a product data type called Coord which takes two integers, X and Y.
data Coord = C Integer Integer

-- 1.2 Now implement your own instance of Show for the data type which outputs a string formatted as: 
-- "Coordinate - X: " ++ show x ++ " Y: " ++ show y
instance Show Coord where
    show (C x y) = "Coordinate - X: " ++ show x ++ " Y:" ++ show y

-- 1.3 Now implement your own instance of Eq for the data type which checks for equality in X and Y values.
instance Eq Coord where
    (C x1 y1) == (C x2 y2) = (x1 == x2) && (y1 == y2)

-- 1.4 Now implement your own instance of the Num typeclass for the data type
instance Num Coord where
    (C x1 y1) + (C x2 y2) = C (x1 + x2) (y1 + y2)
    (C x1 y1) - (C x2 y2) = C (x1 - x2) (y1 - y2)
    (C x1 y1) * (C x2 y2) = C (x1 * x2) (y1 * y2)
    negate (C x y) = C (-x) (-y)
    abs (C x y) = C (abs x) (abs y)
    signum (C x y) = C (signum x) (signum y)
    fromInteger n = C n n



-- 1.5 Now implement a typeclass called OriginDistance which contains a function declaration called
-- distanceFromOrigin which takes some polymorphic input and returns a double
class OriginDistance a where
    distanceFromOrigin :: a -> Double

-- 1.6 Now implement your own instance of the OriginDistance typeclass on the Coord data type with a 
-- definition of the distanceFromOrigin function which uses the pythagorean theorem to find the distance from origin
-- Hint: the fromIntegral function may help
instance OriginDistance Coord where 
    distanceFromOrigin :: Coord -> Double
    distanceFromOrigin (C x y) = sqrt(fromIntegral(x*x) + fromIntegral(y*y))

{- 
2. Recurisve Algebraic Types
    Recurisve Algebraic Types in haskell are data types in haskell which have been defined in a recursive way.
    This means that the data object itself is referenced in the data object. For example:

    Example: data BinaryTree a = Empty | Node a (BinaryTree a) (BinaryTree a)
-}

-- 2.1 Define a singly linked list recursive data type which derives show
data LinkedList a = Empty | Node a (LinkedList a) deriving Show

-- 2.2 Implement a function to determine the length of a linkedlist
sizeList :: LinkedList a -> Integer
sizeList Empty = 0
sizeList (Node a ll) = 1 + sizeList ll

-- 2.3 Implement a function to reverse the linked list FIX
reverseList :: LinkedList a -> LinkedList a
reverseList Empty = Empty
reverseList a = reverseHelper a Empty

reverseHelper :: LinkedList a -> LinkedList a -> LinkedList a
reverseHelper Empty ol = ol
reverseHelper (Node a arem) (Node b brem) = reverseHelper (arem) (Node a (Node b brem))
reverseHelper (Node a arem) Empty = reverseHelper arem (Node a Empty)

-- 2.4 implement a function to build a linked list from a regular haskell list.
fromList :: [a] -> LinkedList a
fromList [] = Empty
fromList (x:xs) = Node x (fromList xs) 
-- fromList = foldr Node Empty

-- 2.5 Implement a function to convert a linked list back to a regular Haskell list 
toList :: LinkedList a -> [a]
toList Empty = []
toList (Node a ll) = a : toList ll  