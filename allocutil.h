#pragma once

#include <cstddef>

struct Block;
struct Head;

/*
    This class will be used to support alloc.h holding the helper functions
 /
*/

/*
    When splitting a block up, we must remove the aligned_size and sizeOf(block) from the original block 
    Then set the aligned_block prev, next to nullptr marking it as allocated
*/

class AllocUtil {

public:

    Head* head;
    int alignment = 8;

    
    AllocUtil(Head* h) : head(h) {}

    /*
        === === === === ALLOCATION CODE === === === ===
    */

    void* allocate(size_t size);
    void* splitBlock(Block* free_block, size_t aligned_size);
    void* removeBlock(Block* free_block, size_t aligned_size);
    Block* findFreeBlock(size_t aligned_size); 
    bool canSplit(Block* block, size_t aligned_size);

    /*
        === === === === DE-ALLOCATION CODE === === === ===
    */
    
    void deallocate(void* ptr);
    void relink(Block* block);
    bool coalesceHead(Block* block);

};
