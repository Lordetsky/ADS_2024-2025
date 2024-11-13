#include "iostream"
#include "vector"


int main() {
    int n;
    std::cin >> n;
    std::vector<int> z(n), p(n, 0);
    for (auto& el : z) std::cin >> el;

    for(int i = 1; i < n; i++) {
        if (z[i] != 0) {
            for (int j = z[i] - 1; j >= 0 and (p[i + j]) == 0; j--) p[i + j] = j + 1;
        }
    }

    for (auto el : p) std::cout << el << ' ';

    return 0;
}

