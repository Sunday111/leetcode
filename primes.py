import matplotlib.pyplot as plt
import bisect

THE_LIMIT = 100000


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


sieve = PrimeSieve(THE_LIMIT)


def smallest_goldbach_prime(n):
    """Return the smallest prime p such that n = p + q, both primes."""
    for p in range(2, n // 2 + 1):
        if sieve.is_prime(p) and sieve.is_prime(n - p):
            return sieve.prime_index(p)
            return p
    return None


def biggest_goldbach_prime(n):
    """Return the smallest prime p such that n = p + q, both primes."""
    for p in range(2, n // 2 + 1):
        if sieve.is_prime(p) and sieve.is_prime(n - p):
            return sieve.prime_index(n - p)
            return n - p
    return None


evens = list(range(4, THE_LIMIT, 2))
small = [smallest_goldbach_prime(n) for n in evens]
big = [biggest_goldbach_prime(n) for n in evens]

plt.figure(figsize=(8, 5))
# plt.plot(evens, y1, label="y = x", color="gray", linestyle="--")
# plt.plot(evens, small, label="Small Prime Index", color="blue", marker="o")
# plt.plot(evens, big, label="Big Prime Index", color="red", marker="o")

skip = 1000
plt.plot(
    evens,
    # [bisect.bisect_left(sieve.primes, x) - (b + s) if x > skip else None for x, s, b in zip(evens, small, big)],
    [bisect.bisect_left(sieve.primes, x) / b if x > skip else None for x, s, b in zip(evens, small, big)],
    color="red",
    marker="o",
)

# y4 = [y / x for x, y in zip(evens, y3)]
# plt.plot(evens, y4, label="big prime / x", color="red", marker="o")

plt.xlabel("Even Number (n)")
plt.grid(True, linestyle="--", alpha=0.4)
plt.show()
