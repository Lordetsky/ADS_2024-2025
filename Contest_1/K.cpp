#include <iostream>
#include <vector>
#include <algorithm>


void Heapify(std::vector<int>& buf, int i, int size) {
    int max = i, child_1 = i * 2 + 1, child_2 = i * 2 + 2;

    if (child_1 < size and buf[child_1] > buf[max]) max = child_1;

    if (child_2 < size and buf[child_2] > buf[max]) max = child_2;

    if (max != i) {
        std::swap(buf[i], buf[max]);
        Heapify(buf, max, size);
    }
}

void BuildHeap(std::vector<int>& buf) {
    int size = buf.size();
    for (int i = size / 2 - 1; i >= 0; i--) {
        Heapify(buf, i, size);
    }
}

void HeapSort(std::vector<int>& buf) {
    BuildHeap(buf);
    int size = buf.size();
    for (int i = size - 1; i > 0; --i) {
        std::swap(buf[0], buf[i]);
        Heapify(buf, 0, i);
    }
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> buf(n);
    for (auto& el : buf) std::cin >> el;

    HeapSort(buf);

    for (const auto& i : buf) std::cout << i << ' ';

    return 0;
}
