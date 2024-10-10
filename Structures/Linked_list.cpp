#include <iostream>


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

public:
    LinkedList() = default;

    int find(int i) {
        Cell *tmp = root;

        while ()
    }

    void insert(T d, int i){
        if (size - 1 < i) {
            std::out_of_range("Index " + std::to_string(i) + " is out of range.\n");
        }
        else {
            Cell *tmp = root;

            while (tmp->index + 1 < i) tmp = tmp->next;

            if (tmp == root) {

            }
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
};
