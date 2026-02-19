#include "alloc.h"
#include "allocutil.h"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <sys/mman.h>
#include <iostream> 


void* Alloc::alloc(size_t size) {
    return util.allocate(size);
}

void Alloc::freealloc(void* ptr) {
    return util.deallocate(ptr);
}
