#include <iostream>
#include<random>
#include<ctime>

std::mt19937_64 rd(time(nullptr));


template<typename T>
class LinkedList {
private:
    struct Cell {
        T data;
        int index;
        Cell *prev = NULL;
        Cell *next = NULL;

        Cell(T d, int i, Cell* p): data(d), index(i), prev(p) {}

        ~Cell() {
            delete next;
        }
    } *root = nullptr;

    size_t size = 0;

    void increase_indexes(Cell *cell) {
        Cell *tmp = cell;
        while (tmp != nullptr) {
            tmp->index++;
            tmp = tmp->next;
        }
    }

public:
    LinkedList() = default;

    T operator[](int i) const {
        Cell *tmp = root;

        while (tmp != nullptr and tmp->index != i) tmp = tmp->next;

        if (tmp == nullptr) {
            std::cout << "Index " << i << " is out of range << '\n";
            return 0;
        }
        else {
            return tmp->data;
        }
    }

    bool find(T value) {
        Cell *tmp = root;

        while (tmp != nullptr and tmp->data != value) tmp = tmp->next;

        if (tmp == nullptr) return false;
        else return true;
    }

    void insert(T d, int i){
        if (size - 1 < i) {
            std::cout << "Index " << i << " is out of range << '\n";
            return;
        }

        Cell *tmp = root;

        while (tmp->index < i) tmp = tmp->next;

        if (tmp == root) {
            tmp = new Cell(d, i, nullptr);
            tmp->next = root;
            root = tmp;
            increase_indexes(root->next);
            root->next->prev = root;
        }
        else {
            Cell *new_cell = new Cell(d, i, tmp->prev);
            new_cell->next = tmp;
            tmp->prev = new_cell;
            increase_indexes(new_cell->next);
            new_cell->prev->next = new_cell;
        }
    }

    void push_back(T d) {
        if (size == 0) root = new Cell(d, 0, nullptr);
        else {
            Cell *tmp = root;
            while (tmp->next != nullptr) tmp = tmp->next;

            tmp->next = new Cell(d, size, tmp);
        }
        size++;
    }

    void remove(T value) {
        Cell *tmp = root;

        while (tmp != nullptr and tmp->data != value) tmp = tmp->next;

        if (tmp == nullptr) std::cout << "There are no " << value << "in this linked list" << '\n';
        else if (tmp == root){
            root = root->next;
            tmp->next = nullptr;
            delete tmp;
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next = nullptr;
            delete tmp;
        }
    }

    void print() const {
        Cell *tmp = root;

        while (tmp != nullptr) {
            std::cout << tmp->data << ' ';
            tmp = tmp->next;
        }

        std::cout << '\n';
    }
};


int main() {
    LinkedList<int> list;
    for (size_t i = 0; i < 20; ++i) list.push_back(rd() % 30);
    list.print();

    std::cout << list[2] << '\n';

    std::cout << list.find(13) << '\n';

    list.insert(25, 2);
    list.print();

    std::cout << list[3] << '\n';

    list.remove(25);
    list.print();

    return 0;
}
