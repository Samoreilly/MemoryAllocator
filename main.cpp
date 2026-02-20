#include "alloc.h"
#include <iostream>
#include <iterator>
#include <memory>

int main() {

    Alloc c;


    int* ptr1 = (int*)c.alloc(8 * sizeof(int));
    if (!ptr1) {
        std::cout << "Allocation failed\n";
        return 1;
    }
    std::cout << "Allocated 8 ints at: " << ptr1 << "\n";
   
    for (int i = 0; i < 8; i++) {
        ptr1[i] = i * 10;
    }
    for (int i = 0; i < 8; i++) {
        std::cout << &ptr1[i] << " = " << ptr1[i] << "\n";
    }

    std::cout << "Freeing ptr1\n";
    c.freealloc(ptr1);

    std::cout << "\nTesting reuse of memory:\n";

    // Allocating again should reuse the same block (or part of it)
    int* ptr2 = (int*)c.alloc(8 * sizeof(int));
     if (!ptr2) {
        std::cout << "Reuse allocation failed!\n";
        return 1;
    }
    std::cout << "Allocated 8 ints at: " << ptr2 << "\n";

    if (ptr1 == ptr2) {
        std::cout << "Memory block was reused\n";
    }
    std::cout << "\n--- Split Test ---\n";
   
    c.freealloc(ptr2);
    
    std::cout << "Allocating 2 blocks half the size\n";
    int* ptr3 = (int*)c.alloc(4 * sizeof(int));
    std::cout << "Allocated 4 ints at: " << ptr3 << "\n";
    
    // Allocate remainder
    int* ptr4 = (int*)c.alloc(4 * sizeof(int));
    std::cout << "Allocated 4 ints at: " << ptr4 << "\n";

    int* ptr5 = (int*) c.alloc(20 * sizeof(int));
    
    std::cout << ptr5 << "\n";


    c.freealloc(ptr5);
    c.freealloc(ptr3);
    c.freealloc(ptr4);

    return 0;
}
