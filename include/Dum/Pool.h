#ifndef HBYTE_POOL
#define HBYTE_POOL

#include <Dum/Interface.h>

#ifndef MEMORY_POOL
#define MEMORY_POOL

struct memPool {
  Byte *iMem;
  Byte *iHead;
  Byte **iEnd;
};
typedef struct memPool ByPool;


// Alloc/Pool Pool
extern By404 allocPool(ByPool *_allo, size_t _size);
extern By404 desallocPool(ByPool *_des);
// Alloc/Desalloc Blocks
extern Address allocBlockdy(size_t _blockSize, ByPool *_mem);
extern By404 desallocBlockdy(Address _memHead, ByPool *_mem);
extern Address allocBlock(ByPool *_mem);
extern By404 reallocBlock(size_t _resize, Address _memHead, ByPool *_mem);
extern By404 desallocBlock(Address _memHead, ByPool *_mem);
// Calculator Pool Size
extern size_t calPool(ByPool *_mem);
// Calculator Blocks Size
extern size_t calBlock(uint32_t _index, ByPool *_mem);
extern size_t calMaxSize(ByPool *_mem);
extern size_t calSegSize(Address _memHead, ByPool *_mem);
// Calculator Position
extern size_t calPos(Address _memHead, ByPool *_mem);
extern size_t calIndex(Address _memHead, ByPool *_mem);
// Segment Memory
extern By404 dySegmetation(size_t _blockSize, ByPool *_mem);
extern By404 stSegmetation(size_t _blockSize, ByPool *_mem);

#endif // !MEMORY_POOL

#endif // !HBYTE_POOL
