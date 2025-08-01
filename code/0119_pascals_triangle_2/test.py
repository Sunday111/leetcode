import math


def sol(row: int, i: int):
    assert i <= row
    r: int = 1
    k1 = min(i, row - i)
    k2 = max(i, row - i)

    for t in range(k2 + 1, row + 1):
        r *= t

    for t in range(1, k1 + 1):
        r //= t

    return r


def main():
    for r in range(30):
        for i in range(r + 1):
            print(sol(r, i), end=" ")
        print()


if __name__ == "__main__":
    main()

    print(math.log2(math.factorial(33)))
