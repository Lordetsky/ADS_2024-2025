#include "iostream"
#include "string"
#include "vector"


void prefix_function(std::vector<int>& p, const std::string& str) {
    for (int i = 1; i < str.size(); i++) {
        int j = p[i - 1];
        while (j > 0 and str[i] != str[j])
            j = p[j-1];

        if (str[i] == str[j]) j++;
        p[i] = j;
    }
}

int main() {
    std::string str;
    std::cin >> str;
    std::vector<int> res (str.size(), 0);

    prefix_function(res, str);

    for (auto el : res) std::cout << el << ' ';

    return 0;
}
