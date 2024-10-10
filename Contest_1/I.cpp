#include "iostream"
#include "vector"
#include "fstream"


class Heap {
private:
    std::vector<long long> heap;

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
        while (i > 0 and heap[i] > heap[parent(i)]) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int max = i, l = left(i), r = right(i);

        if (l < heap.size() and heap[l] > heap[max]) max = l;
        if (r < heap.size() and heap[r] > heap[max]) max = r;

        if (i != max) {
            std::swap(heap[i], heap[max]);
            siftDown(max);
        }
    }

public:
    Heap() = default;

    void clear() {
        heap.clear();
    }

    void add(long long value) {
        heap.push_back(value);
        siftUp();
    }

    void extract() {
        if (heap.empty()) {
            std::cout << "CANNOT" << '\n';
            return;
        }

        std::cout << heap[0] << '\n';
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
    }

    ~Heap() {
        heap.clear();
    }
};


int main() {
//    const std::string FILENAME = "/Users/senya/CLionProjects/ADS_2024-2025/Contest_1/I_input.txt";
    const std::string FILENAME = "input.txt";
    std::ifstream inputFile;
    inputFile.open(FILENAME);
//    if(inputFile)
//    {
//        std::cout<<"OK\n";
//    }

    Heap heap;

    std::string word;
    while (inputFile >> word) {
        if (word == "CLEAR") {
            heap.clear();
        }
        else if (word == "ADD") {
            inputFile >> word;
            heap.add(std::stoll(word));
        }
        else if (word == "EXTRACT") {
            heap.extract();
        }
    }

    return 0;
}