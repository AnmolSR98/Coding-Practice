-- Change the below function so the discriminant and the denominator of the quadratic formula are defined as local variables using "let" and "in"
import Test.QuickCheck

roots :: Double -> Double -> Double -> (Double, Double)
roots a b c = 
    ((-b + sqrt(b*b-4*a*c ) ) / ( 2*a ) ,
    (-b-sqrt(b*b-4*a*c) ) / ( 2*a ) )

-- Used for testing your roots function
rootsTest :: Double -> Double -> Double -> (Double, Double)
rootsTest a b c = 
    ((-b + sqrt(b*b-4*a*c ) ) / ( 2*a ) ,
    (-b-sqrt(b*b-4*a*c) ) / ( 2*a ) )

-- This function should use the discrimnant in a quadratic expression to determine distinct real roots
numberNDroots :: Float -> Float -> Float -> Integer
numberNDroots a b c  =           -- enter your code here
 

-- Implement the fibonnaci sequence using recursion
fibonnaci :: Integer -> Integer
fibonnaci n =            -- enter your code here

-- Implement a factorial function using recursion
factorial :: Integer -> Integer
factorial n =            -- enter your code here

-- Implement a function that uses string concatenation to seperate the strings across three lines
onThreeLines :: String -> String -> String -> String
onThreeLines s1 s2 s3 =           -- enter your code here

-- Using Haskell gaurd syntax, implement a function which takes a character from 1-9 and returns the roman numeral of it
romanDigit :: Char -> String
romanDigit c = -- enter your code here

-- Implement a function that calculates the sum of squares for the first n natural numbers.
sumOfSquares :: Int -> Int
sumOfSquares n =            -- enter your code here

-- Implement a function to check if a given number is prime
isPrime :: Int -> Bool
isPrime n =            -- enter your code here


-- Implement a function that uses function composition to take a number, adds 3, multiply by 2, subtract 1, and then takes the absolute value. 
complexOperation :: Int -> Int
complexOperation =            -- enter your code here

prop_roots :: Double -> Double -> Double -> Bool
prop_roots a b c = (roots a b c == rootsTest a b c)