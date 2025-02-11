
import System.Random

-- the monopoly square names in clockwise order, starting from "GO"
squareNames :: [String]
squareNames = [ "GO","A1","CC1","A2","T1","R1","B1","CH1","B2","B3","JAIL"
                ,"C1","U1","C2","C3","R2","D1","CC2","D2","D3","FP"
                ,"E1","CH2","E2","E3","R3","F1","F2","U2","F3","G2J"
                ,"G1","G2","CC3","G3","R4","CH3","H1","T2","H2"]

-- the squareNames list, but with bars and whitespaces, s.t. the names are easily printable on a map
printableNames :: [String]
printableNames = map fmt squareNames
    where   fmt s = "| " ++ (replicate before ' ') ++ s ++ (replicate after ' ') ++ " |"
                where   before = (4 - length s) `div` 2
                        after = before + ((4 - length s) `mod` 2)

-- take an integer n a list l, and return a list of lists, each of which contains n consecutive integers of l in order.
groupN :: Int -> [a] -> [[a]]
groupN n l = grouping n l []
    where   grouping _ [] s = [reverse s]
            grouping 0 l full = reverse full : grouping n l []
            grouping n' (x:xs) s = grouping (n'-1) xs (x:s)

printableMap :: String
printableMap =      (concat $ take 11 printableNames) ++ interline
                ++  middles (take 9 $ drop 11 printableNames) (take 9 $ drop 31 printableNames)
                ++  (concat $ reverse $ take 11 $ drop 20 printableNames) ++ "\n"
    where   middles lr ll = concatMap middle $ zip (reverse ll) lr
            middle (a, b) = a ++ (replicate 72 ' ') ++ b ++ interline
            interline = "\n" ++ bars ++ (replicate 72 ' ') ++ bars ++ "\n"
            bars = "――――――――"

squareName :: Int -> String
squareName = ((!!) squareNames)

fieldId :: String -> Int
fieldId name = index squareNames 0
    where   index (n:ns) i = if n == name then i else index ns (i+1)

data State = State {
    position :: Int,
    counters :: [Int],
    turnCount :: Int,
    diceRolls :: [Int]
}

rolls n = drop 1 $ genRolls (0, mkStdGen 32) n
    where   genRolls (x, g) n = x : genRolls (uniformR (1, n) g) n

change :: Int -> (a -> a) -> [a] -> [a]
change i f l = take i l ++ [f (l!!i)] ++ (drop (i+1) l)

takeTurn :: State -> State
takeTurn (State p cs c (r:rs)) = State {
    position = (p + r) `mod` 40, counters = change (p+r-1) succ cs, turnCount = (succ c), diceRolls = rs
}

takeTurn :: State -> State
takeTurn (State p cs c (r:rs))
    | p' == 

takeTurns :: Int -> State -> State
takeTurns 0 s = s
takeTurns n s = takeTurns (n-1) (takeTurn s)

s0 :: State
s0 = State 0 (replicate 40 0) 0 (rolls 6)

pos :: State -> Int
pos (State p _ _ _) = p

solve :: Int -> Int -> [(String, Double)]
solve iter dice = zip squareNames $ map ((/ (fromIntegral iter)).fromIntegral) $ counts s1
    where   counts (State _ cs _ _) = cs
            s1 = takeTurns iter s0

prettySolution ::Int -> Int -> String
prettySolution iter dice = concatMap ((++ "\n").show) $ solve iter dice
