myButLast [] = error "Empty list"
myButLast [a] = a
myButLast (v:[a]) = v
myButLast (v:rest) = myButLast rest

myButLast'= head . reverse .init
myButLast'' = last .init
myButLast''' =  head . tail . reverse

myButLast'''' x = reverse x !! 1

main = do
    let myList = [1,2,5,4,6]
        empty = []
    print (myButLast'''' myList)