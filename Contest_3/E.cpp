#include "iostream"
#include "string"
#include "vector"


void Z_func(std::vector<int>& z, const std::vector<int>& str) {
    int left = 1, right = 1;
    for (int i = 1; i < str.size(); i++) {
        if (i <= right) z[i] = std::min(z[i - left], right - i + 1);

        while (i + z[i] < str.size() and str[z[i]] == str[i + z[i]]) z[i]++;

        if (i + z[i] > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> p(n), str(n);
    for (auto& el : p) std::cin >> el;

    int alphabet = 0;

    for (int i = 0; i < n; i++) {
        if (p[i] == 0) {
            str[i] = alphabet;
            alphabet += 1;
        }
        else {
            str[i] = str[p[i] - 1];
        }
    }

    std::vector<int> res(n, 0);
    Z_func(res, str);

    for (auto el : res) std::cout << el << ' ';

    return 0;
}
