
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
groupByPredicate :: (a -> Bool) -> [a] -> [a]
groupByPredicate func xs = [x | x <- xs, func (x)]

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

-- (\x = x + 0.5) (rating x)


