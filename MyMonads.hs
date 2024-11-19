
data LogNumT a = LogNum  {
                         value :: a
                        ,log :: [String]
                        }

instance Functor LogNum where
    (<*>) = undefined
    liftA2 = undefined
    (*>) = undefined
    (<*) = undefined

--{-
instance Monad LogNumT where
    (>>=) (LogNum v l) f = LogNum newV (newL++l)
        where LogNum newV newL = f v
--}