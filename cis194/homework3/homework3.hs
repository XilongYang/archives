--original

skips :: [a] -> [[a]]
skips xs = map (skip xs) [1,2..length xs]
    where
        skip :: [a] -> Int -> [a]
        skip xs i = map (xs !!) (filter right [0..length xs - 1])
            where
                right :: Int -> Bool
                right x = (x + 1) `mod` i == 0

-- lambda

skips' :: [a] -> [[a]]
skips' xs = map (skip xs) [1,2..length xs]
    where
        skip :: [a] -> Int -> [a]
        skip xs i = map (xs !!) (filter (\x -> (x + 1) `mod` i == 0) 
            [0,1..length xs - 1])

-- list comprehension

skips'' :: [a] -> [[a]]
skips'' xs = map (skip xs) [1,2..length xs]
    where
        skip :: [a] -> Int -> [a]
        skip xs i = [xs !! (n - 1) | n<-[1,2..length xs], n `mod` i == 0]

localMaxima :: [Integer] -> [Integer]
localMaxima xs = if length xs < 3 then []
    else [xs !! n | n<-[1,2..length xs - 2], (xs !! n) > (xs !! (n - 1))
        && (xs !! n) > (xs !!(n + 1))] 

histogram :: [Integer] -> String
histogram xs = unlines (stars xs) ++ "==========\n0123456789\n"
    where
        stars :: [Integer]->[String]
        stars xs = map (star xs) [maxCount xs, (maxCount xs) - 1..1]
            where
                maxCount :: [Integer] -> Int
                maxCount xs = maximum (counts xs)
                star :: [Integer] -> Int -> String
                star xs i = map (moreThan xs i) "0123456789"
                    where
                        moreThan :: [Integer] -> Int -> Char -> Char
                        moreThan xs i c = if((counts xs)!!(read [c])) >= i then '*' else ' '
                counts :: [Integer] -> [Int]
                counts xs = map (count xs) [0,1..9]
                    where
                        count :: [Integer] -> Int -> Int
                        count xs i = length [x | x<-xs, fromInteger(x) == i]