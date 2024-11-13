#include "iostream"
#include "map"
#include "string"


class Trie {
private:
    struct Node {
        std::map<char, Node> next;
        int value = 0;
    } root;

public:
    int add(const std::string& str, int val) {
        Node* v = &root;
        for (const char el : str) v = &v->next[el];
        v->value += val;
        return v->value;
    }
};

int main() {
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(nullptr);

    std::string str;
    int value;
    Trie trie;
    while (std::cin >> str >> value) std::cout << trie.add(str, value) << '\n';

    return 0;
}