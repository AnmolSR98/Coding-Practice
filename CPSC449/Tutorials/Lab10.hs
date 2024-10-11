import System.Win32 (xBUTTON1)
-- List Comprehension and Tuple Exercises part 2
{- We will continue from the last lab.

Here are some important Haskell functions for list processing:

1. filter :: (a -> Bool) -> [a] -> [a]
   The filter function takes a predicate and a list, and returns a new list containing only the elements that satisfy the predicate.
   Example: filter even [1,2,3,4,5] returns [2,4]

2. map :: (a -> b) -> [a] -> [b]
   The map function applies a given function to every element in a list and returns a new list with the results.
   Example: map (*2) [1,2,3] returns [2,4,6]

These functions are powerful tools for list manipulation and can often be used as alternatives to list comprehension.
-}

-- 1. Write a function that takes a string and returns a list of tuples,
--    where each tuple contains a character and its frequency in the string.
-- Example: charFrequency "hello" should return [('h',1),('e',1),('l',2),('o',1)]
-- Hint: Use list comprehension with filter and length
charFrequency :: String -> [(Char, Int)]
charFrequency str = [(c, length (filter(==c) str)) | c <- ['a'..'z'], c `elem` str]

-- 2. Implement a function that takes two lists of equal length and
--    returns a list of tuples, where each tuple contains elements from
--    both lists at the same index, but only if their sum is even.
-- Example: evenSumPairs [1,2,3,4] [5,6,7,8] should return [(1,5),(2,6),(4,8)]
-- Hint: Use zip and list comprehension with a condition
evenSumPairs :: [Int] -> [Int] -> [(Int, Int)]
evenSumPairs xs ys = [(x, y) | (x, y)<- zip (xs) (ys), mod (x+y) (2) == 0] 

-- 3. Create a recursive function that takes a list of tuples (Int, Int)
--     representing coordinates and returns the Manhattan distance from (0,0)
--     to the point furthest from the origin.
-- Manhattan distance is calculated as |x1 - x2| + |y1 - y2|
-- Example: maxManhattanDistance [(1,1),(2,2),(3,3)] should return 6
-- Hint: Use pattern matching and max function in recursion
maxManhattanDistance :: [(Int, Int)] -> Int
maxManhattanDistance xs = maxGet (-1) ([abs(x)+abs(y) | (x, y) <- xs]) 

-- can use where if helper functions are not allowed
-- still need to define a helper max function
maxGet:: Int -> [Int] -> Int
maxGet x [] = x
maxGet x list | (head list > x) = maxGet (head list) (drop 1 list)
              | otherwise = maxGet (x) (drop 1 list)

-- 4. Write a function that takes a list of integers and returns a list of tuples,
--     where each tuple contains a number and a string "Even" or "Odd".
--     Use guards to determine if a number is even or odd.
-- Example: evenOddClassify [1,2,3,4] should return [(1,"Odd"),(2,"Even"),(3,"Odd"),(4,"Even")]
-- Hint: Use list comprehension and a helper function with guards
evenOddClassify :: [Int] -> [(Int, String)]
evenOddClassify xs = [(x, classify(x)) | x <- xs]

classify:: Int -> String
classify x | (mod (x) (2) == 0) = "Even"
           | otherwise = "Odd"

-- 5. Implement a function that takes a list of strings and returns a list of tuples,
--     where each tuple contains a string and its length, but only for strings
--     that start with a vowel.
-- Example: vowelStringLengths ["apple", "banana", "orange"] should return [("apple",5),("orange",6)]
-- Hint: Use list comprehension with a condition checking the first character
vowelStringLengths :: [String] -> [(String, Int)]
vowelStringLengths strlist = [(x, length(x)) | x <- strlist, isVowel(x !! 0)] 

isVowel :: Char -> Bool
isVowel x | (x `elem` "aeiouAEIOU") = True
          | otherwise = False

-- 6. Create a recursive function that takes a list of tuples (String, Int)
--     representing items and their quantities, and returns the total number of items.
-- Example: totalItems [("apple", 3), ("banana", 2), ("orange", 4)] should return 9
-- Hint: Use pattern matching and recursion
totalItems :: [(String, Int)] -> Int
totalItems xs = sum ( [y | (x, y) <- xs ] )

-- 7. Implement a function that takes a list of tuples (String, Int) representing
--     students and their scores, and returns a list of tuples (String, Char)
--     where the second element is the grade (A, B, C, D, or F) based on the score.
--     Use guards to determine the grade. Refer to the class syllabus. 
-- Example: assignGrades [("Alice", 85), ("Bob", 70), ("Charlie", 95)] should return [("Alice",'B'),("Bob",'C'),("Charlie",'A')]
-- Hint: Use list comprehension, a where statement containing a helper function with guards for grading
assignGrades :: [(String, Int)] -> [(String, Char)]
assignGrades xs = [ (x, letterGrade(y))  | (x, y) <- xs]

letterGrade :: Int -> Char
letterGrade g | (g >= 85) = 'A'
              | (g >= 70) = 'B'
              | (g >= 55) = 'C'
              | (g >= 45) = 'D'
              | otherwise = 'F'