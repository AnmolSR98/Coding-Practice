-- Data Types with Type Parameters - Maybe and Either

{-
Type constructors can take types as parameters to produce new types.

for example:

data Maybe a = Nothing | Just a

The 'a' here is the type parameter.
And because there's a type parameter involved, we call Maybe a type constructor.
Depending on what we want this data type to hold when it's not Nothing, this type constructor can end up producing a type of Maybe Int, Maybe Car, Maybe String, etc.
No value can have a type of just Maybe, because that's not a type, it's a type constructor.
In order for this to be a real type that a value can be part of, it has to have all its type parameters filled up.
So if we pass Char as the type parameter to Maybe, we get a type of Maybe Char.
The value Just 'x' has a type of Maybe Char, for example.
-}

-- Exercises:
-- 1. Play around Maybe type by running the following in the ghci
{-
ghci> :t Just

ghci> :t Just "Haha"

ghci> :t Just 84

ghci> :t Nothing

ghci> Just 10 :: Maybe Double

-}

-- Why do we use Maybe?
-- the <Maybe a> type is used to represent computations that may fail or produce no result.
-- It is a way of handling values that might be missing or computations that might not return a meaningful value.

-- 2.
-- Write the safeSqrt function that when the input is positive, outputs the square root of the input
-- and when the output is negative outptus Nothing
safeSqrt :: Double -> Maybe Double
safeSqrt x 
            | (x >= 0) = Just(sqrt x)
            | otherwise = Nothing 


-- 3. Write the safeIndex function, that takes a list and an integer as index
-- if the index is out of bounds, returns Nothing, otherwise the element at that index
-- you can use the following functions:
-- length :: [a] -> Int : returns the length of the input list
-- !! :: [a] -> Int -> a : returns a list and an integer and returns the element at the input index
safeIndex :: [a] -> Int -> Maybe a
safeIndex x y 
                | (y >= length(x)) = Nothing
                | otherwise = Just(!! x y)


-- The Either data type
{-
The Either type is used when a computation might return one of two possible results:
one for success and one for failure (or some other alternate outcome).
It allows you to provide additional information about why a computation failed.

data Either a b = Left a | Right b
-}

-- 4. rewrite the safeSqrt function using the Either data type
--safeSqrt' :: Double -> Either String Double
--safeSqrt' = -- ??? --


-- 5. rewrite the safeIndex function using the Either data type
--safeIndex' :: [a] -> Int -> Either String a
--safeIndex' = -- ??? --


-- 6. Write a function that takes a list of integers (l :: [Int]) and an integer index (i :: Int).
-- If i is within bounds, get the element at index i, say i' = l[i].
-- Then, if i' is within bounds, return the element at index i' in the list.
-- If i or i' are out of bounds, return Nothing.
--chainSafeIndex :: [Int] -> Int -> Maybe Int
--chainSafeIndex = -- ??? --


-- 7. rewrite function chainSafeIndex, with Either data type
--chainSafeIndex' :: [Int] -> Int -> Either String Int
--chainSafeIndex' = -- ??? --