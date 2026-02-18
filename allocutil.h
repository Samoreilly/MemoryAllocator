#pragma once

#include <cstddef>

struct Block;
struct Head;

/*
    This class will be used to support alloc.h holding the helper functions
 /
*/

class AllocUtil {

    Head* head;
    int alignment = 8;

public:
    
    AllocUtil(Head* h) : head(h) {}

    void* splitBlock(Block* block, size_t requested_size);
    void removeBlock(Block* block);

};
