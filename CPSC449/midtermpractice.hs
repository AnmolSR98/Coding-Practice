-- lambda function practice
addOne :: [Int] -> [Int]
addOne xs = [(\n -> n + 1) x | x <- xs]

-- map function 
myMap :: [Int] -> [Int]
myMap xs = [x | x <- xs, someFunc(x)]
    where   
        someFunc :: Int -> Bool
        someFunc x = True