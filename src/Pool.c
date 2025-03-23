#include <Dum/Interface.h>
#include <Dum/Pool.h>
#include <stddef.h>

// Pool Funcs
By404 allocPool(ByPool *_allo, Bysize _count) {
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
By404 desallocPool(ByPool *_des) {
  FREE(_des->iMem);
  FREE(_des->iEnd);
  _des->iMem = NULL;
  _des->iHead = NULL;
  _des->iEnd = NULL;
}

// Block Funcs
Address allocBlock(ByPool *_mem) {
  Byte *mem = ACCESSIBLE_MEM(_mem->iHead);
  Byte *nextPtr = MEM_READ_PTR(_mem->iHead);

  if (nextPtr != NULL) {
    _mem->iHead = nextPtr;
     return mem;
  }
  return NULL;
}
By404 desallocBlock(Address _memHead, ByPool *_mem) {
  size_t pos = calPos(_memHead, _mem);
  MEM_COPY_PTR((_mem->iMem + pos), _memHead);
  _mem->iHead = (_mem->iMem + pos);
}

Address allocBlockdy(size_t _blockSize, ByPool *_mem) { 
  size_t blockMaxSize = calMaxSize(_mem); 
  Byte4 *alloInt;
  Byte *mem = (_mem->iHead + sizeof(Byte*));
  Byte *nextPtr = *(Byte**)_mem->iHead;

  size_t blockIndex = calIndex(mem, _mem); 

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
By404 reallocBlock(size_t _resize, Address _memHead, ByPool *_mem) {
  size_t memPos = calPos(_memHead, _mem);
  size_t blockMaxSize = calMaxSize(_mem);
  Byte4 *allocInt = (Byte4*)(_mem->iMem + (sizeof(Byte*)) + 
    (memPos + (blockMaxSize - sizeof(Byte4))));
  *allocInt = _resize;
}

By404 desallocBlockdy(Address _memHead, ByPool *_mem) {
  size_t pos = calPos(_memHead, _mem);
  Byte **allocPtr = (Byte**)(_mem->iMem + pos);
  COPY_BYTES(allocPtr,  _mem->iHead);
  _mem->iHead = (_mem->iMem + pos);
}

// Calculator Funcs
size_t calPool(ByPool *_mem) {
  for (uint32_t i = 0; true; i++) {
    if ((_mem->iMem + i) == *_mem->iEnd)
      return i;
  }
  return 0;
}
size_t calBlock(uint32_t _index, ByPool *_mem) {
  int *getSize;
  size_t memSize = calPool(_mem);

  for (uint32_t i = 0; i < memSize; i++) {
    if((_mem->iMem + i) == *(_mem->iEnd + _index)) {
      getSize = (int*)(_mem->iMem + (i));
      return *getSize;
    }
  }
  return 0;
}
size_t calMaxSize(ByPool *_mem) {
  int *getSize;
  size_t memSize = calPool(_mem);

  getSize = (int*)(_mem->iMem + (memSize + sizeof(Byte*)));
  return *getSize;
}
size_t calSegSize(Address _memHead, ByPool *_mem) {
  return calBlock(calIndex(_memHead, _mem) + 1, _mem);
}

size_t calPos(Address _memHead, ByPool *_mem) {
  size_t blockSize = calMaxSize(_mem); 
  size_t memSize = calPool(_mem);

  for (uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte*) + blockSize))); i++) {
    if((_mem->iMem + ((sizeof(Byte*) + blockSize) * i) + sizeof(Byte*)) == _memHead)
      return ((sizeof(Byte*) + blockSize) * i);
  }

  return 0;
}
size_t calIndex(Address _memHead, ByPool *_mem) {
  size_t blockSize = calMaxSize(_mem); 
  size_t memSize = calPool(_mem);

  for (uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte*) + blockSize))); i++) {
    if((_mem->iMem + ((sizeof(Byte*) + blockSize) * i) + sizeof(Byte*)) == _memHead)
      return (i);
  }

  return 0;
}


// Segment Funcs
By404 stSegmetation(Bysize _bSize, ByPool *_mem) {
  size_t memSize = calPool(_mem);
  MEM_COPY_INT((_mem->iMem + (memSize + sizeof(Byte*))), _bSize);

  for(uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte**) + _bSize))); i++) {
    if(i < (floor(((double)memSize / (sizeof(Byte**) + _bSize))) - 1))
    MEM_COPY_PTR(JUMP_INTO_MEM(_mem->iMem, _bSize, i), JUMP_INTO_MEM(_mem->iMem, _bSize, (i + 1)));
    else MEM_COPY_PTR(JUMP_INTO_MEM(_mem->iMem, _bSize, i), NULL);
  }
}

By404 dySegmetation(size_t _blockSize, ByPool *_mem) {
  size_t memSize = calPool(_mem);
  Byte **alloPtr;
  Byte4 *alloInt = (Byte4*)(_mem->iMem + (memSize + sizeof(Byte*)));
  COPY_BYTES(alloInt, _blockSize);

  Byte **endpoints = calloc((size_t)
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
