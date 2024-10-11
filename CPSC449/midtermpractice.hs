-- lambda function practice
addOne :: [Int] -> [Int]
addOne xs = [(\n -> n + 1) x | x <- xs]

-- map function 
myMap :: (Int -> Int) -> [Int] -> [Int]
myMap someFunc xs = [someFunc x | x <- xs]