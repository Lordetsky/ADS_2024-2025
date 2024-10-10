def SelectionSort(arr):
    ans = []
    while len(arr) > 0:
        ans.append(arr.pop(arr.index(max(arr))))

    return ans


print(*SelectionSort(list(map(int, input().split()))))
