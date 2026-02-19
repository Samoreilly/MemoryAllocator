#include "allocutil.h"
#include "alloc.h"
#include <iostream>





/*
    === === === === ALLOCATION CODE === === === ===
*/
void* AllocUtil::allocate(size_t size) {
    Block* block = head->ptr;

    size_t aligned_size = ((size + alignment - 1) / alignment) * alignment; 

    Block* free_block = findFreeBlock(aligned_size);
    if(!free_block) {
        std::cout << "No free_block found\n";
        return nullptr;
    }
    
    return removeBlock(free_block, aligned_size); 


}


void* AllocUtil::removeBlock(Block* block, size_t aligned_size) {

    size_t original_size = block->size;

    if(block->size < aligned_size + sizeof(Block)) {
        block->free = false;
        return (void*)(block + 1);    
    }


    Block* remainder = (Block*)((char*) block + aligned_size + sizeof(Block));
    remainder->size = original_size - aligned_size - sizeof(Block);
    remainder->free = true;
  
    
    remainder->next = block->next;
    remainder->prev = block;

    if(block->next) {
        block->next->prev = remainder;
    }

    block->next = remainder;
    block->size = aligned_size;
    block->free = false;

    return (void*)(block + 1);
}

Block* AllocUtil::findFreeBlock(size_t aligned_size) {
    Block* b = head->ptr;

    while(b) {
        
        if(canSplit(b, aligned_size) && b->free) {
            return b;        
        }   
        
        b = b->next;
    }

    std::cout << "No free block found";
    return nullptr;
        
}


bool AllocUtil::canSplit(Block* block, size_t aligned_size) {

    return block->size >= aligned_size;
}

/*
    === === === === DE-ALLOCATION CODE === === === ===
*/

void AllocUtil::deallocate(void* ptr) {

    //get header
    Block* block = (Block*) ptr - 1;
    block->free = true;          
    
    coalesce(block);

}

void AllocUtil::coalesce(Block* block) {
    Block* b = block;

    // merge forward
    while(b->next && b->next->free &&
          (char*)b + sizeof(Block) + b->size == (char*)b->next) {
        
        Block* next = b->next;
        b->size += sizeof(Block) + next->size;
        b->next = next->next;

        if(b->next) {
            b->next->prev = b;
        }
    }

    // merge backward
    while(b->prev && b->prev->free &&
          (char*)b->prev + sizeof(Block) + b->prev->size == (char*)b) {
        
        Block* prev = b->prev;

        prev->size += sizeof(Block) + b->size;
        prev->next = b->next;
        
        if(b->next) {
            b->next->prev = prev;
        }
        b = prev;
    }
}

