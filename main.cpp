#include "alloc.h"
#include <iostream>
#include <iterator>

int main() {

    Alloc c;
    std::cout << "\n";

    int* ptr = (int*)c.alloc(8 * sizeof(int));

    for(int i {0}; i < 8;i++) {
        std::cout << ptr << "\n";
        ptr[i] = i;
        ptr++;
    }

    return 0;
}
