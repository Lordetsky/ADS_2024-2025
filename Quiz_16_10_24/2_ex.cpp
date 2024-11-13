#include "iostream"


int main() {
    long long x, i = 1, j = 1, k = 1;
    bool flag = true;
    std::cin >> x;

    while (k <= x) {
        if (i * i < j * j * j) {
            flag = true;
            if (k < x) i++;
        }
        else if (i * i > j * j * j) {
            flag = false;
            if (k < x) j++;
        }
        else if (k < x){
            i++, j++;
        }
        k++;
    }

//    for (int a = 1; a <= i; a++) std::cout << a * a << ' ';
//
//    std::cout << '\n';
//
//    for (int a = 1; a <= j; a++) std::cout << a * a * a << ' ';
//
//    std::cout << '\n';

//    i--, j--;



    if (flag) std::cout << i * i;
    else std::cout << j * j * j;

    return 0;
}