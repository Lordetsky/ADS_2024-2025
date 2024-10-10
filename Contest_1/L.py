a = input()
d = dict()
for i in range(len(a)):
    d[a[i]] = i

line = input()
print("".join(sorted(line, key=lambda x: d[x])))
