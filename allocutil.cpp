#include "allocutil.h"
#include "alloc.h"
#include <iostream>
#include <limits>




/*
    === === === === ALLOCATION CODE === === === ===
*/
void* AllocUtil::allocate(size_t size) {
    Block* block = head->ptr;

    int aligned_size = ((size + alignment - 1) / alignment) * alignment; 

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
        return (void*)(block + 1);    
    }


    Block* remainder = (Block*)((char*) block + 1 + aligned_size);
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

    Block* largestBlock = nullptr;
    int maxSize = std::numeric_limits<int>::lowest();

    while(b) {
        
        if(canSplit(b, aligned_size) && b->free) {
            return b;        
        }   
        
        if((b->size > maxSize) && b->free) {
            largestBlock = b;
            maxSize = b->size;
        }
        b = b->next;
    }

    std::cout << "No free block found";
    return nullptr;
        
}


bool AllocUtil::canSplit(Block* block, size_t aligned_size) {

    return aligned_size <= block->size; 
}

/*
    === === === === DE-ALLOCATION CODE === === === ===
*/

void AllocUtil::deallocate(void* ptr) {

    //get header
    Block* block = (Block*) ptr - 1;

    relink(block);

}


//relink node at head
void AllocUtil::relink(Block* block) {
    
    if (head->ptr) {
               
        if(coalesceHead(block)) {

            std::cout << "Coalesced at head\n";
            //block merged, no need to manage pointers
            return;
        }

        head->ptr->prev = block;
    }

    block->next = head->ptr;
    block->prev = nullptr;


    head->ptr = block;

}

//merge deallocated block with 1st node if free
bool AllocUtil::coalesceHead(Block* block) {
    
    Block* curr = head->ptr;
    
    char* block_bytes = ((char*) block + sizeof(Block) + block->size);
    
    while(curr) {
        
        if(curr->free && block_bytes == (char*) curr) {
            curr->size += block->size + sizeof(Block);
            
            std::cout << "Coalescing\n";
            return true;
        }

        curr = curr->next;
    
    }

    std::cout << "No coalescing made\n";
    return false;

}

































