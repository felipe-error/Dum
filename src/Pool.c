#include <Dum/Interface.h>
#include <Dum/Pool.h>
#include <stddef.h>

// Pool Funcs
void alloc_MEMPOOL(Size _count ,MEM_POOL *_allo) {
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
void desalloc_MEMPOOL(MEM_POOL *_des) {
  FREE(_des->iMem);
  FREE(_des->iEnd);
  _des->iMem = NULL;
  _des->iHead = NULL;
  _des->iEnd = NULL;
}

// Block Funcs
StaticBlock alloc_StaticBlock(int _size, MEM_POOL *_mem) {
  if(_size <= MAX_BLOCK_SIZE(_mem)) { 
    Byte *mem = ACCESS_MEM(_mem->iHead);
    Byte *nextPtr = MEM_READ_PTR(_mem->iHead);

    if (nextPtr != NULL) {
      _mem->iHead = nextPtr;
      return mem;
    }
  }
  return INVALID_BLOCK;
}
void Desalloc_Block(GenericBlock _memHead, MEM_POOL *_mem) {
  Size pos = calPos(_memHead, _mem);
  MEM_COPY_PTR((_mem->iMem + pos), _mem->iHead);
  _mem->iHead = (_mem->iMem + pos);
}

DynamicalBlock alloc_DynamicalBlock(int _blockSize, MEM_POOL *_mem) { 
  Size blockMaxSize = MAX_BLOCK_SIZE(_mem); 
  Byte4 *alloInt;
  Byte *mem = (_mem->iHead + sizeof(Byte*));
  Byte *nextPtr = *(Byte**)_mem->iHead;

  Size blockIndex = calIndex(mem, _mem); 

  if (nextPtr != NULL) {
     if(_blockSize < (blockMaxSize - sizeof(Byte4))) {
      alloInt = (Byte4*)(_mem->iHead + (sizeof(Byte*) + 
      (blockMaxSize - sizeof(Byte4))));  
      COPY_BYTES(alloInt, _blockSize);
      _mem->iEnd[blockIndex + 1] = (_mem->iHead + (sizeof(Byte*) +
        (blockMaxSize - sizeof(Byte4))));
    } else {
       alloInt = (Byte4*)(_mem->iHead + sizeof(Byte*) + 
        (blockMaxSize - sizeof(Byte4)));  
      COPY_BYTES(alloInt, (blockMaxSize - sizeof(Byte4)));
      _mem->iEnd[blockIndex + 1] = (_mem->iHead + (sizeof(Byte*) +
        (blockMaxSize - sizeof(Byte4))));
    }
    _mem->iHead = nextPtr;
     return mem;
  }
  return NULL;
}
void reallocBlock(int _resize, Address _memHead, MEM_POOL *_mem) {
  Size memPos = calPos(_memHead, _mem);
  Size blockMaxSize = MAX_BLOCK_SIZE(_mem);
  Byte4 *allocInt = (Byte4*)(_mem->iMem + (sizeof(Byte*)) + 
    (memPos + (blockMaxSize - sizeof(Byte4))));
  *allocInt = _resize;
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


// Segment Funcs
void Static_Segmetation(Size _bSize, MEM_POOL *_mem) {
  Size memSize = _mem->iSize;
  MEM_COPY_INT((_mem->iMem + (memSize + sizeof(Byte*))), _bSize);

  for(uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte**) + _bSize))); i++) {
    if(i < (floor(((double)memSize / (sizeof(Byte**) + _bSize))) - 1))
    MEM_COPY_PTR(JUMP_INTO_MEM(_mem->iMem, _bSize, i), JUMP_INTO_MEM(_mem->iMem, _bSize, (i + 1)));
    else MEM_COPY_PTR(JUMP_INTO_MEM(_mem->iMem, _bSize, i), NULL);
  }
}

void Dynamical_Segmetation(Size _blockSize, MEM_POOL *_mem) {
  Size memSize = _mem->iSize;
  Byte **alloPtr;
  Byte4 *alloInt = (Byte4*)(_mem->iMem + (memSize + sizeof(Byte*)));
  COPY_BYTES(alloInt, _blockSize);

  Byte **endpoints = calloc((Size)
                           floor(((double)memSize / 
                                 (sizeof(Byte**) + _blockSize))) + 1, sizeof(Byte*));
  endpoints[0] = *_mem->iEnd;
  free(_mem->iEnd);
  _mem->iEnd = endpoints;

  for(uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte**) + _blockSize))); i++) {
    alloPtr = (Byte**)(_mem->iMem + (sizeof(Byte*) + _blockSize) * i);
    if(i < (floor(((double)memSize / (sizeof(Byte*) + _blockSize))) - 1))
      COPY_BYTES(alloPtr, &_mem->iMem[(sizeof(Byte*) + _blockSize) * (i + 1)]); 
    else *alloPtr = NULL;
  }
}
