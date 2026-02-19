#include "alloc.h"
#include <iostream>
#include <iterator>

int main() {

    Alloc c;
    std::cout << "\n";


    int* ptr = (int*)c.alloc(8 * sizeof(int));
   
    for (int i = 0; i < 1000; i++) {
        ptr[i] = i * 10;
    }

    for (int i = 0; i < 50; i++) {
        std::cout << &ptr[i] << " = " << ptr[i] << "\n";
    }

    c.freealloc(ptr);


    return 0;
}
