import matplotlib.pyplot as plt
import math


class PrimeSieve:
    def __init__(self, limit):
        """Initialize sieve up to a given limit."""
        self.limit = limit
        self._sieve_primes()

    def _sieve_primes(self):
        """Generate primes using Eratosthenes' sieve."""
        sieve = [True] * (self.limit + 1)
        sieve[0:2] = [False, False]
        for i in range(2, int(self.limit**0.5) + 1):
            if sieve[i]:
                sieve[i * i : self.limit + 1 : i] = [False] * len(range(i * i, self.limit + 1, i))
        self.primes = [i for i, is_p in enumerate(sieve) if is_p]
        self.is_prime_lookup = sieve
        self.prime_to_index = {p: idx for idx, p in enumerate(self.primes)}

    def is_prime(self, n):
        """Return True if n is prime (only works up to limit)."""
        if 0 <= n <= self.limit:
            return self.is_prime_lookup[n]
        raise ValueError(f"Number {n} exceeds sieve limit {self.limit}")

    def prime_index(self, p):
        """Return the index (0-based) of a prime number."""
        if p in self.prime_to_index:
            return self.prime_to_index[p]
        raise ValueError(f"{p} is not a prime up to {self.limit}")


sieve = PrimeSieve(10000)


def smallest_goldbach_prime(n):
    """Return the smallest prime p such that n = p + q, both primes."""
    for p in range(2, n // 2 + 1):
        if sieve.is_prime(p) and sieve.is_prime(n - p):
            # return sieve.prime_index(p)
            return p
    return None


def biggest_goldbach_prime(n):
    """Return the smallest prime p such that n = p + q, both primes."""
    for p in range(2, n // 2 + 1):
        if sieve.is_prime(p) and sieve.is_prime(n - p):
            # return sieve.prime_index(n - p)
            return n - p
    return None


evens = list(range(4, 1001, 2))
s = [smallest_goldbach_prime(n) for n in evens]
b = [biggest_goldbach_prime(n) for n in evens]

# Compute magnitude (r) and angle (theta)
r = [math.sqrt(x**2 + y**2) for x, y in zip(b, s)]
theta = [math.atan2(y, x) for x, y in zip(b, s)]

# Create polar plot
plt.figure(figsize=(6, 6))
ax = plt.subplot(111, polar=True)

# Connect points in order
ax.plot(theta, r, marker="o", linestyle="-")  # line with markers
ax.set_title("Complex Numbers Connected in Polar Coordinates")
plt.show()
