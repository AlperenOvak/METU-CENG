myLast [] = error "No end for empty lists!"
myLast [x] = x
myLast (_:xs) = myLast xs


main :: IO ()
main = do
    let myList = [1, 2, 3, 4, 5]
        empty = []
    putStrLn $ "The last element of myList is: " ++ show (myLast myList)