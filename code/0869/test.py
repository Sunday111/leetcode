m = 0
for i in range(30):
    v = 2**i
    cnt = [0] * 10
    while v != 0:
        cnt[v % 10] += 1
        v //= 10
    m = max(m, max(cnt))
    print(f"(2^{i:2}) : {2**i:^10}: {str(cnt):40}")
print(m)
