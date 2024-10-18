-- Fill in the missing code for each function

-- I) Lambda Function
-- -------------------
-- A lambda function is an anonymous function that is defined without a name.
-- Lambda functions are useful when you need a small function for a specific purpose and 
-- don’t want to give it a name. They are written using the `\` symbol followed by parameters,
-- an arrow `->`, and the function body.
-- Example: `\x -> x + 1` is a lambda function that increments a number by 1.
-- Lambdas can be passed as arguments to higher-order functions like `map` or `filter`.

-- 1. Function that uses a lambda function to increment all elements of a list by 1
incrementList :: [Int] -> [Int]
incrementList xs = undefined  -- Complete this function

-- 2. Function that uses a lambda function to multiply corresponding elements of two lists
-- Hint: You can use the `zipWith`. zipWith is a higher-order function in Haskell that takes
-- a binary function (a function that operates on two inputs) and two lists, then applies 
-- the function to corresponding pairs of elements from the two lists to produce a new list.
-- Example: zipWith (+) [1, 2, 3] [4, 5, 6] or zipWith (\x y -> x + y) [1, 2, 3] [4, 5, 6]
-- Result: [5, 7, 9]
multiplyLists :: [Int] -> [Int] -> [Int]
multiplyLists xs ys = undefined  -- Complete this function

-- 3. Function that uses a lambda to filter out words shorter than a given length from a list
filterShortWords :: Int -> [String] -> [String]
filterShortWords n words = undefined  -- Complete this function

-- II) More exercises on Maps and Filters
-- ------------------------------------
-- Review: `map` and `filter` are two of the most commonly used prelude higher-order functions
-- in Haskell:
-- - `map` applies a given function to each element of a list, producing a new list.
--   Example 1: `map (*2) [1, 2, 3]` results in `[2, 4, 6]`.
--   Example 2: `map (++ "s") ["cat", "dog"]` results in `["cats", "dogs"]` (adds "s" to each string).
--   Example 3: `map length ["hello", "world"]` results in `[5, 5]` (finds the length of each string).
--
-- - `filter` applies a predicate (a function returning a Bool) to each element of a list and
--   returns a new list containing only elements that satisfy the predicate.
--   Example 1: `filter even [1, 2, 3, 4]` results in `[2, 4]`.
--   Example 2: `filter (> 3) [1, 2, 3, 4, 5]` results in `[4, 5]` (filters elements greater than 3).
--   Example 3: `filter (\x -> length x > 3) ["cat", "horse", "dog"]` results in `["horse"]` (keeps 
--   words longer than 3 characters).

-- 1. Function to multiply each number in a list by its index position (0-based)
-- For example: multiplyByIndex [5, 10, 15] should return [0, 10, 30]
multiplyByIndex :: [Int] -> [Int]
multiplyByIndex xs = undefined  -- Complete this function

-- 2 Function to convert a list of strings to uppercase
-- For example: toUppercase ["hello", "world"] should return ["HELLO", "WORLD"]
import Data.Char (toUpper)
toUppercase :: [String] -> [String]
toUppercase strs = undefined  -- Complete this function

-- 3. Function to filter out all the strings that contain the letter 'a'
-- For example: filterNoA ["apple", "banana", "cherry", "date"] should return ["cherry"]
filterNoA :: [String] -> [String]
filterNoA strs = undefined  -- Complete this function

-- 4. Function to filter out all prime numbers from a list
-- It could be usefull to define a helper function or reuse the one you defined in
-- previous sessions.
filterPrimes :: [Int] -> [Int]
filterPrimes xs = undefined  -- Complete this function

-- III) Custom Higher Order Functions
-- ---------------------------
-- A higher-order function is a function that takes other functions as parameters or returns a function.
-- Higher-order functions allow you to abstract common patterns of computation.
-- Some built-in higher-order functions include `map`, `filter`, and `foldr`.
-- You can also define your own higher-order functions that accept functions as parameters
-- and use them in more flexible ways. While using fold functions for the following exercises is acceptable,
-- it is recommended to solve them without fold functions first. Doing so will help you better understand 
-- the challenges these exercises present and the purpose of fold functions. Once you've tackled these 
-- problems using traditional techniques, the advantages of fold functions will become clearer.

-- 1. Function that takes a function and applies it to each element of a list
applyToList :: (a -> b) -> [a] -> [b]
applyToList f xs = undefined  -- Complete this function

-- 2. Function that takes a list of functions and applies them sequentially to a value
applyFunctions :: [a -> a] -> a -> a
applyFunctions fs x = undefined  -- Complete this function

-- 3. Function that takes a comparison function and returns the maximum element from a list
maxWithFunction :: (a -> a -> Ordering) -> [a] -> a
maxWithFunction cmp xs = undefined  -- Complete this function

-- Hint: Define a helper function to compare and find the max recursively

