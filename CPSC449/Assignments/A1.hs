
-- Anmol Ratol, 30231177

-- CANNOT USE * OPERATOR
-- QUESTION 1
multiply :: Int -> Int -> Int
multiply x y
            | ((x == 0) || (y == 0)) = 0
            | ((x > 0) && (y < 0)) = -y + multiply (x - 1) y 
            | ((x < 0) && (y > 0)) = -x + multiply x (y - 1)
            | otherwise = y + multiply (abs(x-1)) (abs(y))


-- QUESTION 2: making a binomial coefficient function
-- simple little factorial function that spits out double for the sake of making division  simpler
factorial :: Int -> Double
factorial n
            | (n > 0) = fromIntegral(n) * factorial (n - 1)
            | (n == 0) = 1.0
            | otherwise = 0
            


binomial :: Int -> Int -> Int
binomial n k 
            | ((n >= k) && (k >= 0)) = round( (factorial (n)) / (factorial (k) * factorial(n - k)) )
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
myShow :: Int -> String
myShow x 
        | (x == 0) = ""
        | otherwise = myShow( round(fromIntegral(x - mod x 10) / 10)) ++ convertToString(mod x 10)

-- QUESTION 3b: 

-- function to return the length of a string
myLength :: String -> Int
myLength x 
           | (x == "") = 0
           | otherwise = 1 + myLength(drop 1 x)

-- determining whether an integer is even or not
myEven :: Int -> Bool
myEven x
        | (mod x 2 == 0) = True
        | otherwise = False 

-- function to determine whether number of digits in an integer is even or not
processCheck :: Int -> Bool
processCheck x = (myEven . myLength . myShow) x 

-- QUESTION 4:

-- 4a: function to get a power of 2 maybe
powerOfTwoMaybe :: Integer -> Maybe Integer
powerOfTwoMaybe x 
                | (x < 0) = Nothing
                | otherwise = Just (2^x)

-- 4b: 
-- added the deriving Show just to get it to appear nicely
data SF a = SS a | FF deriving Show

-- integer version of factorial function
factorialInteger :: Integer-> Integer
factorialInteger n
            | (n > 0) = n * factorialInteger (n - 1)
            | (n == 0) = 1
            | otherwise = 0

factorialSF :: Integer -> SF Integer
factorialSF x 
        | (x < 0) = FF
        | (x >= 0) = SS (factorialInteger(x)) 
        
-- 4c:

-- function that returns log_2_(x), in int form
intLog :: Integer -> Integer
intLog x 
        | (x == 1) = 0
        | otherwise = 1 + (intLog.floor) (fromIntegral(x) / 2)


invExpEither :: Integer -> Either String Integer
invExpEither x 
                | (x < 0) = Left "Input must be a non-negative integer"
                | (x == 0) = Left "Undefined" -- was unsure what to place here, since 0 ought to prompt an error message as well
                | otherwise = Right (intLog(x)) -- used log function here

