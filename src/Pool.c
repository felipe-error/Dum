#include <Dum/Interface.h>
#include <Dum/Pool.h>
#include <stddef.h>

// Pool Funcs
void Alloc_MEMPOOL(Size _count ,MEM_POOL *_allo) {
  _allo->iSize = (_count - (sizeof(Byte*) + sizeof(int)));

  ALLOC_MEM(_allo->iMem, _count);
  _allo->iHead = _allo->iMem;

  ALLOC_ENDPOINTS(_allo->iEnd, 1);
  *_allo->iEnd = (_allo->iMem + ((_count) - (sizeof(Byte*) + sizeof(int))));

  for (uint32_t i = 0; i < _count; i++) {
   _allo->iMem[i] = 1;
  }

  MEM_COPY_PTR(_allo->iMem, NULL);
  MEM_COPY_PTR(*_allo->iEnd, NULL);

}
void Desalloc_MEMPOOL(MEM_POOL *_des) {
  FREE(_des->iMem);
  FREE(_des->iEnd);
  _des->iMem = NULL;
  _des->iHead = NULL;
  _des->iEnd = NULL;
}

// Block Funcs
StaticBlock Alloc_StaticBlock(ByteWidth _chcsize, MEM_POOL *_mem) {
  if(_chcsize <= MAX_BLOCK_SIZE(_mem)) { 
    Byte *mem = ACCESS_MEM(_mem->iHead);
    Byte *nextPtr = MEM_READ_PTR(_mem->iHead);

    if (nextPtr != NULL) {
      _mem->iHead = nextPtr;
      return mem;
    }
  }
  return INVALID_BLOCK;
}
StaticBlock Realloc_StaticBlock(ByteWidth _chcSize, StaticBlock _memHead, MEM_POOL *_mem) {
  if(_memHead != NULL) {
  Desalloc_Block(_memHead, _mem);
  return BLOLLOC(StaticBlock, _chcSize, _mem);
  } else {
    return NULL;
  }
}

DynamicalBlock Alloc_DynamicalBlock(ByteWidth _blockSize, MEM_POOL *_mem) { 
  ByteWidth bloMax = MAX_BLOCK_SIZE(_mem);
  MEM_Local bloIndex = calIndex(ACCESS_MEM(_mem->iHead), _mem); 
  Byte *mem = ACCESS_MEM(_mem->iHead);
  Byte *memEnd;
  Byte *nextPtr = MEM_READ_PTR(_mem->iHead);

  if (nextPtr != NULL) {
     if(_blockSize < (bloMax - sizeof(Byte4))) {
       memEnd = (mem + (bloMax - sizeof(ByteWidth)));
       MEM_COPY_GENERIC(memEnd, _blockSize, ByteWidth);  
       _mem->iEnd[bloIndex + 1] = memEnd;
    } else {
       memEnd = (mem + (bloMax - sizeof(ByteWidth)));
       MEM_COPY_GENERIC(memEnd, (bloMax - sizeof(ByteWidth)), ByteWidth);  
       _mem->iEnd[bloIndex + 1] = memEnd;
    }
    _mem->iHead = nextPtr;
     return mem;
  }
  return NULL;
}
DynamicalBlock Realloc_DynamicalBlock(ByteWidth _setSize, DynamicalBlock _memHead, MEM_POOL *_mem) {
   if(_memHead != NULL) {
  Desalloc_Block(_memHead, _mem);
  return BLOLLOC(DynamicalBlock, _setSize, _mem);
  } else {
    return NULL;
  }	
}


void Desalloc_Block(GenericBlock _memHead, MEM_POOL *_mem) {
  Size pos = calPos(_memHead, _mem);
  MEM_COPY_PTR((_mem->iMem + pos), _mem->iHead);
  _mem->iHead = (_mem->iMem + pos);
}

// Calculator Funcs
Size calBlock(uint _index, MEM_POOL *_mem) {
  int *getSize;
  Size memSize = _mem->iSize;

  for (int i = 0; i < memSize; i++) {
    if((_mem->iMem + i) == *(_mem->iEnd + _index)) {
      getSize = (int*)(_mem->iMem + (i));
      return *getSize;
    }
  }
  return 0;
}
Size calSegSize(Address _memHead, MEM_POOL *_mem) {
  return calBlock(calIndex(_memHead, _mem) + 1, _mem);
}

Size calPos(Address _memHead, MEM_POOL *_mem) {
  Size blockSize = MAX_BLOCK_SIZE(_mem); 
  Size memSize = _mem->iSize;

  for (uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte*) + blockSize))); i++) {
    if((_mem->iMem + ((sizeof(Byte*) + blockSize) * i) + sizeof(Byte*)) == _memHead)
      return ((sizeof(Byte*) + blockSize) * i);
  }

  return 0;
}
Size calIndex(Address _memHead, MEM_POOL *_mem) {
  Size blockSize = MAX_BLOCK_SIZE(_mem); 
  Size memSize = _mem->iSize;

  for (uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte*) + blockSize))); i++) {
    if((_mem->iMem + ((sizeof(Byte*) + blockSize) * i) + sizeof(Byte*)) == _memHead)
      return (i);
  }

  return 0;
}


void MEM_Segmetation(ByteWidth _blockSize, MEM_POOL *_mem) {
  MEM_Size memSize = _mem->iSize;
  MEM_COPY_GENERIC(JUMP_INTO_MEM(_mem->iMem, memSize, 1), _blockSize, ByteWidth);

  Byte **endpoints = calloc((Size)
                           floor(((double)memSize / 
                                 (sizeof(Byte**) + _blockSize))) + 1, sizeof(Byte*));
  endpoints[0] = *_mem->iEnd;
  free(_mem->iEnd);
  _mem->iEnd = endpoints;

  for(uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte**) + _blockSize))); i++) {
    if(i < (floor(((double)memSize / (sizeof(Byte*) + _blockSize))) - 1))
      MEM_COPY_PTR(
      JUMP_INTO_MEM(_mem->iMem, _blockSize, (i)), 
      JUMP_INTO_MEM(_mem->iMem, _blockSize, (i + 1))); 
    else 
      MEM_COPY_PTR(
      JUMP_INTO_MEM(_mem->iMem, _blockSize, i), 
      NULL); 
  }
}
