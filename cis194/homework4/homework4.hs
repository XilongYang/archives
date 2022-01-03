fun1 :: [Integer] -> Integer
fun1 [] = 1
fun1 (x:xs)
    | even x = (x - 2) * fun1 xs
    | otherwise = fun1 xs

fun1' :: [Integer] -> Integer
fun1' = (foldl (*) 1).(map (subtract 2)).(filter even)

fun2 :: Integer -> Integer
fun2 1 = 0
fun2 n | even n = n + fun2 (n `div` 2)
       | otherwise = fun2 (3 * n + 1)

fun2' :: Integer->Integer
fun2' = sum.(map (extend.transfrom)).(takeWhile (>1)).(iterate (next.transfrom))
    where
        transfrom :: Integer -> Integer
        transfrom = ((!!0).(filter even).(iterate (\n -> 3 * n + 1)))
        extend:: Integer -> Integer
        extend = sum.(takeWhile even).(iterate (`div` 2))
        next:: Integer -> Integer
        next = (!!0).(filter odd).(iterate (`div` 2))

data Tree a = Leaf
            | Node Integer (Tree a) a (Tree a)
    deriving (Show, Eq)

height :: Tree a -> Integer
height Leaf = -1
height (Node n _ _ _) = n;

isFill :: Tree a -> Bool
isFill Leaf = True
isFill (Node n left _ right) = 
    if (height left /= height right) then False
        else isFill left && isFill right

foldTree :: [a] -> Tree a
foldTree = foldr insert Leaf
    where
        insert :: a -> Tree a -> Tree a
        insert x Leaf = Node 0 Leaf x Leaf
        insert x (Node n left x' right) = 
            if (height left < height right) then Node n (insert x left) x' right
            else if (height left > height right) then Node n left x' (insert x right)
            else if (not (isFill left)) then Node n (insert x left) x' right
            else if (not (isFill right)) then Node n left x' (insert x right)
            else Node (n + 1) (insert x left) x' right

xor :: [Bool] -> Maybe Bool
xor [] = Nothing
xor (x:[]) = Nothing
xor (x:xs) = Just (foldl (\a b -> a /= b) x xs)

map' :: (a -> b) -> [a] -> [b]
map' f = foldr (\x ys -> [(f x)] ++ ys) []
-- map' f = foldl (\xs y -> xs ++ [(f y)]) []

myFoldl :: (a -> b -> a) -> a -> [b] -> a
myFoldl f base xs = foldr (\x y -> f y x) base xs

sieveSundaram :: Integer -> [Integer]
sieveSundaram = (filter even).extend
    where
        extend :: Integer -> [Integer]
        extend n = [n, n+1..2 * n + 2]
        isPrime :: Integer -> Bool
        isPrime n = length (filter (== 0) (map (n `mod`) [2,3..n - 1])) == 0
