n = int(input())
line = sorted(input())

d = dict()

for c in line:
    d[c] = d.get(c, 0) + 1

ans = ""
center = ""
flag = True
for key, value in d.items():
    if flag and value % 2 == 1:
        center = key
        flag = False

    ans += key * (value // 2)

if flag:
    print(ans + ans[::-1])
else:
    print(ans + center + ans[::-1])