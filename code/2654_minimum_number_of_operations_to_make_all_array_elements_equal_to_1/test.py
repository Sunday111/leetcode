from math import gcd


nums = [10, 5, 10, 30, 70, 4, 2, 6, 8, 4]

l = len(nums)
for i in range(len(nums)):
    j = i
    g = 0
    while j != l and g != 1:
        g = gcd(g, nums[j])
        j += 1
    if g == 1:
        print(f"[{i}:{j}): {nums[i:j]}")
