#include "allocutil.h"
#include "alloc.h"

void* AllocUtil::splitBlock(Block* block, size_t requested_size) {
    
    int remaining_space = block->size - requested_size;

    int aligned_size = ((requested_size + alignment - 1) / alignment) * alignment;

    //return full block as aligned is too big
    if(aligned_size >= block->size) {
        //TODO: removeblock
        return (void*) (block + 1);
    }

    block->size -= aligned_size;


    
}



void AllocUtil::removeBlock(Block* block) {

    if(block->prev) {
        block->prev->next = block->next;
    }else {
        head->ptr = block->next;
    }


    if(block->prev) {
        
        if(block->next) {
            block->prev->next = block->next;
            block->next->prev = block->prev;
        }else {
            block->prev->next = nullptr;
        }
    }
}
