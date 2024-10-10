file = open("input.txt", encoding="UTF-8")
text = list(map(lambda x: x.strip(), file.readlines()))

ans = {9: [], 10: [], 11: []}

for i in text:
    strr = i.split()
    ans[int(strr[0])].append(strr[1])

for key, value in ans.items():
    for i in value:
        print(key, i)
