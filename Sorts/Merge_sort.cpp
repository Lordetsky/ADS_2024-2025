#include <iostream>
#include <vector>


void MergeSort(std::vector<int>& buf){
    if (buf.size() <= 1) return;

    std::vector<int> left(buf.begin(), buf.begin() + (int) buf.size() / 2),
                    right(buf.begin() + (int) buf.size() / 2, buf.end());

    MergeSort(right);
    MergeSort(left);

    int i = 0, j = 0;
    buf.clear();
    while (i < right.size() and j < left.size()){
        if (right[i] < left[j]){
            buf.push_back(right[i]);
            i++;
        }
        else {
            buf.push_back(left[j]);
            j++;
        }
    }

    if (i == right.size()) buf.insert(buf.end(), left.begin() + j, left.end());
    else buf.insert(buf.end(), right.begin() + i, right.end());
}

int main(){

    std::vector<int> buf = {1, 5, 7, 2, 3, 4, 9, 6, 7, 0, 9, 10};

    std::cout << "Original vector: ";
    for (const auto& i : buf) std::cout << i << ' ';
    std::cout << "\n\n";

    MergeSort(buf);

    std::cout << "Sorted vector: ";
    for (const auto& i : buf) std::cout << i << ' ';
    std::cout << "\n";

    return 0;
}