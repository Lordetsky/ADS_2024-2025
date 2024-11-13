//#include "iostream"
//#include "random"
//#include "ctime"
//
//std::mt19937_64 rd(time(nullptr));
//
//
//template<typename T>
//class Tree {
//private:
//    struct Node{
//        T data;
//        T sum;
//        uint64_t priora = rd();
//        Node* left = nullptr;
//        Node* right = nullptr;
//
//        Node(T d): data(d), sum(d){}
//
//        ~Node() {
//            delete left;
//            delete right;
//        }
//    } *root = nullptr;
//
//    T get_sum(Node *node) {
//        if (node != nullptr) return node->sum;
//        return 0;
//    }
//
//    std::pair<Node*, Node*> split(Node* tree, T key) {
//        if (tree == nullptr) return {nullptr, nullptr};
//
//        if (tree->data > key) {
//            auto q = split(tree->left, key);
//            tree->left = q.second;
//            tree->sum = get_sum(tree->left) + get_sum(tree->right) + tree->data;
//
//            return {q.first, tree};
//        }
//        else {
//            auto q = split(tree->right, key);
//            tree->right = q.first;
//            tree->sum = get_sum(tree->left) + get_sum(tree->right) + tree->data;
//
//            return {tree, q.second};
//        }
//    }
//
//    Node* merge(Node* smaller, Node* bigger) {
//        if (smaller == nullptr) return bigger;
//        if (bigger == nullptr) return smaller;
//
//        if (bigger->priora < smaller->priora) {
//            smaller->right = merge(smaller->right, bigger);
//            smaller->sum = get_sum(smaller->left) + get_sum(smaller->right) + smaller->data;
//
//            return smaller;
//        }
//        else {
//            bigger->left = merge(smaller, bigger->left);
//            bigger->sum = get_sum(bigger->left) + get_sum(bigger->right) + bigger->data;
//
//            return bigger;
//        }
//    }
//
//    Node* remove(Node* node, T key) {
//        if (node == nullptr) return nullptr;
//
//        if (node->data == key) {
//            Node* result = merge(node->left, node->right);
//            node->left = nullptr;
//            node->right = nullptr;
//            delete node;
//
//            return result;
//        }
//
//        if (key < node->data) node->left = remove(node->left, key);
//        else node->right = remove(node->right, key);
//
//        node->sum = get_sum(node->left) + get_sum(node->right) + node->data;
//
//        return node;
//    }
//
//    T lr_sum(Node* node, T l, T r) {
//        auto [left, middle] = split(node, l - 1);
//        auto [mid, right] = split(middle, r);
//
//        T result = get_sum(mid);
//        root = merge(left, merge(mid, right));
//        return result;
//    }
//
//    bool find(Node* node, T key) {
//        if (node == nullptr) return false;
//
//        if (node->data == key) return true;
//        if (key < node->data) return find(node->left, key);
//        return find(node->right, key);
//    }
//
//public:
//    Tree() = default;
//
//    void insert(T key) {
//        auto q = split(root, key);
//        root = merge(merge(q.first, new Node(key)), q.second);
//    }
//
//    void remove(T data) {
//        root = remove(root, data);
//    }
//
//    bool find(T key) {
//        return find(root, key);
//    }
//
//    T lr_sum(T l, T r) {
//        return lr_sum(root, l, r);
//    }
//
//    ~Tree() {
//        delete root;
//    }
//};
//
//long long f(long long x, long long s) {
//    return (x + s) % 1000000001;
//}
//
//int main() {
//    Tree<long long> tree;
//    int n;
//    std::cin >> n;
//
//    char word;
//    long long a, b, s = 0;
//    for (int i = 0; i < n; i++) {
//        std::cin >> word >> a;
//        if (word == '+') {
//            tree.insert(f(a, s));
//        } else if (word == '-') {
//            tree.remove(f(a, s));
//        } else if (word == '?') {
//            if (tree.find(f(a, s))) {
//                std::cout << "Found" << '\n';
//            } else {
//                std::cout << "Not found" << '\n';
//            }
//        } else if (word == 's') {
//            std::cin >> b;
//            s = tree.lr_sum(f(a, s), f(b, s));
//            std::cout << s << '\n';
//        }
//    }
//
//    return 0;
//}


#include<iostream>


