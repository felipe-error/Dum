#ifndef POOL
#define POOL

#include <Dum/Interface.h>

#ifndef MEMORY_POOL
#define MEMORY_POOL

struct memPool {
  Byte *iMem;
  Byte *iHead;
  Byte **iEnd;
};
typedef struct memPool MEM_POOL;


// Alloc/Pool Pool
extern void alloc_MEMPOOL(Size _size, MEM_POOL *_allo);
extern void desalloc_MEMPOOL(MEM_POOL *_des);
// Alloc/Desalloc Blocks
extern Address allocBlockdy(int _blockSize, MEM_POOL *_mem);
extern void reallocBlock(int _resize, Address _memHead, MEM_POOL *_mem);
extern void desallocBlockdy(Address _memHead, MEM_POOL *_mem);
extern Address stAllocBlock(MEM_POOL *_mem);
extern void stDesallocBlock(Address _memHead, MEM_POOL *_mem);
// Calculator Pool Size
extern Size calPool(MEM_POOL *_mem);
// Calculator Blocks Size
extern Size calBlock(uint32_t _index, MEM_POOL *_mem);
extern Size calMaxSize(MEM_POOL *_mem);
extern Size calSegSize(Address _memHead, MEM_POOL *_mem);
// Calculator Position
extern Size calPos(Address _memHead, MEM_POOL *_mem);
extern Size calIndex(Address _memHead, MEM_POOL *_mem);
// Segment Memory
extern By404 Dynamical_Segmetation(Size _blockSize, MEM_POOL *_mem);
extern By404 Static_Segmetation(Size _blockSize, MEM_POOL *_mem);

#define ALLOC_MEMPOOL(pool, size) alloc_MEMPOOL(size, pool)
#define FREE_MEMPOOL(des) desalloc_MEMPOOL(des)

#endif // !MEMORY_POOL

#endif // !POOL
