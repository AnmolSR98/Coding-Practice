-- making a quickie function as described in assignment 1
-- CANNOT USE * OPERATOR
-- QUESTION 1
multiply :: Int -> Int -> Int
multiply x y
            | ((x == 0) || (y == 0)) = 0
            | ((x > 0) && (y < 0)) = -y + multiply (x - 1) y 
            | ((x < 0) && (y > 0)) = -x + multiply x (y - 1)
            | otherwise = y + multiply (abs(x-1)) (abs(y))


-- QUESTION 2: making a binomial coefficient function
-- Working fine, just need to make sure to find a way to convert integer to double [DONE]
factorial :: Int -> Double
factorial n
            | (n > 0) = fromIntegral(n) * factorial (n - 1)
            | (n == 0) = 1.0
            | otherwise = 0
            


binomial :: Int -> Int -> Int
binomial n k 
            | ((n > k) && (k >= 0)) = round( (factorial (n)) / (factorial (k) * factorial(n - k)) )
            | otherwise = 0

-- QUESTION 3a: converting integer to string representation without using show in prelude

-- simple function to convert numbers less than 10 to strings
convertToString :: Int -> String
convertToString x
                  | (x == 0) = "0"
                  | (x == 1) = "1"
                  | (x == 2) = "2"
                  | (x == 3) = "3"
                  | (x == 4) = "4"
                  | (x == 5) = "5"
                  | (x == 6) = "6"
                  | (x == 7) = "7"
                  | (x == 8) = "8"
                  | otherwise = "9"

-- assumed that 0 doesn't count as positive 
myShow :: Int->String
myShow x 
        | (x == 0) = ""
        | otherwise = myShow( round(fromIntegral(x - mod x 10) / 10)) ++ convertToString(mod x 10)

-- QUESTION 3b: 

-- function to return the length of a string
myLength :: String -> Int
myLength x 
           | otherwise = 0

-- determining whether an integer is even length or not
myEven :: Int -> Bool
myEven x
        | (mod x 2 == 0) = True
        | otherwise = False 

-- function to determine whether number of digits in an integer is even or not
processCheck :: Int -> Bool
processCheck x = myEven(myLength(myShow(x))) 