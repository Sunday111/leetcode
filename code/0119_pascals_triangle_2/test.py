import math
from pathlib import Path

mod5_table = [[math.comb(a, b) % 5 if b <= a else 0 for b in range(5)] for a in range(5)]


def binom_mod2(n, k):
    return 1 if (k & ~n) == 0 else 0


def binom_mod5(n, k):
    result = 1
    while n or k:
        ni, ki = n % 5, k % 5
        result = (result * mod5_table[ni][ki]) % 5
        n //= 5
        k //= 5
    return result


def crt_mod10(mod2, mod5):
    for x in range(10):
        if x % 2 == mod2 and x % 5 == mod5:
            return x


def binom_mod10(n, k):
    m2 = binom_mod2(n, k)
    m5 = binom_mod5(n, k)
    return crt_mod10(m2, m5)


def main():
    values = []
    for r in range(999):
        for i in range(r + 1):
            values.append(math.comb(r, i) % 10)
    with open(Path(__file__).parent.resolve() / "precompute.txt", mode="wt") as f:
        f.write(str(values))

    v2 = []
    for r in range(999):
        for i in range(r + 1):
            v2.append(binom_mod10(r, i))
    assert values == v2


if __name__ == "__main__":
    main()
