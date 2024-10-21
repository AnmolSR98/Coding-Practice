-- Anmol Ratol 3023177
-- Question 1: Transpose a Matrix

-- transpose matrix immediately calls a helper function
transposeMatrix :: [[a]] -> [[a]]
transposeMatrix x = transposer (x) (0)

-- helper function that calls another function that gets all the elements in a specific column
transposer :: [[a]] -> Int -> [[a]]
transposer x y | (y == length(x !! 0)) = [] -- if the column being requested equals the length of the matrix, then return []
               | otherwise = [getArrayOfColumnN (x) (y)] ++ transposer (x) (y+1) -- get the column at y and then get the column at y + 1
                                                                                 -- provided there is one                   

-- function that returns an array of the nth columns of the matrix
getArrayOfColumnN :: [[a]] -> Int -> [a]
getArrayOfColumnN [] y = [] -- when there no rows left, terminate
getArrayOfColumnN (x:xs) y = [(x !! y)] ++ getArrayOfColumnN (xs) (y) -- take the nth element of each row

-- Question 2: Group by Predicate

-- if the first value is true, then start grouping the true values before grouping false, then grouping true, and so on
-- otherwise, group by false, then true, then false, etc.
groupByPredicate :: (a -> Bool) -> [a] -> [[a]]
groupByPredicate func [] = []
groupByPredicate func xs | (checkFirst func xs) = [customTakeWhile (func) (xs)] ++ groupByPredicate (not.func) (drop (getNumberTaken (func) (xs)) (xs)) 
                         | otherwise = [customTakeWhile (not.func) (xs)] ++ groupByPredicate (func) (drop (getNumberTaken (not.func) (xs)) (xs))

-- function to check the first value of a list to determine grouping pattern 
checkFirst :: (a -> Bool) -> [a] -> Bool
checkFirst func [] = True
checkFirst func (x:xs) = func x

-- getting the number taken from take while so that they can used to drop those values from the list
getNumberTaken :: (a -> Bool) -> [a] -> Int
getNumberTaken func xs = length(takeWhile (func) (xs))

-- using my own custom takewhile function
customTakeWhile :: (a -> Bool) -> [a] -> [a]
customTakeWhile func []  = []
customTakeWhile func (x:xs) | (func x) = [x] ++ customTakeWhile func xs
                            | otherwise = []

-- Question 3: Movie Questions, should redo a few of these with map, filter, lambda
-- definition for Movie
data Movie = Movie { title :: String, rating :: Float, genre :: String } deriving Show

-- writing out the list of movies to use for testing
movies :: [Movie]
movies = [  Movie "Inception" 8.8 "Sci-Fi", 
            Movie "The Matrix" 8.7 "Sci-Fi", 
            Movie "Jaws" 7.9 "Thriller", 
            Movie "Frozen" 7.4 "Animation", 
            Movie "Interstellar" 8.6 "Sci-Fi", 
            Movie "The Godfather" 9.7 "Crime", 
            Movie "Toy Story" 8.3 "Animation"]

-- using list comprehension with the requirement that the rating must be higher than a given score, and then taking the title of that movie
topRatedMovies :: [Movie] -> Float -> [String]
topRatedMovies mlist score = [title x | x <- filter ((\x -> (rating (x) > score))) (mlist)]

-- adding the title of a movie given that the genre is a match
moviesByGenre :: [Movie] -> String -> [String]
moviesByGenre mlist mgenre = [title x | x <- filter ((\x -> (genre (x) == mgenre))) (mlist)]

-- helper function to update rating, uses guards to keep rating from going above 10.0
updateRating:: Float -> Float
updateRating x | (x + 0.5 < 10.0) = x + 0.5
               | otherwise = 10.0

-- adding a movie to a list that shares all the same values as the input movies, the only difference being a bump in ratings
adjustedRatings :: [Movie] -> [Movie]
adjustedRatings mlist = map (\x -> Movie (title x) ( (updateRating.rating) x) (genre x)) (mlist)

-- Question 4: Merge Sort

-- function to get halfway index of a list
getHalf:: Int -> Int
getHalf x = round(fromIntegral(x)/2)

-- actual merge sort function, which splits lists in half using take and drop recursive until size 1 lists are achieved
-- which are then recursively merged and sorted using the merge function
mergeSort:: Ord a => [a] -> [a]
mergeSort x | (length(x) <= 1) = x -- base case where list is either size one or empty
mergeSort x = merge (mergeSort (take (getHalf (length x)) x)) (mergeSort (drop (getHalf (length x)) x)) -- get first half using take
                                                                             -- and then drop those elements for the second argument


-- merging two lists so that they appear in ascending order, using recursion
merge:: Ord a => [a] -> [a] -> [a]
merge [] [] = []                                            -- if both lists are empty, done
merge (x:xs) [] = [x] ++ merge (xs) []                      -- if one is empty, continue to add the elements of the other
merge [] (y:ys) = [y] ++ merge [] (ys)
merge (x:xs) (y:ys) | (x < y)   = [x] ++ merge (xs) (y:ys)  -- if neither are empty, add the smallest head of each list
                    | otherwise = [y] ++ merge (x:xs) (ys)
