#pragma once

#include "allocutil.h"
#include <cstddef>


//size if of current block, Block* points to next block of data

struct Block {
    size_t size;
    Block* next;
    Block* prev;
};

struct Head {
    Block* ptr = nullptr;
};


class Alloc {

    AllocUtil util;
    //first block - serves no purpose other than pointing to nodes
    Head* head;

public:
    
    void* alloc(size_t size);
    void freealloc(void* ptr);

};
