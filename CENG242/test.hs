-- comments

f x y = x*y

square::Integer->Integer
square x = x*x

ssum n = if n<=0 then
            0
        else 
            n + ssum (n-1)

sssum n | n<=0 = 0
        | otherwise = n + sssum (n-1)


fib 0 = 1
fib 1 = 1
fib n = fib (n-1)+fib(n-2)

fibb n i a b    | i==n = b
                | otherwise = fibb n (i+1) b (a+b)  

fib2 n = fibb n 1 1 1


poww x 0 = 1
poww x n | n `mod` 2 == 0 = poww (x*x) (div n 2) 
         | otherwise = poww (x*x) (div n 2)  * x


data Person = Person String Integer Bool

data WState = Sunny | PartClouds | Clouds | Rain | Snow deriving (Show,Eq)

data Value = Rat (Integer,Integer) | RV Float deriving Show
add :: Value -> Value -> Value

add (Rat (a,b)) (Rat(c,d)) = Rat(a*d+b*c,b*d)
add (Rat(a,b)) (RV f) = RV (f + (fromInteger a)/(fromInteger b))
add (RV f) (Rat(a,b)) = RV (f + (fromInteger a)/(fromInteger b))
add (RV g) (RV f) = RV (f+g)

toReal val = case val of
            RV v -> v
            Rat(a,b) -> ((fromInteger a)/(fromInteger b))


index _ [] = -1
index k (v:rest) | k == v = 0
                 | otherwise = case index k rest of     
                                -1 ->  -1
                                a ->  a+1 
                                
reversee [] = []
reversee (v:rest) = (reversee rest) ++ [v]

reverse2' [] new = new 
reverse2' (k:rest) new = reverse2' rest (k:new)

reverse2 list = reverse2' list []


isprefix [] _ = True
isprefix _ [] = False
isprefix (a:ra) (b:rb)  | a==b = isprefix ra rb
                        |  otherwise = False


issuffix [] [] = Just 0
issuffix _ [] = Nothing
issuffix ra rB@(b:rb) | isprefix ra rB = Just 0
                      | otherwise = case issuffix ra rb of 
                                    Nothing -> Nothing
                                    Just a -> Just (a+1)    
yesOrNo a b | True = case issuffix a b of 
                Nothing -> False
                Just a -> True
            | otherwise = False
                        
pset [] = [[]]
pset (v:rest) = let sub = pset rest
                in sub ++ [v:m | m <-sub]