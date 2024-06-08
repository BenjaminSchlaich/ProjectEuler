
import Data.List (sort, find, sortBy, (\\))
import Data.Maybe (fromJust)
import Useful

data Color = Clubs | Spades | Hearts | Diamonds deriving (Eq, Show, Read)

type Card = (Color, Int)

instance {-# OVERLAPPING #-} Ord Card where
    compare (c1, v1) (c2, v2)   | v1 < v2 = LT
                                | v1 == v2 = EQ
                                | otherwise = GT

type Deck = [Card]

-- group cards by their values, ignoring the color
groupValues :: Deck -> [Deck]
groupValues = equivalenceClasses (\x y -> snd x == snd y)

-- returns the card with the highest value from the deck
highest :: Deck -> Card
highest = foldr max (Diamonds, 0)

-- returns the Just the sorted cards
msort :: Deck -> Maybe Deck
msort cs = Just $ sort cs

-- there are at least two different equivalence classes with each at least two cards in them? returns the highest paired card?
-- returns one of the cards from the highest pair
pair :: Deck -> Maybe Deck
pair cs = if null pairs then Nothing else Just ((last.sort.(map head)) pairs : (sort $ cs \\ (concat pairs)))
    where pairs = filter ((>= 2).length) $ groupValues cs

-- there are at least two different equivalence classes with each at least two cards in them? returns the paired cards, higher card first?
-- returns one card of each pair, the highest first
twoPairs :: Deck -> Maybe Deck
twoPairs cs = if length pairs < 2 then Nothing else Just $ (reverse.sort.(map head)) pairs
    where pairs = filter ((>= 2).length) $ groupValues cs

-- there is a equivalence class with four or more elements for the relation "equal value" on the deck of cards?
-- returns one of the cards making up the triplet
threeOfAKind :: Deck -> Maybe Deck
threeOfAKind cs = if null quadruple then Nothing else Just $ (head (fromJust quadruple)) : other
    where   quadruple = find ((== 3).length) $ groupValues cs
            other = if null quadruple then [] else sort $ cs \\ (fromJust quadruple)

-- there is a equivalence class with four or more elements for the relation "equal value" on the deck of cards?
-- returns some of the cards that make up the full house, the triplet value first, then the pair value
fullHouse :: Deck -> Maybe Deck
fullHouse cs = if null triple || null pair then Nothing else Just (map head [fromJust triple, fromJust pair])
    where   triple = (find ((== 3).length)) eqClasses
            pair = (find ((== 2).length)) eqClasses
            eqClasses = equivalenceClasses (\x y -> snd x == snd y) cs

-- there is a equivalence class with four or more elements for the relation "equal value" on the deck of cards?
-- returns one of the cards that makes up the quadruple.
fourOfAKind :: Deck -> Maybe Deck
fourOfAKind cs = if null quadruple then Nothing else Just $ (head (fromJust quadruple)) : other
    where   quadruple = find ((>= 4).length) $ groupValues cs
            other = if null quadruple then [] else (if length quadruple == 5 then [head $ fromJust quadruple] else cs \\ (fromJust quadruple))

-- all values are consecutive integers when sorted?
-- returns the highest of the cards
straight :: Deck -> Maybe Deck
straight cs = if straight sorted then Just sorted else Nothing
    where   sorted = sort cs
            straight [c] = True
            straight (c:cs) = snd c + 1 == snd (head cs) && straight cs

-- all cards have the same color (as the first card)
flush :: Deck -> Maybe Deck
flush l@((c, v):cs) = if all (== c) $ map fst cs then Just $ sort l else Nothing

-- straight and flush at the same time
straightFlush :: Deck -> Maybe Deck
straightFlush cs = if null (straight cs) || null (flush cs) then Nothing else msort cs

ranking :: [Deck -> Maybe Deck]
ranking = [straightFlush, fourOfAKind, fullHouse, flush, straight, threeOfAKind, twoPairs, pair, msort]

rankNames :: [String]
rankNames = ["straightFlush", "fourOfAKind", "fullHouse", "flush", "straight", "threeOfAKind", "twoPairs", "pair", "high card"]

-- test decks
testdeckStrings =
            [["2D", "3C", "4D", "5S", "6S"]     -- straight
            ,["5S", "6S", "7S", "8S", "9S"]     -- straight flush
            ,["2D", "2C", "2D", "1S", "3S"]     -- three of a kind
            ,["2D", "2C", "2D", "1S", "2S"]     -- four of a kind
            ,["2D", "2C", "2D", "2S", "2S"]     -- four of a kind
            ,["2D", "2C", "2D", "1S", "1S"]     -- full house
            ,["2D", "3D", "KD", "1D", "2D"]     -- flush
            ,["2D", "2C", "1D", "3S", "AD"]     -- pair
            ,["2D", "3C", "QD", "2S", "3S"]     -- two pairs
            ,["2D", "5C", "7D", "1S", "QS"]]    -- high card

testdecks = map parse testdeckStrings

findbest = best ranking rankNames
    where best (f:fs) (n:ns) cs | null $ f cs = best fs ns cs
                                | otherwise = n

testresults = map findbest testdecks

hgh :: Deck -> Deck -> Ordering
hgh [] [] = EQ
hgh [] _ = LT
hgh _ [] = GT
hgh (bc:bcs) (dc:dcs) = if compare bc dc == EQ then hgh bcs dcs else compare bc dc

instance {-# OVERLAPPING #-} Ord Deck where
    compare b d = cmp ranking b d
        where cmp (f:fs) b d    | null $ f b = if null $ f d then cmp fs b d else LT
                                | null $ f d = GT
                                | otherwise = hgh (fromJust $ f b) (fromJust $ f d)

-- mistake 1:
error11 :: Deck
error11 = parse $ words "2H 2D 4C 4D 4S"

error12 :: Deck
error12 = parse $ words "3C 3D 3S 9S 9D"

parse :: [String] -> Deck
parse = map prs
    where   prs (v:c:[]) = (prsC c, prsV v)
            prsV v  | v == 'A' = 14
                    | v == 'K' = 13
                    | v == 'Q' = 12
                    | v == 'J' = 11
                    | v == 'T' = 10
                    | otherwise = read (v:[]) :: Int
            prsC c  | c == 'C' = Clubs
                    | c == 'S' = Spades
                    | c == 'H' = Hearts
                    | c == 'D' = Diamonds

winningCards :: String -> [String]
winningCards strs = filter winning $ lines strs
    where winning str = d1 > d2
            where   d1 = parse $ take 5 ws
                    d2 = parse $ drop 5 ws
                    ws = words str

main = do
    contents <- readFile "Problem54/0054_poker.txt"
    putStrLn (show $ length $ winningCards contents)
