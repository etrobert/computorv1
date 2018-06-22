main = interact computorv1

parse_input :: (Num a) => String -> Equation a
parse_input _ = Equation [1, 0, 1]

computorv1 :: String -> String
computorv1 s = show $ solve $ parse_input s

data Equation a = Equation [a]

solve :: (Num a, Fractional a) => Equation a -> [a]
solve (Equation [0])        = [] -- TODO Everything is good
solve (Equation (_:[]))     = [] -- There are no solutions
solve (Equation (x:y:[]))   = [(-x)/y]
solve (Equation (x:y:z:[])) = solve3 (x, y, z)
solve (Equation _)          = [] -- TODO Can not handle

-- TODO
solve3 :: (Num n, Fractional n) => (n, n, n) -> [n]
solve3 (a, b, c) =
  let disc = b * b - 4 * a * c
  in [- b / ( 2 * a )]
