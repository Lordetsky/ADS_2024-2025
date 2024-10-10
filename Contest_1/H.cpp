#include "iostream"
#include "vector"
#include "numeric"
#include "algorithm"


bool sortirovka(std::pair<int, int> a, std::pair<int, int> b) {
//    std::cout << (double) a.first / a.second << "  " << (double) b.first / b.second << "  " << (((double) a.first / a.second) < ((double) b.first / b.second)) << '\n';
    return ((double) a.first / a.second) < ((double) b.first / b.second);
}


int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> numerators(n), denominators(n);
    std::vector<std::pair<int, int>> fractions(n * n);

    for (auto& el : numerators) std::cin >> el;
    for (auto& el : denominators) std::cin >> el;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int del = std::gcd(numerators[i], denominators[j]);
            fractions[i * n + j] = {numerators[i] / del, denominators[j] / del};
        }
    }

//    std::cout << '\n';
//
//    for (auto& i : fractions) {
//        std::cout << i.first << ' ' << i.second << '\n';
//    }
//
//    std::cout << "\n\n";

    std::sort(fractions.begin(), fractions.end(), sortirovka);

//    std::cout << "\n\n";
//
//    for (auto& i : fractions) {
//        std::cout << i.first << ' ' << i.second << '\n';
//    }
//
//    std::cout << "\n\n";

    std::vector<int> indexes(q);
    for (auto& el : indexes) std::cin >> el;

    for (auto i : indexes) {
        std::cout << fractions[i - 1].first << ' ' << fractions[i - 1].second << '\n';
    }

    return 0;
}