#include "iostream"
#include "vector"
#include "tuple"


class Tree {
private:
    struct Node{
        int data;
        int priora;
        int index;
        Node *parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int d, int heap, int i): data(d), priora(heap), index(i) {}

        ~Node() {
            delete left;
            delete right;
        }
    } *root = nullptr;

    std::vector<std::tuple<int, int, int>> nodes;

    void make_vector(Node* node) {
        if (node == nullptr) return;

        make_vector(node->left);
        nodes[node->index - 1] = {get_index(node->parent), get_index(node->left), get_index(node->right)};

        make_vector(node->right);
    }

    std::pair<Node*, Node*> split(Node* tree, int key) {
        if (tree == nullptr) return {nullptr, nullptr};

        if (tree->data > key) {
            auto q = split(tree->left, key);
            tree->left = q.second;
            if (q.second != nullptr) q.second->parent = tree;

            return {q.first, tree};
        }
        else {
            auto q = split(tree->right, key);
            tree->right = q.first;
            if (q.first != nullptr) q.first->parent = tree;

            return {tree, q.second};
        }
    }

    Node* merge(Node* smaller, Node* bigger) {
        if (smaller == nullptr) return bigger;
        if (bigger == nullptr) return smaller;

        if (bigger->priora > smaller->priora) {
            smaller->right = merge(smaller->right, bigger);
            if (smaller->right != nullptr) smaller->right->parent = smaller;

            return smaller;
        }
        else {
            bigger->left = merge(smaller, bigger->left);
            if (bigger->left != nullptr) bigger->left->parent = bigger;

            return bigger;
        }
    }

    int get_index(Node *node) {
        if (node != nullptr) return node->index;
        return 0;
    }

public:
    Tree() = default;

    void insert(int key, int heap, int i) {
        auto q = split(root, key);
        root = merge(merge(q.first, new Node(key, heap, i)), q.second);
    }

    void make_vector() {
        make_vector(root);
    }

    void resize(int n) {
        nodes.resize(n);
    }

    void print_indexes() {
        std::cout << "YES" << '\n';
        for (auto i : nodes) {
            std::cout << std::get<0>(i) << ' ' << std::get<1>(i) << ' ' << std::get<2>(i) << '\n';
        }
    }

    ~Tree() {
        delete root;
    }
};


int main() {
    Tree tree;
    int n;
    std::cin >> n;
    tree.resize(n);

    int num, heap;
    for (int i = 0; i < n; i++) {
        std::cin >> num >> heap;
        tree.insert(num, heap, i + 1);
    }

    tree.make_vector();
    tree.print_indexes();

    return 0;
}