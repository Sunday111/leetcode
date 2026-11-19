import operator
import math
from typing import Generator, Callable

digits = list(range(1, 10))
ops = [operator.add, operator.sub, operator.mul, operator.truediv]


def gen_digits() -> Generator[tuple[int, int, int, int], None, None]:
    for a in digits:
        for b in digits:
            for c in digits:
                for d in digits:
                    yield a, b, c, d


def gen_operators() -> Generator[list[Callable[[float, float], float]], None, None]:
    for o0 in ops:
        for o1 in ops:
            for o2 in ops:
                yield o0, o1, o2


def main():
    variants: set[int] = set()

    for a, b, c, d in gen_digits():

        def test(v: float):
            if math.isclose(24, v):
                l = sorted([a, b, c, d])
                variants.add(l[0] + l[1] * 10 + l[2] * 100 + l[3] * 1000)

        for o0, o1, o2 in gen_operators():
            try:
                test(o2(o1(o0(a, b), c), d))  # (((a, b), c) d)
            except ZeroDivisionError:
                pass

            try:
                test(o2(o0(a, o1(b, c)), d))  # ((a, (b, c)), d)
            except ZeroDivisionError:
                pass

            try:
                test(o1(o0(a, b), o2(c, d)))  # ((a, b), (c, d))
            except ZeroDivisionError:
                pass

            try:
                test(o0(a, o2(o1(b, c), d)))  # (a, ((b, c), d))
            except ZeroDivisionError:
                pass

            try:
                test(o0(a, o1(b, o2(c, d))))  # (a, (b, (c, d)))
            except ZeroDivisionError:
                pass

    print(f'std::array<int, {len(variants)}> kValid{{{",".join(str(x) for x in sorted(variants))}}};')


if __name__ == "__main__":
    main()
