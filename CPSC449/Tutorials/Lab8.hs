{-
  List Comprehension in Haskell
  -----------------------------
  List comprehension provides a concise way to create and transform lists.
  It follows the form:
  
  [ expression | pattern <- list, condition ]
  
  - The `expression` defines how each element is transformed.
  - The `pattern <- list` part is where elements are drawn from.
  - The `condition` (optional) filters elements that should be included.

-}

-- 1. Create a List of Even Numbers
-- This example generates a list of even numbers between 1 and n.
-- Here, the pattern `x <- [1..n]` takes numbers from 1 to n, and `even x` filters out only even numbers.
evenNumbers :: Int -> [Int]
evenNumbers n = [x | x <- [1..n], even x]

-- 2. Create a List of Squares
-- This list comprehension generates squares of numbers from 1 to n.
-- The `x * x` expression squares each number.
squares :: Int -> [Int]
squares n = [x * x | x <- [1..n]]

-- 3. Filter Positive Numbers
-- The list comprehension filters out positive numbers from the list.
-- It includes only numbers `x` such that `x > 0` is true.
positiveNumbers :: [Int] -> [Int]
positiveNumbers xs = [x | x <- xs, (x > 0)]
    
-- 4. Filter Strings with More Than 3 Characters
-- This filters out strings whose length is greater than 3.
-- `length x > 3` is the condition that filters the strings.
longStrings :: [String] -> [String]
longStrings xs = [x | x <- xs, (length(x) > 3)]

-- 5. Find Divisors of a Number
-- This finds all divisors of a number `n`.
-- The list comprehension filters numbers that divide `n` with no remainder.
divisors :: Int -> [Int]
divisors n = [x | x <- [1..n], (mod n x == 0)] 

-- 6. Pythagorean Triples
-- Generates a list of Pythagorean triples (a, b, c) where a^2 + b^2 = c^2.
-- The list comprehension finds all such triples within a given range of numbers.
pythagoreanTriples :: Int -> [(Int, Int, Int)]
pythagoreanTriples n = [ (x, y, n) | x <- [1..n], y <-[1..n], (x*x + y*y == n*n)]

-- 7. Generate Multiplication Table
-- This generates a list of tuples representing the multiplication table up to `n`.
-- The list comprehension iterates over all pairs of numbers from 1 to n and computes their product.
multiplicationTable :: Int -> [(Int, Int, Int)]
multiplicationTable n = [ (x, y, n) | x <- [1..n], y <- [1..n], (x * y == n)]

-- 8. Filter Palindromes from a List of Strings
-- This example filters out palindromes from a list of strings.
-- A palindrome is a word that reads the same forward and backward, and this is checked using `reverse`.
isPalindrome :: String -> Bool
isPalindrome x = (reverse(x) == x)  

filterPalindromes :: [String] -> [String]
filterPalindromes xs = [x | x <- xs, isPalindrome(x)]

-- 9. Cartesian Product of Two Lists
-- This example creates the Cartesian product of two lists.
-- It generates all possible pairs `(x, y)` where `x` is from the first list and `y` is from the second.
cartesianProduct :: [a] -> [b] -> [(a, b)]
cartesianProduct xs ys = [(x, y) | x <- xs, y <- ys]

-- 10. Flatten a List of Lists
-- This flattens a list of lists into a single list.
-- The list comprehension iterates over each sublist and then each element within that sublist.

flatten :: [[a]] -> [a]
flatten xss = [x | xs <- xss, x <- xs] -- ordering is crucial

-- 11. Count Occurrences of a Character in a String
-- This counts how many times a character appears in a string using list comprehension.
-- The condition `x == c` ensures that only matching characters are counted.
sumFunction :: [Int] -> Int
sumFunction [] = 0
sumFunction (x:xs) = x + sumFunction(xs)

countChar :: Char -> String -> Int
countChar c xs = sumFunction( [1 | x <-xs, (x == c)] )

-- 12. List of All Subsets
-- This generates all subsets of a list using list comprehension.
-- Recursively builds subsets by including or excluding the current element.
subsets :: [a] -> [[a]]
subsets [] = [[]]
subsets (x:xs) = [x:ys| ys <- subsets xs] ++ subsets xs

-- 13. Generate All Possible Permutations of a List
-- This example generates all possible permutations of a list.
-- The list comprehension recursively constructs permutations by picking each element and removing it from the rest.
-- permutations :: Eq a => [a] -> [[a]]
-- permutations =

-- where 