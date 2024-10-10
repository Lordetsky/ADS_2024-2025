#include <iostream>
#include <vector>


void MergeSort(std::vector<int>& buf){
    if (buf.size() <= 1) return;

    std::vector<int> left(buf.begin(), buf.begin() + (int) buf.size() / 2),
            right(buf.begin() + (int) buf.size() / 2, buf.end());

    MergeSort(left);
    MergeSort(right);

    int i = 0, j = 0;
    while (i < left.size() and j < right.size()){
        if (left[i] < right[j]){
            buf[i + j] = left[i];
            i++;
        }
        else {
            buf[i + j] = right[j];
            j++;
        }
    }

    while (i < left.size()) {
        buf[i + j] = left[i];
        i++;
    }
    while (j < right.size()) {
        buf[i + j] = right[j];
        j++;
    }
}

int main(){
    int n;
    std::cin >> n;
    std::vector<int> buf(n);
    for (auto& el : buf) std::cin >> el;

    std::cout << "Original vector: ";
    for (const auto& i : buf) std::cout << i << ' ';
    std::cout << "\n\n";

    MergeSort(buf);

    std::cout << "Sorted vector: ";
    for (const auto& i : buf) std::cout << i << ' ';
    std::cout << "\n";

    return 0;
}