#ifndef POOL
#define POOL

#include <Dum/Interface.h>

#ifndef MEMORY_POOL
#define MEMORY_POOL

typedef Address GenericBlock, DynamicalBlock, StaticBlock;

struct memPool {
  Byte *iMem;
  Byte *iHead;
  Byte **iEnd;
  Size iSize;
};
typedef struct memPool MEM_POOL;

// Alloc/Pool Pool
extern void alloc_MEMPOOL(Size _size, MEM_POOL *_allo);
extern void desalloc_MEMPOOL(MEM_POOL *_des);
// Alloc/Desalloc Blocks
extern DynamicalBlock alloc_DynamicalBlock(int _blockSize, MEM_POOL *_mem);
extern DynamicalBlock realloc_DynamicalBlock(int _resize, DynamicalBlock _memHead, MEM_POOL *_mem);

extern StaticBlock alloc_StaticBlock(int _size, MEM_POOL *_mem);
extern StaticBlock realloc_StaticBlock(int _size, StaticBlock _memHead, MEM_POOL *_mem);

extern void desalloc_Block(GenericBlock _memHead, MEM_POOL *_mem);
// Calculator Blocks Size
extern Size calBlock(uint _index, MEM_POOL *_mem);
extern Size calSegSize(Address _memHead, MEM_POOL *_mem);
// Calculator Position
extern Size calPos(Address _memHead, MEM_POOL *_mem);
extern Size calIndex(Address _memHead, MEM_POOL *_mem);
// Segment Memory
extern void Dynamical_Segmetation(Size _blockSize, MEM_POOL *_mem);
extern void Static_Segmetation(Size _blockSize, MEM_POOL *_mem);

#define INVALID_BLOCK NULL

#define ALLOC_MEMPOOL(pool, size) alloc_MEMPOOL(size, pool)

#define BLOLLOC(type, size, pool) alloc_##type(size, pool) 
#define REBLOC(type, head, size, pool) realloc_##type(size, head, pool)

#define FREE_MEMPOOL(des) desalloc_MEMPOOL(des)
#define FREE_BLOCK(mem, head) desalloc_Block(head, mem)

#define MAX_BLOCK_SIZE(pool) \
MEM_READ_INT(ACCESS_MEM(*pool->iEnd))

#endif // !MEMORY_POOL

#endif // !POOL
