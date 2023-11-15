def generate_primes(n):
    primes = []
    for possiblePrime in range(2, n + 1):
        isPrime = True
        for num in range(2, int(possiblePrime ** 0.5) + 1):
            if possiblePrime % num == 0:
                isPrime = False
        if isPrime:
            primes.append(possiblePrime)
    return primes

def relate_power_to_primes(power_percentages, primes):
    for i, power in enumerate(power_percentages):
        if i < len(primes):
            print(f"Power output: {power}% --> Related prime: {primes[i]}")
        else:
            print(f"Power output: {power}% --> No related prime (not enough primes)")

# Generate a list of prime numbers up to 100
primes = generate_primes(100)

# Example power output percentages (replace this with your actual data)
power_output_percentages = [90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5]

# Relate the power output percentages to the list of primes
relate_power_to_primes(power_output_percentages, primes)
