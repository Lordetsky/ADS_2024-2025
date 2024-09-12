#include <iostream>
#include <vector>
#include <bitset>
#include <queue>

void RadixSort(std::vector<unsigned int>& buf){
    std::vector<std::bitset<32>> bin_buf(buf.size());

    for (int i = 0; i < buf.size(); i++) {
        bin_buf[i] = std::bitset<32>(buf[i]);
    }

    std::vector<std::queue<std::bitset<32>>> all_queues(256);

    for (int i = 0; i < 4; i++) {
        for (const auto& el : bin_buf) {
            std::bitset<8> num;
            for (int j = 0; j < 8; j++) {
                num[j] = el[i * 8 + j];
            }

            int index = static_cast<int>(num.to_ulong());
            all_queues[index].push(el);
        }

        int index = 0;
        for (auto& queue : all_queues) {
            while (!queue.empty()) {
                bin_buf[index] = queue.front();
                index++;
                queue.pop();
            }
        }
    }

    for (int i = 0; i < bin_buf.size(); i++) {
        buf[i] = static_cast<int>(bin_buf[i].to_ulong());
    }
}

int main() {
    std::vector<unsigned int> buf = {1, 5, 7, 2, 3, 4, 9, 6, 7, 0, 9};

    std::cout << "Original vector: ";
    for (const auto& i : buf) std::cout << i << ' ';
    std::cout << "\n\n";

    RadixSort(buf);

    std::cout << "Sorted vector: ";
    for (const auto& i : buf) std::cout << i << ' ';
    std::cout << "\n";

    return 0;
}
