elementAt [] _ = error "index out of range"
elementAt (v:rest) x | x < 1 = error "index out of range"
                     | x == 1 = v
                     | otherwise = elementAt rest (x-1)

                     

main = do
    let myList = [1,2,5,4,6]
        empty = []
    print (elementAt myList (-1))