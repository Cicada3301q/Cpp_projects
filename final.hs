
module Final where 
--Author Quenten Welch 30054505
--Question 1.


--A binary relation over Integer can be represented as a list of Integer pairs
type Binrel = [(Integer, Integer)]
bin_rel_comp :: Binrel -> Binrel -> Binrel
-- function uses list comprehension in order to creat a list  of of Binrels (x, z) by first pulling pairs from br1 and if the second element of 
-- the pair from br1 "x" is equal to the first element  in the pair from br2 "z" then the pair (x,z) is added to the output. 
bin_rel_comp br1 br2 = [(x, z) | (x, y) <- br1, (w, z) <- br2, y == w]


--Question 2
--helper function 

type BitVec = [Bool]

--helper function to ensure that input lists are the same length, if not padding False to the list as x + false = x 
sameLength :: BitVec -> BitVec -> (BitVec, BitVec)
sameLength (x:xs) (y:ys) 
    | length xs < length ys = sameLength((x:xs)++(replicate (length ys - length xs) False)) (y:ys)
    | length xs > length ys = sameLength(x:xs) (y:ys ++(replicate (length xs - length ys) False))
	| otherwise = ((x:xs),(y:ys))

--helper function for determining results of singleton lists ie boolean logic table with the exception of True
-- as this will need to result in false with a True carry ie 1 + 1 = 10 
halfAdder :: Bool -> Bool -> Bool
halfAdder True False  = True
halfAdder False True  = True
halfAdder True True   = False
halfAdder False False = False


-- in case of same significant bit on both vectors being True, genorates a carry 
carryBool :: Bool -> BitVec -> BitVec -> BitVec
carryBool carry [] [] | carry == True = [True]
					  | otherwise = [] 
carryBool carry (x:xs) (y:ys) 
    | x && y = carry : carryBool True xs ys
    | otherwise = carry : carryBool False xs ys

-- recursively bitsums both inputs, making them the same length if needed to ensure significant digits are maintained
-- adds elements of inputs one at a time, if carry is true appends to the end of the current result, 
addbv :: BitVec -> BitVec -> BitVec
addbv bv bv2 
    | or bv = addbv carry res
    | otherwise = bv2 where
			res = zipWith halfAdder y x
			(y,x)  = sameLength bv bv2
			carry  = carryBool False y x
			
			
--Question 4
type VarName = Char


data Expr = Lit Integer
          | Var VarName
          | Add Expr Expr


ex :: Expr
ex = Add (Add (Var 'x') (Lit 3)) (Var 'y')


type Binding = (VarName, Expr)
type Substitution = [Binding]

sub :: Substitution
sub = [('x', Lit 7), ('y', Var 'z'), ('z', Lit 0)]

--uses pattern matching to determine input type, on case of Add, recursively calls itself to make appropriate substition for ex1, ex2
-- on case of Var, use of list comprehension to match against the head of each pair in sub against the input 
substitute :: Substitution -> Expr -> Expr
substitute sub (Add ex1 ex2) = Add (substitute sub ex1) (substitute sub ex2)
substitute sub (Var v) = head [ex | (vn, ex) <- sub, v==vn]
substitute sub exp = exp


--helper function provided in exam
showExpr :: Expr -> String
showExpr (Lit n) = "(Lit " ++ (show n) ++ ")"
showExpr (Var name) = "(Var " ++ (show name) ++ ")"
showExpr (Add e1 e2) = "(Add " ++ (showExpr e1) ++ " " ++ (showExpr e2) ++ ")"

--helper function provided in exam
showSub :: Substitution -> String
showSub [] = "[]"
showSub ((ch, e):ss) =
    "[(" ++ (show ch) ++ ", " ++ (showExpr e) ++ ")" ++
    (concat [", (" ++ (show ch2) ++ ", " ++ (showExpr e2) ++ ")" |
             (ch2, e2) <- ss]) ++
    "]"
			
			
			
--Question 6a
--helper function that sums all elements of a list
sumList :: [Int] -> Int
sumList []  = 0
sumList (x:xs) = x + sumList xs 

--helper function that squared an input
square :: Int -> Int
square x = x * x

--first filter returns a list of even numbers from the input, map applies square to each element of newly created list of even numbers
-- sum adds the list of squared even numbers
sum_sq_even :: [Int] -> Int
sum_sq_even xs = sumList (map square (filter even xs)) 
			
			
			
--Question 6b.
--helper function returns the last element of a list 
newHead :: [Int] -> Int
newHead = foldl1 (\_ x-> x) 

--uses newHead to append last element to input, calls init to remove last element from input. 
bubble_up ::[Int] ->[Int]
bubble_up [] = []
bubble_up xs = [newHead xs] ++ init xs

--Question 6c. 


			
crunch :: [Integer] -> [Integer] -> Integer
crunch [] []     = 0
crunch (x:xs) [] = crunch xs [x]
crunch [] (y:ys) = y + crunch [] ys
crunch (x:xs) (y:ys)
  | even x       = crunch xs (x:y:ys)
  | otherwise    = crunch ((x+y):xs) ys
  
  
  --Question 7
--type BitVec = [Bool]


elegant :: [BitVec]
elegant = [[True], [False]] ++ smap elegant

smap :: [BitVec] -> [BitVec]
smap [] = []
smap (x:xs) = [False:(x++[False])] ++ [True:(x++[True])] ++ smap xs
		
		
		