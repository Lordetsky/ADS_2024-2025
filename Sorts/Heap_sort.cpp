#include <iostream>
#include <vector>
#include <algorithm>


void Heapify(std::vector<int>& buf, int i, bool flag=true){
    if (i >= buf.size() or i * 2 + 1 >= buf.size() or i * 2 + 2 >= buf.size()) return;
    if (flag) Heapify(buf,  i + 1);

    if (buf[i] >= buf[i * 2 + 1] and buf[i] >= buf[i * 2 + 2]) return;

//    std::cout << "i: " << i << ", num: " << buf[i] << "   "
//                << "i * 2 + 1: " << i * 2 + 1 << ", num: " << buf[i * 2 + 1] << "   "
//                << "i * 2 + 2: " << i * 2 + 2 << ", num: " << buf[i * 2 + 2] << '\n';

    int max = i;
    if (buf[max] < buf[i * 2 + 1]) max = i * 2 + 1;
    if (buf[max] < buf[i * 2 + 2]) max = i * 2 + 2;

    if (max != i){
        std::swap(buf[i], buf[max]);
//        std::cout << "We need to swap numbers\n"
//                    << "Now i: " << i << ", num: " << buf[i] << "   "
//                    << "max: " << max << ", num: " << buf[max] << "\n\n";
//        std::cout << "Vector: ";
//        for (const auto& i : buf) std::cout << i << ' ';
//        std::cout << "\n\n";

        Heapify(buf,  max);
    }
//    else std::cout << "Nothing to swap\n\n";
}

int main() {
    std::vector<int> buf = {1, 5, 7, 2, 3, 4, 9, 6, 7, 0, 9};
    std::cout << "Vector: ";
    for (const auto& i : buf) std::cout << i << ' ';
    std::cout << "\n\n";


    Heapify(buf, 0);

    std::cout << "Heapified vector: ";
    for (const auto& i : buf) std::cout << i << ' ';

    std::cout << "\n\n";

//    std::cout << "Now we need to sort it\n\n";

    std::vector<int> sorted_buf;
    while (buf.size() > 2){
        sorted_buf.push_back(buf[0]);
        std::swap(buf[0], buf[buf.size() - 1]);
        buf.pop_back();

        Heapify(buf, 0, false);
    }
    if (buf[0] > buf[1]){
        sorted_buf.push_back(buf[0]);
        sorted_buf.push_back(buf[1]);
    }
    else {
        sorted_buf.push_back(buf[1]);
        sorted_buf.push_back(buf[0]);
    }

    std::cout << "Sorted vector: ";
    for (const auto& i : sorted_buf) std::cout << i << ' ';

    return 0;
}
