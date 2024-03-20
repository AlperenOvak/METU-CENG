--Problem 6
--(*) Find out whether a list is a palindrome.

isPalindrome [ ] = True
isPalindrome [_] = True
isPalindrome (x:xs)
    | x == last xs = isPalindrome (tail (reverse xs))
    | otherwise = False

main = do
    let myList = [ 2,3,5,3 ,2]
    print (isPalindrome myList)
