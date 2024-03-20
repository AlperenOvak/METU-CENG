--Eliminate consecutive duplicates of list elements.

compress [] = []
compress [a] = [a]
compress (v:r:rest) | v == r = compress (v:rest)
                    | otherwise = v:(compress (r:rest))

main = do
    let myList = [2,3,3,5,5,3,3,3,2]
    print (compress myList)
