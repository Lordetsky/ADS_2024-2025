#include "iostream"
#include "string"
#include "vector"


void Z_func(std::vector<int>& z, const std::string& str) {
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
    std::string str;
    std::cin >> str;
    std::vector<int> res (str.size(), 0);

    Z_func(res, str);
    res[0] = str.size();

    for (auto el : res) std::cout << el << ' ';
}