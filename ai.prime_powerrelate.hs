import Data.List

-- Function to check if a number is prime
isPrime :: Int -> Bool
isPrime n = null [x | x <- [2..n - 1], n `mod` x == 0]

-- Function to generate primes up to n
generatePrimes :: Int -> [Int]
generatePrimes n = [x | x <- [2..n], isPrime x]

-- Function to relate power to primes
relatePowerToPrimes :: [Int] -> [Int] -> IO ()
relatePowerToPrimes [] _ = return ()
relatePowerToPrimes _ [] = return ()
relatePowerToPrimes (p:ps) (r:rs) = do
    putStrLn ("Power output: " ++ show p ++ "% --> Related prime: " ++ show r)
    relatePowerToPrimes ps rs

-- Generate a list of prime numbers up to 100
let primes = generatePrimes 100

-- Example power output percentages (replace this with your actual data)
let powerOutputPercentages = [90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5]

-- Relate the power output percentages to the list of primes
relatePowerToPrimes powerOutputPercentages primes
