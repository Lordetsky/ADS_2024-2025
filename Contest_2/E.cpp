#include<iostream>
#include "fstream"


class Tree {
private:
    struct Node {
        int data;
        int height = 1;
        int size = 1;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int d) : data(d) {}

        ~Node() {
            delete left;
            delete right;
        }

    } *root = nullptr;

    int get_height(Node *node) {
        if (node != nullptr) return node->height;
        return 0;
    }

    int get_size(Node *node) {
        if (node != nullptr) return node->size;
        return 0;
    }

    Node* left_rotation(Node *node) {
        Node *right = node->right;
        Node *right_left = right->left;

        right->left = node;
        node->right = right_left;

        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
        node->size = get_size(node->left) + get_size(node->right) + 1;

        right->height = std::max(get_height(right->left), get_height(right->right)) + 1;
        right->size = get_size(right->left) + get_size(right->right) + 1;

        return right;
    }

    Node* right_rotation(Node *node) {
        Node *left = node->left;
        Node *left_right = left->right;

        left->right = node;
        node->left = left_right;

        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
        node->size = get_size(node->left) + get_size(node->right) + 1;

        left->height = std::max(get_height(left->left), get_height(left->right)) + 1;
        left->size = get_size(left->left) + get_size(left->right) + 1;

        return left;
    }

    Node* insert(Node *node, int data) {
        if (node == nullptr) return new Node(data);
        if (data < node->data) node->left = insert(node->left, data);
        else if (data > node->data) node->right = insert(node->right, data);
        else return node;

        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
        node->size = get_size(node->left) + get_size(node->right) + 1;

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

    Node* remove(Node *node, int data) {
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

        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
        node->size = get_size(node->left) + get_size(node->right) + 1;

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

    std::pair<bool, int> kth(Node *node, int k) {
        if (node == nullptr) return {false, 0};

        int left_size = get_size(node->left);

        if (k == left_size + 1) return {true, node->data};
        else if (k <= left_size) return kth(node->left, k);
        else return kth(node->right, k - left_size - 1);
    }

public:
    Tree() = default;

    void insert(int data) {
        root = insert(root, data);
    }

    bool find(int data) {
        Node *tmp = root;
        bool isdata = false;

        while(tmp != nullptr) {
            if (tmp->data == data) {
                isdata = true;
                break;
            }
            if (tmp->data > data) tmp = tmp->left;
            else tmp = tmp->right;
        }

        return isdata;
    }


    void remove(int data) {
        root = remove(root, data);
    }

    void next(int data) {
        Node *tmp = root, *res = nullptr;
        while (tmp != nullptr) {
            if (data < tmp->data) {
                res = tmp;
                tmp = tmp->left;
            }
            else tmp = tmp->right;
        }

        if (res != nullptr) std::cout << res->data << '\n';
        else std::cout << "none" << '\n';
    }

    void prev(int data) {
        Node *tmp = root, *res = nullptr;
        while (tmp != nullptr) {
            if (data > tmp->data) {
                res = tmp;
                tmp = tmp->right;
            }
            else tmp = tmp->left;
        }

        if (res != nullptr) std::cout << res->data << '\n';
        else std::cout << "none" << '\n';
    }

    void kth(int k) {
        auto result = kth(root, k);
        if (result.first) std::cout << result.second << '\n';
        else std::cout << "none" << '\n';
    }

    ~Tree() {
        delete root;
    }
};

int main() {
//    const std::string FILENAME = "/Users/senya/CLionProjects/ADS_2024-2025/Contest_2/E_input.txt";
    const std::string FILENAME = "input.txt";
    std::ifstream inputFile;
    inputFile.open(FILENAME);

    Tree tree;


    std::string word;
    int num;
    while (inputFile >> word) {
        inputFile >> num;
        if (word == "insert") {
            tree.insert(num);
        }
        else if (word == "delete") {
            tree.remove(num);
        }
        else if (word == "exists") {
            if (tree.find(num)) std::cout << "true" << '\n';
            else std::cout << "false" << '\n';
        }
        else if (word == "next") {
            tree.next(num);
        }
        else if (word == "prev") {
            tree.prev(num);
        }
        else if (word == "kth") {
            tree.kth(num);
        }
    }

    return 0;
}