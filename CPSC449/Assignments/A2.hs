
-- Anmol Ratol 3023177
-- Question 1: Transpose a Matrix
transposeMatrix :: [[a]] -> [[a]]
transposeMatrix x = transposer (x) (0) 

-- helper function that recursively uses the number of columns to determine when the process is done
transposer :: [[a]] -> Int -> [[a]]
transposer x y | (y == length(x !! 0)) = []
               | otherwise = [getArrayOfColumnN (x) (y)] ++ transposer (x) (y+1)

-- function that returns an array of the nth element of each column
getArrayOfColumnN :: [[a]] -> Int -> [a]
getArrayOfColumnN [] y = []
getArrayOfColumnN (x:xs) y = [(x !! y)] ++ getArrayOfColumnN (xs) (y)

-- Question 2: Group by Predicate
-- going to need a take while esque helper
-- will insert an errant empty list if the first value is not true, maybe have a checker for that
groupByPredicate :: (a -> Bool) -> [a] -> [[a]]
groupByPredicate func [] = []
groupByPredicate func xs | (checkFirst func xs) = [takeWhile (func) (xs)] ++ groupByPredicate (functionInverse func) (drop (getNumberTaken (func) (xs)) (xs)) 
                         | otherwise = [takeWhile (functionInverse func) (xs)] ++ groupByPredicate (func) (drop (getNumberTaken (functionInverse func) (xs)) (xs))

checkFirst :: (a -> Bool) -> [a] -> Bool
checkFirst func [] = True
checkFirst func (x:xs) = func x

functionInverse :: (a -> Bool) -> a -> Bool
functionInverse func x = not(func x)

getNumberTaken :: (a -> Bool) -> [a] -> Int
getNumberTaken func xs = length(takeWhile (func) (xs))

-- Question 3: Movie questions
data Movie = Movie { title :: String, rating :: Float, genre :: String } deriving Show

-- writing out the list of movies
movies :: [Movie]
movies = [  Movie "Inception" 8.8 "Sci-Fi", 
            Movie "The Matrix" 8.7 "Sci-Fi", 
            Movie "Jaws" 7.9 "Thriller", 
            Movie "Frozen" 7.4 "Animation", 
            Movie "Interstellar" 8.6 "Sci-Fi", 
            Movie "The Godfather" 9.7 "Crime" ]

-- haskell has a truly bizarre convention for accessing custom data types attributes
topRatedMovies :: [Movie] -> Float -> [String]
topRatedMovies mlist score = [(title x) | (x) <- mlist, ((rating x) >= score)]

moviesByGenre :: [Movie] -> String -> [String]
moviesByGenre mlist mgenre = [(title x) | (x) <- mlist, ((genre x) == mgenre)]

adjustedRatings :: [Movie] -> [Movie]
adjustedRatings mlist = [ Movie (title x) ((\x -> x + 0.5) (rating x)) (genre x) | x <- mlist]

-- Question 4: Merge sort, 
-- working, but I don't think this is an actual merge sort unfortunately since it isn't cleanly merge two halves together 
-- maybe use take to get first half of list 

-- actual merge sort function here
mergeSort:: Ord a => [a] -> [a]
mergeSort a = runMerge a

getHalf:: Int -> Int
getHalf x = round(fromIntegral(x)/2)

-- maybe get a function to divide them into two lists and then use list comprehension
runMerge:: Ord a => [a] -> [a]
runMerge x | (length(x) <= 1) = x
runMerge x = merge (runMerge (take (getHalf (length x)) x)) (runMerge (drop (getHalf (length x)) x)) 
           -- | otherwise = merge (genericTake (getHalf (length x)) (x)) (x) --merge (merge (x) (y)) (runMerge (rem))


-- merging two lists so that they appear in order
merge:: Ord a => [a] -> [a] -> [a]
merge [] [] = []
merge (x:xs) [] = [x] ++ merge (xs) []
merge [] (y:ys) = [y] ++ merge [] (ys)
merge (x:xs) (y:ys) | (x < y)   = [x] ++ merge (xs) (y:ys)
                    | otherwise = [y] ++ merge (x:xs) (ys)
