#include "iostream"
#include "vector"
#include "iomanip"


class Heap {
private:
    std::vector<int> heap;

    int parent(int i) const {
        return (i - 1) / 2;
    }
    int left(int i) const {
        return 2 * i + 1;
    }
    int right(int i) const {
        return 2 * i + 2;
    }

    void siftUp() {
        int i = (int) heap.size() - 1;
        while (i > 0 and heap[i] < heap[parent(i)]) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int min = i, l = left(i), r = right(i);

        if (l < heap.size() and heap[l] < heap[min]) min = l;
        if (r < heap.size() and heap[r] < heap[min]) min = r;

        if (i != min) {
            std::swap(heap[i], heap[min]);
            siftDown(min);
        }
    }

public:
    Heap() = default;

    int getSize() const {
        return (int) heap.size();
    }

    void clear() {
        heap.clear();
    }

    void add(int value) {
        heap.push_back(value);
        siftUp();
    }

    int extract() {
//        if (heap.empty()) {
//            std::cout << "CANNOT" << '\n';
//            return;
//        }

        int ans = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);

        return ans;
    }

    ~Heap() {
        heap.clear();
    }
};


int main() {
    int n, new_num;
    std::cin >> n;

    Heap heap;
    for (int i = 0; i < n; i++) {
        std::cin >> new_num;
        heap.add(new_num);
    }

    double ans = 0;
    while (heap.getSize() > 1) {
        new_num = heap.extract() + heap.extract();
        ans += new_num;
        heap.add(new_num);
    }

    std::cout << std::fixed << std::setprecision(2) << ans * 0.05 << std::endl;

    return 0;
}