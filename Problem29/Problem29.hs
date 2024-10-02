
import Data.List (nub)

generatePowers aMin aMax bMin bMax = [ a^b | a<-[aMin..aMax], b<-[bMin..bMax]]

solution = length $ nub $ generatePowers 2 100 2 100
