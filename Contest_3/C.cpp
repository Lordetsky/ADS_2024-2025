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
//    for (int i = 0; i < 50000; i++) str.push_back('c');
//    str.push_back('a');

    std::vector<int> z (str.size(), 0);

    Z_func(z, str);

    bool flag = true;
    if (str.size() == 1) std::cout << 1;
    else {
        for (int i = 0; i < str.size(); i++) {
            if (i + z[i] == str.size()){
                std::cout << i;
                flag = false;
                break;
            }
        }
    }

    if (flag) std::cout << str.size();
}