-- Type Checking
-- ------------------
-- Haskell has a strong, static type system. The type of every expression is known at compile time.
-- Use `:type` or `:t` in GHCi to check the type of expressions. The following exercises are designed to
-- deepen your understanding of Haskell's type system.

-- 1. Define a polymorphic function `alwaysTrue` that works for any type and always returns `True`.
--    Example: alwaysTrue 5, alwaysTrue "hello" -> True

alwaysTrue :: a -> Bool
alwaysTrue = (\x -> True)  -- Complete this function

-- 2. Define a function `applyTwice` that takes a function and an argument, and applies the function twice.
--    Example: applyTwice (*2) 3 -> 12

applyTwice :: (a -> a) -> a -> a
applyTwice f x = (f.f) (x)   -- Complete this function

-- 3. The type of a function can guide how it must behave.
--    Write a function `idList` that takes a list and returns the same list without inspecting its elements.
--    Example: idList [1,2,3] -> [1,2,3]

idList :: [a] -> [a]
idList xs = xs  -- Complete this function

-- 4. Haskell supports higher-kinded types. Define a function `mapMaybe` that behaves like `map`,
--    but works for the `Maybe` type. 
--    Example: mapMaybe (+1) (Just 5) -> Just 6
--             mapMaybe (+1) Nothing -> Nothing

mapMaybe :: (a -> b) -> Maybe a -> Maybe b
mapMaybe f Nothing = Nothing
mapMaybe f (Just ma) = Just (f (ma)) -- Complete this function

-- 5. Write a type signature for a function `composeThree` that composes three functions.
--    The function itself is already defined for you. Add the correct type signature.

composeThree :: (t1 -> t2) -> (t3 -> t1) -> (t4 -> t3) -> t4 -> t2
composeThree f g h x = f (g (h x))  -- Add the type signature here

-- 6. Define a function `applyIfTrue` that takes:
--    - A boolean value (`Bool`),
--    - A function (`a -> a`),
--    - And a value (`a`).
--    If the boolean is `True`, the function should apply the given function to the value.
--    Otherwise, it should return the value unchanged.
--    Example:
--      applyIfTrue True (*2) 5 -> 10
--      applyIfTrue False (*2) 5 -> 5

applyIfTrue :: Bool -> (a -> a) -> a -> a
applyIfTrue True f x = f x
applyIfTrue False f x = x   -- Complete this function

-- 7. Using the `primes` list from before, implement a `twinPrimes` list which is a list
--    of all tuples containing prime numbers (p, q) such that p - q = 2.
--    Example:
--      take 3 twinPrimes -> [(3, 5), (5, 7), (11, 13)]

primes :: [Int]
primes = sieve [2..]
  where
    sieve (p:xs) = p : sieve [x | x <- xs, x `mod` p /= 0]

twinPrimes :: [(Int, Int)]
twinPrimes = twinHelper primes  -- Complete this definition

twinHelper :: [Int] -> [(Int, Int)]
twinHelper [] = []
twinHelper (x:y:rem) | (y - x == 2) = [(x, y)] ++ twinHelper (y:rem)
                     | otherwise = twinHelper (y:rem)