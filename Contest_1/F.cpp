#include "iostream"
#include "algorithm"
#include "vector"


int main() {
    int n;
    std::cin >> n;
    std::vector<int> buf(n);
    for (auto& el : buf) std::cin >> el;

    int min_el = *std::min_element(buf.begin(), buf.end());
    int max_el = *std::max_element(buf.begin(), buf.end());
    int index = min_el < 0 ? std::abs(min_el) : 0;
    std::vector<int> result(index + 1 + max_el);
    std::fill(result.begin(), result.end(), 0);

    for(const auto el : buf) result[index + el] += 1;

    for (int i = 0; i < result.size(); i++){
        if (result[i] > 0) {
            for (int j = 0; j < result[i]; j++) {
                std::cout << std::to_string(-index + i) << ' ';
            }
        }
    }

    return 0;
}