-- List Comprehension and Tuple Exercises

{-
This lab focuses on working with lists and tuples in Haskell, as well as exploring list comprehension.

Lists in Haskell:
Lists are homogeneous collections of elements of the same type. They are defined using square brackets.
Example: [1, 2, 3] or ['a', 'b', 'c']

Tuples in Haskell:
Tuples are fixed-size collections that can contain elements of different types. They are defined using parentheses.
Example: (1, "hello") or (True, 42, 'x')

List Comprehension:
List comprehension is a concise way to create lists based on existing lists or other iterables.
Basic syntax: [expression | generator, conditions]
Example: [x^2 | x <- [1..5], even x] produces [4, 16]
-}

-- 1. Create a list of tuples where the first element is a number from 1 to 10,
-- and the second element is that number squared.
-- Example: [(1,1), (2,4), (3,9), ...]
-- Hint: You may find it useful to do list comprehension with a range [1..10]
squarePairs :: [(Int, Int)]
squarePairs = [(x, x*x) | x <- [1..10]] 

-- 2. Write a function that takes a list of integers and returns a list of tuples,
-- where each tuple contains the original number and its absolute value.
-- Example: absValuePairs [-1, 2, -3] should return [(-1,1), (2,2), (-3,3)]
-- Hint: You may find it useful to do list comprehension and the abs function
absValuePairs :: [Int] -> [(Int, Int)]
absValuePairs xs = [(x, abs(x)) | x <- xs]


-- 3. Implement a function that generates a list of all possible combinations
-- of two lists as tuples.
-- Example: combinations [1,2] ['a','b'] should return [(1,'a'),(1,'b'),(2,'a'),(2,'b')]
combinations :: [a] -> [b] -> [(a, b)]
combinations xs ys = [(x, y) | x <- xs, y <-ys]

{-
Now lets discuss some useful Haskell functions for working with lists:

1. zip :: [a] -> [b] -> [(a, b)]
   The zip function takes two lists and returns a list of corresponding pairs.
   Example: zip [1,2,3] ['a','b','c'] returns [(1,'a'),(2,'b'),(3,'c')]

2. head :: [a] -> a
   The head function returns the first element of a list.
   Example: head [1,2,3] returns 1

3. tail :: [a] -> [a]
   The tail function returns a list with all elements except the first one.
   Example: tail [1,2,3] returns [2,3]

These functions can be particularly useful when working with pairs and adjacent elements in lists.
-}

-- 4. Create a function that takes a list of elements and returns a list of tuples,
-- where each tuple contains adjacent elements from the original list.
-- Hint: Consider using the zip function with tail.
-- Example: adjacentPairs [1,2,3,4] should return [(1,2),(2,3),(3,4)]
adjacentPairs :: [a] -> [(a, a)]
adjacentPairs [] = []
adjacentPairs x | (length(x) == 1) = []
adjacentPairs x = [((x !! 0), (x !! 1))] ++ adjacentPairs (drop 1 x)

-- 5. Write a recursive function that calculates the dot product of two vectors
--    represented as lists of the same length.
-- Example: dotProduct [1,2,3] [4,5,6] should return 32 (1*4 + 2*5 + 3*6)
-- Hint: You may find it useful to do pattern matching and recursion
dotProduct :: Num a => [a] -> [a] -> a
dotProduct [] [] = 0
dotProduct (x:xs) (y:ys) = x*y + dotProduct (xs) (ys) 

-- 6. Implement a function that takes a list of tuples (String, Int) representing
--    items and their prices, and returns the total cost of items costing less than 50.
-- Example: totalCostUnder50 [("apple", 30), ("banana", 60), ("orange", 40)] should return 70
-- Hint: Use list comprehension with a condition and sum the results
totalCostUnder50 :: [(String, Int)] -> Int
totalCostUnder50 xs = sum( [ y | (x, y) <- xs, ( y < 50)] )

-- 7. Create a function that takes a list of integers and returns a list of tuples,
--    where each tuple contains the original number and its factorial.
--    Use guards in the factorial calculation.
-- Example: factorialPairs [1,2,3] should return [(1,1),(2,2),(3,6)]
-- Hint: You may find it useful to define a helper function for factorial using guards
factorialPairs :: [Int] -> [(Int, Int)]
factorialPairs xs = [(x, factorialCustom(x)) | x <- xs]

factorialCustom :: Int -> Int
factorialCustom 0 = 1
factorialCustom n = n * factorialCustom (n - 1)

{- Here are some important Haskell functions for list processing:

1. filter :: (a -> Bool) -> [a] -> [a]
   The filter function takes a predicate and a list, and returns a new list containing only the elements that satisfy the predicate.
   Example: filter even [1,2,3,4,5] returns [2,4]

2. Lambda functions in Haskell:
A lambda function, also known as an anonymous function, is a function without a name.
It's defined inline using the backslash (\) followed by parameters, then an arrow (->),
and finally the function body.

Syntax: \param1 param2 ... -> expression

Example: \x -> x * 2  -- This lambda function doubles its input

Lambda functions are useful for short, one-off functions, especially when passing
functions as arguments to higher-order functions like sortBy, map, or filter.

In the sortTuples exercise, you'll use a lambda function to define a custom 
comparison function for sorting the tuples.

-}

-- use filter, returns a list of those that are true

-- 8. Use the filter function to create a list of all palindromic numbers 
-- between 1 and 1000. A number is palindromic if it reads the same backwards 
-- as forwards when written as a string.
palindromicNumbers :: [Int]
palindromicNumbers = filter isPalindrome [1..1000]

isPalindrome :: Int -> Bool
isPalindrome x = ((show x) == reverse(show x))

-- 9. Use a lambda function to create a list of tuples where the first element
-- is a number from 1 to 5, and the second element is that number raised to a given power.
-- The power should be a parameter of the function.
-- Example: powerTuples 2 should return [(1,1),(2,4),(3,9),(4,16),(5,25)]
-- Hint: Use a lambda function inside of list comprehension
--powerTuples :: Int -> [(Int, Int)]
--powerTuples = -- ??? --

-- lambda function is basically just an anonymous function