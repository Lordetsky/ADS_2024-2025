#include<iostream>
#include<random>
#include<ctime>

std::mt19937_64 rd(time(nullptr));

template<typename T>
class Tree {
private:
    struct Node {
        T data;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;

        Node(T d) : data(d) {}

        ~Node() {
            delete left;
            delete right;
        }

    } *root = nullptr;

    void print(Node* node) {
        if (node == nullptr) return;

        print(node->left);
        std::cout << node->data << ' ';
        print(node->right);
    }

    Node* max(Node* node) {
        if (node == nullptr) return nullptr;

        while (node->right != nullptr) {
            node = node->right;
        }

        return node;
    }

    Node* min(Node* node) {
        if (node == nullptr) return nullptr;
        
        while (node->left != nullptr) {
            node = node->left;
        }
        
        return node;
    }

    void remove(Node* node) {
        if (node == nullptr) return;
        
        if (node == root) {
            if (node->left == nullptr and node->right == nullptr) delete root;
            else if (node->right == nullptr) root = root->left;
            else if (node->left == nullptr) root = root->right;
            else {
                Node* tmp = max(node->left);
                node->data = tmp->data;
                remove(tmp);
            }
        }
        else if (node->left == nullptr and node->right == nullptr) {
            Node* tmp = node->parent;
            
            if (tmp->left == node) tmp->left = nullptr;
            else tmp->right = nullptr;
            
            delete node;
        } 
        else if (node->left == nullptr or node->right == nullptr) {
            Node* tmp = node->parent;
            Node* child = node->left == nullptr ? node->right : node->left;

            if (tmp->left == node) tmp->left = child;
            else tmp->right = child;

            child->parent = tmp;
            delete node;
        }
        else {
            Node* tmp = max(node->left);
            node->data = tmp->data;
            remove(tmp);
        }
    }

public:
    Tree() = default;

    void insert(T data) {
        if (root == nullptr) {
            root = new Node(data);
        }
        else {
            Node *tmp = root;

            while(tmp->data != data) {
                if (tmp->data > data) {
                    if (tmp->left == nullptr) {
                        tmp->left = new Node(data);
                        tmp->left->parent = tmp;
                    }
                    tmp = tmp->left;
                }
                else {
                    if (tmp->right == nullptr) {
                        tmp->right = new Node(data);
                        tmp->right->parent = tmp;
                    }
                    tmp = tmp->right;
                }
            }
        }
    }

    bool find(T data) {
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

    void print() {
        print(root);
        std::cout << '\n';
    }

    void remove(T d) {
        Node *tmp = root;

        while(tmp != nullptr) {
            if (tmp->data == d) break;

            if (tmp->data > d) tmp = tmp->left;
            else tmp = tmp->right;
        }
        remove(tmp);
    }

    ~Tree() {
        delete root;
    }
};

int main() {
    Tree<double> tree;
    tree.insert(10);
    for (size_t i = 0; i < 20; ++i) {
        tree.insert(rd() % 30);
    }
    tree.print();

    tree.remove(10);
    tree.print();

    return 0;
}
