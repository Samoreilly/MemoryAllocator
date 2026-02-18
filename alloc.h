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

    Head* head;  
    AllocUtil util;

public:
    
    Alloc() : head(new Head{}), util(head) {   
        //first block - serves no purpose other than pointing to nodes
        head->ptr = new Block{};
        head->ptr->next = new Block{ 65536, nullptr, nullptr};
    }

    void* alloc(size_t size);
    void freealloc(void* ptr);

};
