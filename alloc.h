#include <cstddef>


//size if of current block, Block* points to next block of data

struct Block {
    size_t size;
    Block* next;
    Block* prev;
};

struct Start {
    Block* head = nullptr;
};


class Alloc {

public:
    
    void* alloc(size_t size);
    void freealloc(void* ptr);

};
