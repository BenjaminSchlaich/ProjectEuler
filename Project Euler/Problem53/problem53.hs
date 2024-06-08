
import Useful

solution = length [(n, k) | n<-[1..100], k<-[0..n], binCoeff n k > 10^6]