template<typename T>
class Tree {
private:
    struct Node {
         T data;
        int height = 1;
         T sum;
        Node *left = nullptr;
        Node *right = nullptr;
        Node( T d) : data(d), sum(d) {}

        ~Node() {
            delete left;
            delete right;
        }

    } *root = nullptr;

    int get_height(Node *node) {
        if (node != nullptr) return node->height;
        return 0;
    }

     T get_sum(Node *node) {
        if (node != nullptr) return node->sum;
        return 0;
    }

    void node_update(Node *node) {
        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
        node->sum = get_sum(node->left) + get_sum(node->right) + node->data;
    }

    Node* left_rotation(Node *node) {
        Node *right = node->right;
        Node *right_left = right->left;

        right->left = node;
        node->right = right_left;

        node_update(node);
        node_update(right);

        return right;
    }

    Node* right_rotation(Node *node) {
        Node *left = node->left;
        Node *left_right = left->right;

        left->right = node;
        node->left = left_right;

        node_update(node);
        node_update(left);

        return left;
    }

    Node* insert(Node *node,  T data) {
        if (node == nullptr) return new Node(data);
        if (data < node->data) node->left = insert(node->left, data);
        else if (data > node->data) node->right = insert(node->right, data);
        else return node;

        node_update(node);

        int index = get_height(node->left) - get_height(node->right);
        if (index == 2) {
            if (data < node->left->data) return right_rotation(node);
            else {
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }
        }
        else if (index == -2) {
            if (data > node->right->data) return left_rotation(node);
            else {
                node->right = right_rotation(node->right);
                return left_rotation(node);
            }
        }
        return node;
    }

    Node *min(Node *node) {
        Node *tmp = node;
        while (tmp->left != nullptr) tmp = tmp->left;

        return tmp;
    }

    int height_diff(Node *node) {
        return get_height(node->left) - get_height(node->right);
    }

    Node* remove(Node *node,  T data) {
        if (node == nullptr) return node;
        else if (data < node->data) node->left = remove(node->left, data);
        else if (data > node->data) node->right = remove(node->right, data);
        else if (node->left == nullptr or node->right == nullptr) {
            Node *tmp = node->left != nullptr ? node->left : node->right;
            if (tmp == nullptr) {
                tmp = node;
                node = nullptr;
            } else *node = *tmp;
            tmp->left = nullptr, tmp->right = nullptr;
            delete tmp;
        }
        else {
            Node *tmp = min(node->right);
            node->data = tmp->data;
            node->right = remove(node->right, tmp->data);
        }

        if (node == nullptr) return nullptr;

        node_update(node);

        int index = height_diff(node);

        if (index > 1) {
            if (height_diff(node->left) >= 0) return right_rotation(node);
            else {
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }
        }
        else if (index < -1) {
            if (height_diff(node->right) <= 0) return left_rotation(node);
            else {
                node->right = right_rotation(node->right);
                return left_rotation(node);
            }
        }
        return node;
    }

     T lr_sum(Node *node,  T l,  T r) {
        if (node == nullptr) return 0;
        if (node->data < l) return lr_sum(node->right, l, r);
        if (node->data > r) return lr_sum(node->left, l, r);
        return node->data + lr_sum(node->left, l, r) + lr_sum(node->right, l, r);
    }

public:
    Tree() = default;

    void insert( T data) {
        root = insert(root, data);
    }

    bool find( T data) {
        Node* tmp = root;
        while (tmp != nullptr) {
            if (tmp->data == data) return true;
            tmp = data < tmp->data ? tmp->left : tmp->right;
        }
        return false;
    }


    void remove( T data) {
        root = remove(root, data);
    }

     T sum( T l,  T r) {
        return lr_sum(root, l, r);
    }

    ~Tree() {
        delete root;
    }
};

long long f(long long x, long long s) {
    return (x + s) % 1000000001;
}

int main() {
    Tree<long long> tree;
    int n;
    std::cin >> n;

    char word;
    long long a, b, s = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> word >> a;
        if (word == '+') {
            tree.insert(f(a, s));
        }
        else if (word == '-') {
            tree.remove(f(a, s));
        }
        else if (word == '?') {
            if (tree.find(f(a, s))) std::cout << "Found" << '\n';
            else std::cout << "Not found" << '\n';
        }
        else if (word == 's') {
            std::cin >> b;
            s = tree.sum(f(a, s), f(b, s));
            std::cout << s << '\n';
        }
    }

    return 0;
}