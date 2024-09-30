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
            


binomial :: Int -> Int -> Double
binomial n k 
            | ((n > k) && (k >= 0)) = (factorial (n)) / (factorial (k) * factorial(n - k))
            | otherwise = 0.0

-- QUESTION 3: converting integer to string representation without using show in prelude
myShow :: Int->String
myShow x
        | (x >= 0) = ""
