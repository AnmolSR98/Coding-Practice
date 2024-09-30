-- Mastering Conditional Logic: If-Else Statements and Guards

{- In Haskell, when using guards, the first guard that evaluates to True is the one that gets 
 executed, and the subsequent guards are ignored. Haskell does not evaluate all guards once it 
 finds a True condition. However it is best practice to not use overlapping guard conditions
 in your codes as it might get confusing to navigate.
 
 The otherwise expression is often used as a catch-all for cases that don’t match any of the 
 previous guards. What other expression could you replace the otherwise expression with, so 
 that the behavior of the function remains the same? Write it in the integer sing checking
 function down below.
-}

signCheck :: Int -> String
signCheck a
  | a > 0           = "Positive"
  | a == 0          = "Zero"
  | True           = "Negative" -- note that otherwise immediately gets set to True, ie. they are equivalent

{- While both if-else and guards can be used to handle conditions in Haskell guards provide a
 more readable and structured approach for dealing with multiple conditions. If-else is useful
 for simpler decisions but can become inconvenient with complexity. But in the end, it is a 
 matter of personal preference and there is no machine-side advantage for going with one or the
 other.
-}

{- Write a function that takes the coordinates of a point (x, y) and determines which quadrant
 of the Cartesian plane the point is in. If the point is on an axis, return a specific message.
-}
quadrantCheck :: Double -> Double -> String
quadrantCheck x y   
                    | ((x > 0) && (y > 0)) = "1"
                    | ((x < 0) && (y > 0)) = "2"
                    | ((x < 0) && (y < 0)) = "3"
                    | (y == 0) = "On X-axis"
                    | (x == 0) = "On Y-axis"
                    | otherwise = "4"
  {- FILL HERE -}

{- Write a function that takes three sides of a triangle and determines if it is equilateral, 
 isosceles, or scalene.
-}
triangleType :: Int -> Int -> Int -> String
triangleType a b c   

                     | ( (a == b) && (b == c) ) = "equilateral"
                     | ( (a /= b) && (b /= c)  && (a /= c) ) = "scalene"
                     | otherwise = "isosceles"
  {- FILL HERE -}

{- Now that we know about the conditional operators let's build up on the quadradic equation
 function from last week! We want to check a few more things this time and make the function
 perhapse useful in real life!
-}

{- Write a function that takes the coefficients (a, b, c) of a quadratic equation:
    ax^2 + bx + c = 0.

 It should:
 - Handle cases where a = 0 (i.e., it's not a quadratic equation).
 - Return both real and complex roots when applicable in a message of the type string.
 - Provide feedback about the nature of the roots (distinct, repeated, complex).

 Note 1: You can use the "Let In" and "Where" structures to make the function easier to
 read.
 Note 2: The function abs takes a number as input and returns it's absolute value.
-} 
-- Going to have to calculate the roots as well as the error message 
solveQuadratic :: Double -> Double -> Double -> String
solveQuadratic a b c   
                       | (a == 0) = "Not Quadratic"
                       | (b*b - 4*a*c > 0) = "Distinct: " ++ show ( ( (-1)*b + sqrt(b*b - 4*a*c)) / (2*a) ) ++ ", " ++ show ( ( (-1)*b - sqrt(b*b - 4*a*c)) / (2*a) )
                       | (b*b - 4*a*c == 0) = "Repeated: " ++ show ( ( (-1)*b ) / (2*a) )                    
                       | otherwise = "Complex: " ++ show ( ( (-1)*b ) / (2*a) )  ++ "+/-" ++ show ( (sqrt(4*a*c - b*b)) / (2*a)) ++ "i"-- Can also solve the complex roots as a personal challenge
  {- FILL HERE -}

{-  all guards in a function must be indented at the same level. If they are not, the
 Haskell parser will raise an error because inconsistent indentation breaks the expected
 structure of the code as Haskell is sensitive to indentation. 
 
 However, the number of spaces after the | symbol does not need to be consistent and 
 Haskell will still compile the code correctly. Like with other aspects of formatting,
 it's a good practice to align the conditions for readability but in the end, it's a matter
 of personal preference.

 TL;DR:

 correctSignCheck a
  |             a > 0                           = "Positive"
  | a == 0  = "Zero"
  |                                                             otherwise = "Negative"

 works, while

 incorrectSignCheck a
  | a > 0           = "Positive"
            | a == 0        = "Zero"
                    | otherwise   = "Negative"

 doesn't! -}