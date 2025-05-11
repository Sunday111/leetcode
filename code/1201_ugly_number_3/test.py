import math


def brute_force(k: int, a: int, b: int, c: int):
    r = 0
    for v in range(2, k):
        if (v % a == 0) or (v % b == 0) or (v % c) == 0:
            r += 1
    return r


def theory(k: int, a: int, b: int, c: int):
    lcm_ab = math.lcm(a, b)
    ppa = k // a + k // b + k // c
    pps = 0
    pps += k // lcm_ab
    pps += k // math.lcm(b, c)
    pps += k // math.lcm(c, a)
    pps -= k // math.lcm(lcm_ab, c)
    return ppa - pps


def main():
    max_val = 200
    for a in range(2, max_val):
        for b in range(a + 1, max_val):
            for c in range(b + 1, max_val):
                bf = brute_force(max_val, a, b, c)
                th = theory(max_val - 1, a, b, c)
                if bf != th:
                    print(f"{a=} {b=} {c=}")
                    print(f"brute force: {bf}")
                    print(f"theory: {th}")


if __name__ == "__main__":
    main()


# def yo():
#     max_val = 100
#     for a in range(2, max_val):
#         for b in range(a + 1, max_val):
#             for c in range(b + 1, max_val):
#                 values = [a, b, c]

#                 values_and_multiples = {x: list(i for i in range(1, max_val + 1) if i % x == 0) for x in values}
#                 intersection = set.intersection(*(set(x) for x in values_and_multiples.values()))
#                 union = set.union(*(set(x) for x in values_and_multiples.values()))

#                 p = sum(len(x) for x in values_and_multiples.values())
#                 lcm_ab = math.lcm(a, b)
#                 lcm_bc = math.lcm(b, c)
#                 lcm_ca = math.lcm(c, a)
#                 lcm_abc = math.lcm(a, b, c)

#                 for x, multiples in values_and_multiples.items():
#                     assert len(multiples) == max_val // x

#                 def print_stats():
#                     print(f"{values=}")
#                     print("    multiples")
#                     for x, multiples in values_and_multiples.items():
#                         assert len(multiples) == max_val // x
#                         print(f"        {x:2}: {multiples} ({len(multiples)})")
#                     print(f"    {p} total numbers")
#                     print(f"    intersection: {sorted(intersection)}, {len(intersection)} common items")
#                     print(f"    union: {sorted(union)}, {len(union)} unique items")
#                     print(f"    lcm(a,b): {lcm_ab},  ({max_val//lcm_ab})")
#                     print(f"    lcm(b,c): {lcm_bc},  ({max_val//lcm_bc})")
#                     print(f"    lcm(c,a): {lcm_ca},  ({max_val//lcm_ca})")
#                     print(f"    lcm(a,b,c): {lcm_abc},  ({max_val//lcm_abc})")

#                 ppa = max_val // a + max_val // b + max_val // c
#                 pps = max_val // lcm_ab + max_val // lcm_bc + max_val // lcm_ca - max_val // lcm_abc
#                 assert (ppa - pps) == len(union)

#                 pp = max_val // a + max_val // b + max_val // c
#                 assert len(union) == pp - (max_val // lcm_ab + max_val // lcm_bc + max_val // lcm_ca) + (
#                     max_val // lcm_abc
#                 )

#                 if len(union) != brute_force(max_val + 1, a, b, c):
#                     print_stats()
#                     print(f"brute_force: {brute_force(max_val + 1, a, b, c)}")
#                     assert False


# yo()
