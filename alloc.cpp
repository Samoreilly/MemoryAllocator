#include "alloc.h"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <sys/mman.h>
#include <iostream> 


void* Alloc::alloc(size_t size) {
    Block* block = head->ptr;
    
    while(block->next != nullptr) {

        if(size + sizeof(Block) <= block->size) {
            bool x = util.splitBlock(block);             
        }
    }

    
    return nullptr;

}





void Alloc::freealloc(void* ptr) {



}
