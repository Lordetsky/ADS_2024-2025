#include "iostream"
#include "string"
#include "vector"
#include "algorithm"


bool cmp(std::pair<std::string, int> p1, std::pair<std::string, int> p2) {
    return p1.first < p2.first;
}

int main() {
    std::string str;
    std::getline(std::cin, str);

    std::vector<std::pair<std::string, int>> suffixes(str.size());
    for (int i = 0; i < str.size(); i++) suffixes[i] = {str.substr(i, str.size() - i), i + 1};

    std::sort(suffixes.begin(), suffixes.end(), cmp);

    for (const auto& el : suffixes) std::cout << el.second << ' ';

    return 0;
}