{-# OPTIONS_GHC -Wall #-}
module LogAnalysis where
import Log
import Data.Maybe
import Data.Char

safeGet :: [String] -> Int -> String
safeGet strs n = if (length strs) < n + 1 then "" else strs!!n

isNum :: String -> Bool
isNum "" = False
isNum (c:"") = isNumber c
isNum (c:cs) = isNumber c && isNum cs

parseMessageType :: String -> ((Maybe MessageType), String)
parseMessageType "" = (Nothing, "")
parseMessageType str
    | name == "I" = ((Just Info), left)
    | name == "W" = ((Just Warning), left)
    | name == "E" && isNum eno = ((Just (Error (read eno))), left')
    where
        stream = words str
        name = safeGet stream 0
        left = unwords (drop 1 stream)
        eno = safeGet stream 1
        left' = unwords (drop 2 stream)
parseMessageType str = (Nothing, str)

parseMessage :: String -> LogMessage
parseMessage str = if isNothing mType || not (isNum time)
    then Unknown str
    else LogMessage (fromJust mType) (read time) message
    where
        mType = fst (parseMessageType str)
        left = (words.snd.parseMessageType) str
        time = safeGet left 0
        message = unwords (drop 1 left)
        
parse :: String -> [LogMessage]
parse str = parse' strs []
    where
        strs = lines str
        parse' :: [String]->[LogMessage]->[LogMessage]
        parse' [] logs = logs
        parse' (s:ss) logs = parse' ss (logs ++ [parseMessage s])

messageTime :: LogMessage -> Maybe TimeStamp
messageTime (Unknown _) = Nothing
messageTime (LogMessage _ t _) = Just t 

insert :: LogMessage -> MessageTree -> MessageTree
insert (Unknown _) node = node
insert mes Leaf = Node Leaf mes Leaf
insert mes (Node left curMes right) 
    | time < curTime = Node (insert mes left) curMes right
    | time > curTime = Node left curMes (insert mes right)
    where
        time = messageTime mes
        curTime = messageTime curMes
insert _ node = node

build :: [LogMessage] -> MessageTree
build logs = build' logs Leaf
    where
        build' :: [LogMessage] -> MessageTree -> MessageTree
        build' [] tree = tree
        build' (l:ls) tree = build' ls (insert l tree)

inOrder :: MessageTree -> [LogMessage]
inOrder Leaf = [] 
inOrder (Node left mes right) = (inOrder left) ++ [mes] ++ (inOrder right)

whatWentWrong :: [LogMessage]->[String]
whatWentWrong [] = []
whatWentWrong ((LogMessage (Error n) _ mes):ls)
    | n >= 50 = [mes] ++ (whatWentWrong ls)
whatWentWrong (_:ls) = whatWentWrong ls
