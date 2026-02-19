#pragma once

#include "allocutil.h"
#include <cstddef>
#include <cstdlib>
#include <new>

//size if of current block, Block* points to next block of data

struct Block {
    size_t size;
    Block* next;
    Block* prev;
    bool free {true};
};

struct Head {
    Block* ptr = nullptr;
};


class Alloc {

    Head* head;  
    AllocUtil util;
    char* memory;
    size_t t_size;

public:
    
    Alloc() : head(new Head{}), t_size(65536), util(head) {   

        memory = static_cast<char*>(std::malloc(t_size));

        //first block - serves no purpose other than pointing to nodes
        head = new Head{};
        
        //initialize it to 1 big block of memory (64kb)
        head->ptr = reinterpret_cast<Block*>(memory);
        head->ptr->size = t_size;
        head->ptr->next = nullptr;
        head->ptr->prev = nullptr;
        head->ptr->free = true;

    }

    void* alloc(size_t size);
    void freealloc(void* ptr);

    ~Alloc() {
        std::free(memory);
        delete head;
    }


};
