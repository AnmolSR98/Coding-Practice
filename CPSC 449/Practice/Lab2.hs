-- Change the below function so the discriminant and the denominator of the quadratic formula are defined as local variables using "let" and "in"

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
numberNDroots a b c  = if ((b*b - 4*a*c) == 0) then 1
                    else if ((b*b - 4*a*c) < 0) then 0
                    else 2 -- enter your code here
 

-- Implement the fibonnaci sequence using recursion
fibonnaci :: Integer -> Integer
fibonnaci n = if n == 0 then 0           -- enter your code here
            else if n == 1 then 1
            else (fibonnaci (n - 1) + fibonnaci (n - 2))

-- Implement a factorial function using recursion
factorial :: Integer -> Integer
factorial n = if n == 0 then 1
        else n * factorial (n-1)           -- enter your code here

-- Implement a function that uses string concatenation to seperate the strings across three lines
onThreeLines :: String -> String -> String -> String
onThreeLines s1 s2 s3 = s1 ++ "\n" ++ s2 ++ "\n" ++ s3           -- enter your code here

-- Using Haskell gaurd syntax, implement a function which takes a character from 1-9 and returns the roman numeral of it
romanDigit :: Char -> String
romanDigit c    | c == '1' = "I"
                | c == '2' = "II"
                | c == '3' = "III"
                | c == '4' = "IV"
                | c == '5' = "V"
                | c == '6' = "VI"
                | c == '7' = "VII"-- enter your code here
                | c == '8' = "VIII"
                | c == '9' = "IX"


-- Implement a function that calculates the sum of squares for the first n natural numbers.
sumOfSquares :: Int -> Int
sumOfSquares n = if n == 1 then 1
        else n*n + sumOfSquares(n - 1)           -- enter your code here

-- Implement a function to check if a given number is prime
--isPrime :: Int -> Bool
--isPrime n =            -- enter your code here


-- Implement a function that uses function composition to take a number, adds 3, multiply by 2, subtract 1, and then takes the absolute value. 
--complexOperation :: Int -> Int
--complexOperation x = absolute.           -- enter your code here

--prop_roots :: Double -> Double -> Double -> Bool
--prop_roots a b c = (a /= 0.0) ==> (roots a b c == rootsTest a b c)
