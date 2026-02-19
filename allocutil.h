#pragma once

#include <cstddef>

struct Block;
struct Head;

/*
    This class will be used to support alloc.h holding the helper functions
 /
*/

class AllocUtil {

public:

    Head* head;
    int alignment = 8;

    
    AllocUtil(Head* h) : head(h) {}

    void* allocate(int size);
    void* splitBlock(Block* free_block, int aligned_size);
    void* removeBlock(Block* free_block, int aligned_size);
    Block* findFreeBlock(int aligned_size); 
    bool canSplit(Block* block, int aligned_size);


    /*
        When splitting a block up, we must remove the aligned_size and sizeOf(block) from the original block 
        Then set the aligned_block prev, next to nullptr marking it as allocated
    */
};
