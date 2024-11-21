-- Lazy Evaluation
-- -------------------
-- Haskell uses lazy evaluation, meaning expressions are not evaluated until their values are needed.
-- This allows infinite data structures and can improve efficiency by avoiding unnecessary computations.
-- However, it also means you need to think carefully about when and how evaluation occurs to avoid issues like space leaks.

-- 1. Define an infinite list of all natural numbers (0, 1, 2, 3, ...).
--    Use this list to write a function `takeEvenNumbers` that takes the first `n` even numbers from the list.

infiniteNaturals :: [Int]
infiniteNaturals = [1..]  -- Define the infinite list

takeEvenNumbers :: Int -> [Int]
takeEvenNumbers n = take n (filter even infiniteNaturals)  -- Complete this function

-- 2. Define a function `sumToN` that lazily computes the sum of the first `n` natural numbers.
--    Use the infinite list `infiniteNaturals` in your implementation.

sumToN :: Int -> Int
sumToN n = sum (take n infiniteNaturals)  -- Complete this function

-- 3. Lazy evaluation allows for conditional processing of infinite lists.
--    Define a function `findFirstMultiple` that finds the first number in an infinite list
--    that is a multiple of a given number `k`.

findFirstMultiple :: Int -> Int
findFirstMultiple k = head (filter (\x -> (mod x k == 0)) infiniteNaturals)  -- Complete this function

-- 4. Haskell's laziness can sometimes lead to inefficiencies. Define a recursive list `fibs`
--    of Fibonacci numbers using laziness, and write a function `nthFib` to find the nth Fibonacci number.

fibs :: [Int]
--fibs = 0 : 1 : zipWith (+) fibs (tail fibs)   -- Define the lazy Fibonacci sequence
fibs = map fibohelp infiniteNaturals

fibohelp :: Int -> Int
fibohelp 0 = 1
fibohelp 1 = 1
fibohelp n = fibohelp (n-1) + fibohelp (n-2)

nthFib :: Int -> Int
nthFib n = fibs !! n 

-- 5. Implement the Sieve of Eratosthenes lazily.

primes :: [Int]
primes = sieve [2..] -- Implement the sieve here

-- function here to remove each multiple of n from the list of infinite numbers
sieve :: [Int] -> [Int]
sieve (h:xs) = [h] ++ sieve (filter (\x -> (mod x h /= 0)) xs)