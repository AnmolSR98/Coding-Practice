
-- Implement a function which behaves as an exclusive Or using boolean logic
exOr :: Bool -> Bool -> Bool
exOr a b =           -- enter your code here

-- This is used for testing the exclusive Or function that you make
exOrTest :: Bool -> Bool -> Bool
exOrTest a b = a/=b

-- Implement a function that calculates the area of a triangle given its base and height.
triangleArea :: Double -> Double -> Double
triangleArea base height =           -- enter your code here

-- Implement a function that determines if three numbers can form a right triangle.
isPythagoreanTriple :: Int -> Int -> Int -> Bool
isPythagoreanTriple a b c =            -- enter your code here   

prop_exOr :: Bool -> Bool -> Bool
prop_exOr a b = (exOr a b == exOrTest a b)

prop_isPythagoreanTriple :: Int -> Int -> Int -> Bool
prop_isPythagoreanTriple a b c =
  isPythagoreanTriple (abs a) (abs b) (abs c) ==
  isPythagoreanTriple (abs b) (abs c) (abs a)