--findInMatrix :: (Eq a) => [[a]] -> [[a]] -> [[(Int, Int)]]
--findInMatrix [] _ = []
--findInMatrix r l =
--    let 
--        result = finderMatrix l r (0,0) (0,0)
--    in   
--        createMatrix [] result
--
--
--addValueToNestedList :: [[a]] -> Int -> a -> [[a]]
--addValueToNestedList nestedList i value
--    | i >= length nestedList = nestedList ++ [[value]] -- If i is out of range, return the original nested list
--    | otherwise = take i nestedList ++ [newValue] ++ drop (i+1) nestedList
--    where newValue = (nestedList !! i) ++ [value]  -- Append the value to the i-th list and store it in newValue
--createMatrix a [] = a         
--createMatrix newM ((m,n,j):flatten) =
--    createMatrix (addValueToNestedList newM j (m,n)) flatten
--
--
--nextItem matrix (i,j)= 
--    let n = length matrix
--        m = length (head matrix)
--        diagonalFrom i j =
--            if (i == n -1 && j == m-1)
--                    then (-1,-1)
--                    else if  i >= n-1 || j == 0 -- bottom border
--                        then if i+j >= m-1 -- go down
--                            then (i+j-m+2,m-1) 
--                            else (0,i+j+1)
--            else 
--                (i+1,j-1) 
--    in
--        diagonalFrom i j
--
--finderMatrix l r (i,j) (k,m) =
--    if (i > -1 && j > -1 && k > -1 && m > -1)
--        then if ((l !! i !! j) == (r !! k !! m))
--                 then (i,j,k):finderMatrix l r (nextItem l (i,j)) (nextItem r (k,m))
--                 else finderMatrix l r (nextItem l (i,j)) (k,m)
--    else 
--        []
--
--main :: IO ()
--main = do
--    let l =  [[1,2,3,4],[5,6,7,9],[9,10,11,12],[8,14,15,13]]
--        r = [[1,6,8],[7,9,13]]
--
--        result = finderMatrix l r (0,0) (0,0)
--    
--
--    print result


trd :: (a, b, c) -> c
trd (_, _, x) = x

fr :: (a, b, c) -> a
fr (x, _, _) = x

sc :: (a, b, c) -> b
sc (_, x, _) = x

makelist :: [[c]] -> Int -> Int -> Int -> Int -> [(Int, Int, c)]
makelist matrix row column row_max column_max
    | row == row_max && column == column_max = []
    | column == column_max = makelist matrix (row+1) (column-1) row_max column_max
    | otherwise = traversedia matrix row column row_max ++ makelist matrix row (column+1) row_max column_max

traversedia :: [[c]] -> Int -> Int -> Int -> [(Int, Int, c)]
traversedia matrix row column row_max
    | row == row_max || column < 0 = []
    | otherwise = (row, column, matrix !! row !! column) : traversedia matrix (row+1) (column-1) row_max
    
comparex [] _ = []
comparex ((a,b,c):rest) ((d,e,f):resx)
    |c == f = (a,b,d):comparex rest resx
    |otherwise = comparex ((a,b,c):rest) resx
    

main :: IO ()
main = do
    let result = makelist [[1,2,3,4],[1,2,3,4],[5,6,7,8]] 0 0 3 4
        x = makelist [[1,5],[3,4]] 0 0 2 2
        y = comparex x result
    print y