n = int(input())
n_items = list(map(int, input().split()))
m = int(input())
m_items = list(map(int, input().split()))

delta, left, right = abs(n_items[0] - m_items[0]), n_items[0], m_items[0]
i, j = 0, 0
while i < n and j < m:
    if delta > abs(n_items[i] - m_items[j]):
        delta, left, right = abs(n_items[i] - m_items[j]), n_items[i], m_items[j]

    if n_items[i] < m_items[j]:
        i += 1
    else:
        j += 1

print(left, right)
