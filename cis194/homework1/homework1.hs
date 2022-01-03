-- validateing credit card numbers
toDigits :: Integer->[Integer]
toDigits n 
    | n <= 0 = []
    | otherwise = toDigits(n `div` 10) ++ [n `mod` 10]

toDigitsRev :: Integer->[Integer]
toDigitsRev n = reverse (toDigits n)

doubleEveryOtherRev :: [Integer]->[Integer]
doubleEveryOtherRev [] = []
doubleEveryOtherRev [x] = [x]
doubleEveryOtherRev (x:y:ys) = [x, y*2] ++ doubleEveryOtherRev ys

doubleEveryOther :: [Integer]->[Integer]
doubleEveryOther = reverse.doubleEveryOtherRev.reverse

sumDigits :: [Integer]->Integer
sumDigits [] = 0
sumDigits [x]
    | x <= 0 = 0
    | x < 10 = x
    | otherwise = sumDigits (toDigits x)
sumDigits (x:xs) = sumDigits [x] + sumDigits xs

validate :: Integer->Bool
validate n
    | result == 0 = True
    | otherwise = False
    where result = (sumDigits.doubleEveryOther.toDigits) n `mod` 10

-- the towers of hanoi

type Peg = String
type Move = (Peg, Peg)

-- hanoi numOfDiscs->originPeg->targetPeg->otherPeg->moves
hanoi :: Integer->Peg->Peg->Peg->[Move]
hanoi 0 a b c = []
hanoi n a b c = hanoi (n - 1) a c b ++ [(a, b)] ++ hanoi (n - 1) c b a

hanoiPlus :: Integer->Peg->Peg->Peg->Peg->[Move]
hanoiPlus 0 _ _ _ _ = []
hanoiPlus n a b c d = hanoiPlus (left - k) a c b d
            ++ hanoi k a d b
            ++ [(a, b)]
            ++ hanoi k d b a
            ++ hanoiPlus (left - k) c b a d
    where   
        left = n - 1
        k = minimalDivide n

minimalDivide :: Integer->Integer
minimalDivide 0 = 0
minimalDivide n = head (minimalDivideList n)

minimalDivideList :: Integer->[Integer]
minimalDivideList 0 = []
minimalDivideList n = minimalDivideList' [1,2..n] []
    where
        minimalDivideList' :: [Integer]->[Integer]->[Integer]
        minimalDivideList' (x:xs) [] = minimalDivideList' xs [0]
        minimalDivideList' [] ys = ys
        minimalDivideList' (x:xs) (y:ys) = minimalDivideList' xs (cur:(y:ys))
            where
                --x-y <= 1会使hanoiPlus'死循环
                cur = if x - y <= 1 || hanoiPlus' x y <= hanoiPlus' x (y + 1)
                    then y else y + 1
                --跟据已知最优分割求出最小步数
                hanoiPlus' :: Integer->Integer->Integer
                hanoiPlus' 0 _ = 0
                hanoiPlus' n' divide = 
                    2 * hanoiPlus' left' divide'
                    + 2 * (2^divide - 1) 
                    + 1
                    where 
                        left' = n' - divide - 1
                        divide' = if left' == 0 then 0 else reverse (y:ys)!!fromInteger(left' - 1)

--check function
f :: Integer->Integer
f 1 = 1
f n = f (n-1) + 2^(floor (sqrt (fromInteger(8*n-7)) - 1) `div` 2)