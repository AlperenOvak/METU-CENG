module PE2 where

data Tree k v = EmptyTree | Node k v [Tree k v] deriving (Show, Eq)

-- Question 1
selectiveMap :: (a -> Bool) -> (a -> a) -> [a] -> [a]
selectiveMap boolf func [] = []
selectiveMap boolf func (v:right) | boolf v  = (func v :selectiveMap boolf func right) 
                                  | otherwise = (v : selectiveMap boolf func right)
-- Question 2
tSelectiveMap :: (k -> Bool) -> (v -> v) -> Tree k v -> Tree k v
tSelectiveMap _ _ EmptyTree = EmptyTree
tSelectiveMap boolf func (Node k v children) | boolf k = Node k (func v) (map (tSelectiveMap boolf func) children)
                                             | otherwise = Node k v (map (tSelectiveMap boolf func) children)


-- Question 3
tSelectiveMappingFold :: (k -> Bool) -> (k -> v -> r) -> (r -> r -> r) -> r -> Tree k v -> r
tSelectiveMappingFold _ _ _ idt EmptyTree = idt 
tSelectiveMappingFold predicate mapper combiner acc (Node key value children)
    | predicate key = let mappedValue = mapper key value
                          childrenFolded = foldr (\child accum -> tSelectiveMappingFold predicate mapper combiner accum child) acc children
                      in combiner mappedValue childrenFolded
    | otherwise     = foldr (\child accum -> tSelectiveMappingFold predicate mapper combiner accum child) acc children



-- Question 4
finder defo EmptyTree _ = defo
finder defo (Node k v children) wanted | wanted == k = v
                                       | otherwise = foldr (\child defos -> finder defos child wanted) defo children


combinerY x y = y
combinerX x y = x
truee :: a -> Bool
truee _ = True

ali 3 = 5
ali 6 = 8

funcc [] def k = def
--funcc ((\x -> y):rest) def k | x==k = y 
--                             | otherwise = funcc rest def k

funcc ((func):rest) def k | func k == def = funcc rest def k
                          | otherwise = func k

f def k v key | k==key = v
              | otherwise = def

com def func1 func2 k | func1 k == def = func2 k 
                      | otherwise = func1 k

--and (func y) (func1 z) = (\x -> if x==y then (func y) else if x==z then (func1 z))

--outerFunction :: Int -> Int
--outerFunction x = innerFunction x
--  where
--    --innerFunction :: Int -> Int -> Int
--    innerFunction x = (\3 -> x*3)

--veli x y = and (\y -> x) (\x -> y)

searchTree :: (Eq v, Eq k) => v -> Tree k v -> (k -> v)
searchTree def = tSelectiveMappingFold a b c d
    where a = (truee)
          b = f def
          c = com def
          d = const def

