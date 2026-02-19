#include "allocutil.h"
#include "alloc.h"
#include <iostream>
#include <limits>




/*
    === === === === ALLOCATION CODE === === === ===
*/
void* AllocUtil::allocate(int size) {
    Block* block = head->ptr;

    int aligned_size = ((size + alignment + 1) / alignment) * alignment; 

    Block* free_block = findFreeBlock(aligned_size);
    if(!free_block) {
        std::cout << "No free_block found\n";
        return nullptr;
    }
    
    return removeBlock(free_block, aligned_size); 


}


void* AllocUtil::removeBlock(Block* block, int aligned_size) {

    if(block->size < aligned_size + sizeof(Block)) {

        block->next = nullptr;
        block->prev = nullptr;
        block->free = false;

        return (void*)(block + 1);    
    }


    Block* remainder = (Block*)((char*) (block + 1) + aligned_size);
    remainder->size = block->size - aligned_size - sizeof(Block);

    //replace the old block
    remainder->prev = block->prev;
    remainder->next = block->next;

    if(remainder->prev) {
        block->prev->next = remainder;
    }else {
        head->ptr = remainder;   
    }

    if(remainder->next) {
        block->next->prev = remainder;
    }

    block->size = aligned_size;
    block->next = nullptr;
    block->prev = nullptr;
    block->free = false;
    return (void*)(block + 1);
}

Block* AllocUtil::findFreeBlock(int aligned_size) {
    Block* b = head->ptr;

    Block* largestBlock = b;
    largestBlock->size = std::numeric_limits<int>::lowest();

    while(b) {
        
        if(canSplit(b, aligned_size) && b->free) {
            return b;        
        }   
        
        if((b->size > largestBlock->size) && b->free) {
            largestBlock = b;
        }
        b = b->next;
    }

    std::cout << "No free block found";
    return b->size >= aligned_size ? b : nullptr;
        
}


bool AllocUtil::canSplit(Block* block, int aligned_size) {

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
    
    if(!head->ptr->free || ((char*) block + sizeof(Block) + block->size != (char*) head )) return false;

    head->ptr->size += block->size + sizeof(Block);

    return true;

}

































