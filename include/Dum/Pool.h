#ifndef POOL
#define POOL

#include <Dum/Interface.h>

#ifndef MEMORY_POOL
#define MEMORY_POOL

typedef Memory GenericBlock, DynamicalBlock, StaticBlock;

struct memPool {
  Byte *iMem;
  Byte *iHead;
  Byte **iEnd;
  Size iSize;
};
typedef struct memPool MEM_POOL;

// Alloc/Pool Pool
extern void Alloc_MEMPOOL(Size _size, MEM_POOL *_allo);
extern void Desalloc_MEMPOOL(MEM_POOL *_des);
// Alloc/Desalloc Blocks
extern DynamicalBlock Alloc_DynamicalBlock(ByteWidth _setSize, MEM_POOL *_mem);
extern DynamicalBlock Realloc_DynamicalBlock(ByteWidth _setSize, DynamicalBlock _memHead, MEM_POOL *_mem);

extern StaticBlock Alloc_StaticBlock(ByteWidth _chcSize, MEM_POOL *_mem);
extern StaticBlock Realloc_StaticBlock(ByteWidth _chcSize, StaticBlock _memHead, MEM_POOL *_mem);

extern void Desalloc_Block(GenericBlock _memHead, MEM_POOL *_mem);

// Calculator Blocks Size
extern Size calBlock(uint _index, MEM_POOL *_mem);
extern Size calSegSize(Address _memHead, MEM_POOL *_mem);
// Calculator Position
extern Size calPos(Address _memHead, MEM_POOL *_mem);
extern Size calIndex(Address _memHead, MEM_POOL *_mem);
// Segment Memory
extern void MEM_Segmetation(ByteWidth _blockSize, MEM_POOL *_mem);

#define ALLOC_MEMPOOL(pool, size) Alloc_MEMPOOL(size, pool)

#define BLOLLOC(type, size, pool) Alloc_##type(size, pool) 
#define REBLOC(type, head, size, pool) realloc_##type(size, head, pool)

#define FREE_MEMPOOL(des) Desalloc_MEMPOOL(des)
#define FREE_BLOCK(mem, head) Desalloc_Block(head, mem)

#define MAX_BLOCK_SIZE(pool) \
MEM_READ_INT(ACCESS_MEM(*pool->iEnd))

#define SEGMENT(pool, bytewidth) \
MEM_Segmetation(bytewidth, pool)

#endif // !MEMORY_POOL

#endif // !POOL
