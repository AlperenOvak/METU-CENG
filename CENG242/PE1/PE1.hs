module PE1 where

-- Question 1
findInList :: (Eq a) => [a] -> [a] -> [Int]
-- findInList _ _ = []
findInList a b = findListIndex a b 0

findListIndex :: (Eq a) => [a] -> [a] -> Int -> [Int]
findListIndex [] _ _ = []
findListIndex (a:l) (b:r) c | a == b = (c : findListIndex l r (c+1))
                            | otherwise = findListIndex (a:l) r (c+1)

-- Question 2
findInMatrix :: (Eq a) => [[a]] -> [[a]] -> [[(Int, Int)]]
findInMatrix [] _ = []
findInMatrix r l =
    let 
        result = traversee l r
    in   
        createMatrix [] result


addValueToNestedList :: [[a]] -> Int -> a -> [[a]]
addValueToNestedList nestedList i value
    | i >= length nestedList = nestedList ++ [[value]] -- If i is out of range, return the original nested list
    | otherwise = take i nestedList ++ [newValue] ++ drop (i+1) nestedList
    where newValue = (nestedList !! i) ++ [value]  -- Append the value to the i-th list and store it in newValue

--
diagonal :: Int -> Int  -> [(Int, Int)]
diagonal n m= 
    let 
        -- Function to generate diagonal elements starting from a given column and row
        diagonalFrom startCol startRow =
            if startCol < 0 || startRow >= n
                then []
                else (startRow, startCol) : diagonalFrom (startCol - 1) (startRow + 1)
        
        -- For each column, generate diagonal elements starting from row 0
        diagonalCols = [diagonalFrom col 0 | col <- [0..(m-1)]]
        
        -- For each row, generate diagonal elements starting from last column
        diagonalRows = [diagonalFrom (m-1) row | row <- [1..(n-1)]]
    in
        concat diagonalCols ++ concat diagonalRows

traversee l r = 
    let 
        matrix = diagonal (length l)  (length (head l) )
        subcheck = diagonal (length r) (length (head r) )

        -- Print statements to display matrix and subcheck
        
    in 
        checker matrix subcheck l r

--checker :: Eq a => [(Int, Int)] -> [(Int, Int)] -> [[a]] -> [[a]] -> [(Int, Int)]
checker :: Eq a => [(Int, Int)] -> [(Int, Int)] -> [[a]] -> [[a]] -> [(Int, Int, Int)]
checker [] _ _ _= [] -- Base case when the first list is empty
checker _ [] _ _= [] -- Base case when the second list is empty
--checker ((m,n):matrix) ((i,j):subcheck) nested sub  
--    | (nested !! m !! n) == (sub !! i !! j) = (m,n) : checker matrix subcheck nested sub -- If the elements match, include the element in the result and continue checking
--    | otherwise = checker matrix ((i,j):subcheck) nested sub-- If the elements don't match, continue checking without including the element

checker ((m,n):matrix) ((i,j):subcheck) nested sub = do
    if (nested !! m !! n) == (sub !! i !! j)
        then (m, n, i) : checker matrix subcheck nested sub 
        else checker matrix ((i, j):subcheck) nested sub

createMatrix a [] = a         
createMatrix newM ((m,n,j):flatten) =
    createMatrix (addValueToNestedList newM j (m,n)) flatten

main :: IO ()
main = do
    let l =  [[1,2,3,4],[1,2,3,4],[5,6,7,8]]
        r = [[1,5],[3,4]]
        result = traversee l r
        resultt = createMatrix [] result
        resulttt = findInMatrix r l
    
    print resulttt
