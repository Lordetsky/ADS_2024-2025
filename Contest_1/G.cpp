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


unsigned int cur = 0;
unsigned int a, b;

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int a_1 = nextRand24(), b_1 = nextRand24();
    return (a_1 << 8) ^ b_1;
}

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        std::cin >> n >> a >> b;

        std::vector<unsigned int> arr(n);
        for (int j = 0; j < n; j++) arr[j] = nextRand32();

        RadixSort(arr);

        unsigned long long result = 0;
        for (int j = 0; j < n; j++) result += static_cast<unsigned long long>(arr[j]) * (j + 1);

        std::cout << result << '\n';
    }

    return 0;
}
