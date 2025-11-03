import math
import cmath
import matplotlib.pyplot as plt

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


import math
import cmath
import matplotlib.pyplot as plt


def dft(signal):
    """
    Compute the Discrete Fourier Transform (DFT) of a signal.
    No NumPy used.
    """
    N = len(signal)
    result = []
    for k in range(N):
        s = 0
        for n in range(N):
            angle = -2j * math.pi * k * n / N
            s += signal[n] * cmath.exp(angle)
        result.append(s)
    return result


def main():
    # Example input samples (you can modify this)
    samples = [sieve.primes[i] - sieve.primes[i - 1] for i in range(1, len(sieve.primes))]
    # samples = [math.sin(2 * math.pi * 3 * t / 32) for t in range(32)]

    # Compute DFT
    freq_data = dft(samples)

    # Magnitude spectrum
    magnitudes = [abs(x) for x in freq_data]

    # Plot the original signal
    plt.figure(figsize=(10, 6))
    plt.subplot(2, 1, 1)
    plt.title("Original Signal")
    plt.plot(samples, marker="o")
    plt.xlabel("Sample index")
    plt.ylabel("Amplitude")

    # Plot the magnitude spectrum
    plt.subplot(2, 1, 2)
    plt.title("Frequency Spectrum (DFT Magnitude)")
    plt.plot(magnitudes, marker="o")
    plt.xlabel("Frequency index")
    plt.ylabel("Magnitude")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
