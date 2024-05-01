module PE3 where

data Expression = Variable String 
    | Constant Float
    | Sine Expression
    | Cosine Expression
    | Negation Expression
    | Addition Expression Expression
    | Multiplication Expression Expression

class Differential a where
    diff :: a -> a -> a

instance Show Expression where
    show (Variable x) = "Variable '" ++ x ++ "'"
    show (Constant c) = "Constant " ++ show c
    show (Sine expr) = "sin " ++ show expr
    show (Cosine expr) = "cos " ++ show expr
    show (Negation expr) = "-" ++ show expr
    show (Addition expr1 expr2) = "(" ++ show expr1 ++ " + " ++ show expr2 ++ ")"
    show (Multiplication expr1 expr2) = "(" ++ show expr1 ++ " * " ++ show expr2 ++ ")"

instance Eq Expression where
    (==) (Variable a) (Variable b) = a == b
    (==) (Constant c) (Constant d) = c == d
    (==) (Negation exprA) (Negation exprB) = exprA == exprB
    (==) (Sine exprA) (Sine exprB) = exprA == exprB
    (==) (Cosine exprA) (Cosine exprB) = exprA == exprB
    (==) (Addition expr11 expr12) (Addition expr21 expr22) = (expr11 == expr21 && expr12==expr22)
    (==) (Multiplication expr11 expr12) (Multiplication expr21 expr22) = (expr11 == expr21 && expr12==expr22)
    (==) _ _ = False

instance Num Expression where
    fromInteger x = Constant (fromInteger x)
    (*) _ (Constant 0.0) = Constant 0.0
    (*) (Constant 0.0) _ = Constant 0.0
    (*) (Constant 1.0) expr = expr
    (*) expr (Constant 1.0) = expr
    (*) expr1 expr2 = Multiplication expr1 expr2
    (+) (Constant 0.0) expr = expr
    (+) expr (Constant 0.0) = expr
    (+) expr1 expr2 = Addition expr1 expr2
    negate (Constant c) = Constant (-c)
    negate expr = Negation expr
    abs (Constant c) 
        | c > 0 = (Constant c) 
        | otherwise = (Constant (-c)) 
    abs (Negation (Constant c)) = (Constant c)
    signum (Constant c) 
        | c>0 = Constant 1
        | c==0 = Constant 0
    signum (Negation (Constant c)) = -1


instance Differential Expression where
    diff (Constant _) _ = Constant 0  -- Constant: Derivative of a constant is always zero
    diff (Variable v) (Variable dv)
        | v == dv = Constant 1  -- Variable: Derivative of a variable with respect to itself is 1
        | otherwise = Constant 0
    diff (Sine expr) (Variable dv) = Multiplication (Cosine expr) (diff expr (Variable dv))
    diff (Cosine expr) (Variable dv) = Multiplication (Negation (Sine expr)) (diff expr (Variable dv))
    diff (Negation expr) (Variable dv) = Negation (diff expr (Variable dv))
    diff (Addition lhs rhs) (Variable dv) = Addition (diff lhs (Variable dv)) (diff rhs (Variable dv))
    diff (Multiplication lhs rhs) (Variable dv) = Addition (Multiplication (diff lhs (Variable dv)) rhs) (Multiplication lhs (diff rhs (Variable dv)))


newreverse :: [a] -> [a]
newreverse [] = []
newreverse (a : rest) = newreverse rest ++ [a]

shuntingyard :: [String] -> [String] -> [String] -> [String]
shuntingyard [] [] a = newreverse a

shuntingyard [] (b:st) a = shuntingyard [] st (b:a)
--TO DO for empty stack
shuntingyard (v:list) [] a 
    | v == "-" || v=="sin" || v=="cos" || v=="*" || v=="+" || v=="("  = shuntingyard list [v] a
    | otherwise = shuntingyard list [] (v:a)
shuntingyard (v:list) (b:st) a 
    | v == "-" =
        if b == "-" 
            then shuntingyard (v:list) st (b:a)  
            else shuntingyard list (v:b:st) a
    | v == "sin" =
        if b == "-" || b == "sin" || b == "cos"
            then shuntingyard (v:list) st (b:a) 
            else shuntingyard list (v:b:st) a
    | v == "cos" =
        if b == "-"
            then shuntingyard (v:list) st (b:a) 
            else shuntingyard list (v:b:st) a
    | v == "*"
        = if b == "-" || b == "sin" || b == "cos" || b == "*"
            then shuntingyard (v:list) st (b:a) 
            else shuntingyard list (v:b:st) a
    | v == "+"
        = if b == "-" || b == "sin" || b == "cos" || b == "*" || b == "+"
            then shuntingyard (v:list) st (b:a) 
            else shuntingyard list (v:b:st) a
    | v == "(" = shuntingyard list (v:b:st) a
    | v == ")"
        = if b == "-" || b == "sin" || b == "cos" || b == "*" || b == "+"
            then shuntingyard (v:list) st (b:a) 
            else shuntingyard list st a
    | otherwise = shuntingyard list (b:st) (v:a)




tokenize :: String -> [String]
tokenize = words
main = do
    let input = "( a + b ) * ( ( - a + 9 ) * - c * ( sin a + cos c ) )"
    let tokens = tokenize input


    --print $ shuntingyard tokens [] []