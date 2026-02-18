
Intrusive free-list - sort by address
Easy for memory coalescing (merging memory blocks)


|      |     |  100  |     |   200   |
| HEAD | <-> | BLOCK | <-> |  BLOCK  |
|      |     |       |     |         |


# Implementing a First-fit


## Plan 
Initially there is one big contigious block of memoryo, when a user requests
a block of memory, a block of that size  is removed from the free-list

When deallocation is called that block is appended back into the block



alloc(size_t size):

find a free chunk that is (free chunk >= requested size + block size)
and if free chunk minus (requested size + block size) is greater than or equal to
32, split the chunk to avoid wasted memory


