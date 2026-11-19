s = "a"
for i in range(0, 26):
    r = ""
    for c in s:
        if c == "z":
            r += "ab"
        else:
            r += chr(ord(c) + 1)
    s = r
print(s)
