{-# LANGUAGE TypeSynonymInstances #-}
{-# LANGUAGE FlexibleInstances #-}

import ExprT
import Parser
import StackVM
import Data.Maybe
import Language.Haskell.TH (reifyInstances)
import System.Directory.Internal.Prelude (Integral(toInteger))
import GHC.Real (Integral(toInteger))
import qualified Data.Map as M

-- Exercise 1

eval :: ExprT -> Integer 
eval (ExprT.Lit x) = x
eval (ExprT.Add a b) = eval a + eval b
eval (ExprT.Mul a b) = eval a * eval b

-- Exercise 2

evalStr :: String -> Maybe Integer
evalStr s | (isNothing . parseExp ExprT.Lit ExprT.Add ExprT.Mul) s = Nothing 
evalStr s = (Just . eval . fromJust . parseExp ExprT.Lit ExprT.Add ExprT.Mul) s

-- Exercise 3

class Expr e where
    lit :: Integer -> e
    add :: e -> e -> e
    mul :: e -> e -> e

instance Expr ExprT where
    lit  = ExprT.Lit
    add  = ExprT.Add
    mul  = ExprT.Mul

reify :: ExprT -> ExprT
reify = id

-- Exercise 4

instance Expr Integer where
    lit x = x
    add = (+)
    mul = (*)

instance Expr Bool where
    lit = (>0)
    add = (||) 
    mul = (&&)

newtype MinMax = MinMax Integer deriving (Show, Eq)

instance Expr MinMax where
    lit = MinMax
    add (MinMax a) (MinMax b) = lit $ max a b
    mul (MinMax a) (MinMax b) = lit $ min a b

newtype Mod7 = Mod7 Integer deriving (Show, Eq)

instance Expr Mod7 where
    lit = Mod7
    add (Mod7 a) (Mod7 b) = lit $ (a + b) `mod` 7
    mul (Mod7 a) (Mod7 b) = lit $ (a * b) `mod` 7

testExp :: Expr a => Maybe a
testExp = parseExp lit add mul "(3 * -4) + 5"

testInteger = testExp :: Maybe Integer
testBool = testExp :: Maybe Bool
testMM = testExp :: Maybe MinMax
testSat = testExp :: Maybe Mod7

-- Exercise 5

instance Expr Program where
    lit x = [PushI x]
    add a b = a ++ b ++ [StackVM.Add]
    mul a b = a ++ b ++ [StackVM.Mul]

compile :: String -> Maybe Program 
compile = parseExp lit add mul

testProgram :: String -> Either String StackVal
testProgram = stackVM . fromJust . compile 

--Exercise 6

class HasVars e where
    var :: String -> e

data VarExprT = Lit Integer
    | Var String 
    | Add VarExprT VarExprT
    | Mul VarExprT VarExprT
    deriving(Show, Eq)

instance Expr VarExprT where
    lit = Main.Lit
    add = Main.Add
    mul = Main.Mul

instance HasVars VarExprT where
    var = Main.Var

instance HasVars (M.Map String Integer -> Maybe Integer) where
    var = M.lookup 

instance Expr (M.Map String Integer -> Maybe Integer) where
    lit i = \_ -> Just i
    add v1 v2 = \m -> if isNothing (v1 m) || isNothing (v2 m)
                      then Nothing 
                      else Just $ fromJust (v1 m) + fromJust (v2 m)
    mul v1 v2 = \m -> if isNothing (v1 m) || isNothing (v2 m)
                      then Nothing 
                      else Just $ fromJust (v1 m) * fromJust (v2 m)

withVars :: [(String, Integer)]
         -> (M.Map String Integer -> Maybe Integer)
         -> Maybe Integer
withVars vs exp = exp $ M.fromList vs