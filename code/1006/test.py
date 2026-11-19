first = 1

for i in range(0, 100):
    k = first + i * 4
    a = (k * (k - 1) // (k - 2)) - k + 3
    print(a)
