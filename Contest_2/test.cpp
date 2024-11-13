#include<iostream>

template<typename T>
class Tree {
private:
    enum Color {RED, BLACK};

    struct Node {
        T data;
        T sum;
        Color color;
        Node *left, *right, *parent;

        Node(T d, Color c) : data(d), sum(d), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
    } *root = nullptr;

    void left_rotate(Node *&currentRoot, Node *&pt) {
        Node *pt_right = pt->right;
        pt->right = pt_right->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr)
            currentRoot = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void right_rotate(Node *&currentRoot, Node *&pt) {
        Node *pt_left = pt->left;
        pt->left = pt_left->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            currentRoot = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fix_violation(Node *&currentRoot, Node *&pt) {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;

        while ((pt != currentRoot) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {
                Node *uncle_pt = grand_parent_pt->right;

                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else {
                    if (pt == parent_pt->right) {
                        left_rotate(currentRoot, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    right_rotate(currentRoot, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            else {
                Node *uncle_pt = grand_parent_pt->left;

                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else {
                    if (pt == parent_pt->left) {
                        right_rotate(currentRoot, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    left_rotate(currentRoot, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        currentRoot->color = BLACK;
    }

    Node* bst_insert(Node* currentRoot, Node* pt) {
        if (currentRoot == nullptr)
            return pt;

        if (pt->data < currentRoot->data) {
            currentRoot->left = bst_insert(currentRoot->left, pt);
            currentRoot->left->parent = currentRoot;
        }
        else if (pt->data > currentRoot->data) {
            currentRoot->right = bst_insert(currentRoot->right, pt);
            currentRoot->right->parent = currentRoot;
        }
        return currentRoot;
    }

    Node* min(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    void delete_fixup(Node*& currentRoot, Node*& x) {
        while (x != currentRoot && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(currentRoot, x->parent);
                    w = x->parent->right;
                }
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    } else {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(currentRoot, w);
                        w = x->parent->right;
                    }
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != nullptr)
                    w->right->color = BLACK;
                left_rotate(currentRoot, x->parent);
                x = currentRoot;
            } else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(currentRoot, x->parent);
                    w = x->parent->left;
                }
                if (w->right == nullptr || w->right->color == BLACK) {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    } else {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(currentRoot, w);
                        w = x->parent->left;
                    }
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != nullptr)
                    w->left->color = BLACK;
                right_rotate(currentRoot, x->parent);
                x = currentRoot;
            }
        }
        if (x != nullptr)
            x->color = BLACK;
    }

    Node* rb_delete(Node* currentRoot, Node* z) {
        if (z == nullptr) return currentRoot;

        Node* y = z;
        Node* x = nullptr;
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            rb_transplant(currentRoot, z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            rb_transplant(currentRoot, z, z->left);
        }
        else {
            y = min(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != nullptr) x->parent = y;
            } else {
                rb_transplant(currentRoot, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rb_transplant(currentRoot, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == BLACK && x != nullptr)
            delete_fixup(currentRoot, x);

        return currentRoot;
    }

    void rb_transplant(Node* &currentRoot, Node* u, Node* v) {
        if (u->parent == nullptr)
            currentRoot = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    T lr_sum(Node *node, T l, T r) {
        if (node == nullptr) return 0;
        if (node->data < l) return lr_sum(node->right, l, r);
        if (node->data > r) return lr_sum(node->left, l, r);
        return node->data + lr_sum(node->left, l, r) + lr_sum(node->right, l, r);
    }

public:
    Tree() = default;

    void insert(T data) {
        Node* pt = new Node(data, RED);
        root = bst_insert(root, pt);
        fix_violation(root, pt);
    }

    void remove(T data) {
        Node* z = root;
        while (z != nullptr && z->data != data) {
            if (data < z->data)
                z = z->left;
            else
                z = z->right;
        }
        if (z != nullptr)
            root = rb_delete(root, z);
    }

    bool find(T data) {
        Node* tmp = root;
        while (tmp != nullptr) {
            if (tmp->data == data) return true;
            tmp = data < tmp->data ? tmp->left : tmp->right;
        }
        return false;
    }

    T sum(T l, T r) {
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
