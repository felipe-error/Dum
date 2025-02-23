#include <Dum/Interface.h>
#include <Dum/Pool.h>

By404 allocPool(ByPool *_allo, size_t _size) {
  _allo->iMem = calloc(_size, sizeof(Byte));
  _allo->iHead = _allo->iMem;

  _allo->iEnd = calloc(1, sizeof(Byte**));
  *_allo->iEnd = (_allo->iMem + ((_size) - (sizeof(Byte*) + sizeof(int))));

  for (uint32_t i = 0; i < _size; i++) {
   _allo->iMem[i] = 1;
  }

  Byte **alloPtr = (Byte**)_allo->iMem;
  *alloPtr = NULL;
  alloPtr = (Byte**)*_allo->iEnd;
  *alloPtr = NULL;
}
By404 desallocPool(ByPool *_des) {
  free(_des->iMem);
  free(_des->iEnd);
  _des->iMem = NULL;
  _des->iHead = NULL;
  _des->iEnd = NULL;
}

Address allocBlock(ByPool *_mem) {
  Byte *mem = (_mem->iHead + sizeof(Byte*));
  Byte *nextPtr = *(Byte**)_mem->iHead;

  if (nextPtr != NULL) {
    _mem->iHead = nextPtr;
     return mem;
  }
  return NULL;
}
By404 desallocBlock(Address _memHead, ByPool *_mem) {
  size_t pos = calPos(_memHead, _mem);
  Byte **allocPtr = (Byte**)(_mem->iMem + pos);
  COPY_BYTES(allocPtr,  _mem->iHead);
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
      alloInt = (Byte4*)(_mem->iHead + (sizeof(Byte*) + _blockSize));  
      COPY_BYTES(alloInt, _blockSize);
      _mem->iEnd[blockIndex + 1] = (_mem->iHead + (sizeof(Byte*) + _blockSize));
    } else {
       alloInt = (Byte4*)(_mem->iHead + sizeof(Byte*) + 
        (blockMaxSize - sizeof(Byte4)));  
      COPY_BYTES(alloInt, (blockMaxSize - sizeof(Byte4)));
      _mem->iEnd[blockIndex + 1] = (_mem->iHead + (sizeof(Byte*) + (blockMaxSize - sizeof(Byte4))));
    }
    _mem->iHead = nextPtr;
     return mem;
  }
  return NULL;
}

By404 desallocBlockdy(Address _memHead, ByPool *_mem) {
  size_t pos = calPos(_memHead, _mem);
  Byte **allocPtr = (Byte**)(_mem->iMem + pos);
  COPY_BYTES(allocPtr,  _mem->iHead);
  _mem->iHead = (_mem->iMem + pos);
}

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
  getSize = (int*)(_mem->iMem + (memSize + sizeof(Byte*)));
  return *getSize;
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

By404 stSegmetation(size_t _blockSize, ByPool *_mem) {
  size_t memSize = calPool(_mem);
  Byte **alloPtr;
  Byte4 *alloInt = (Byte4*)(_mem->iMem + (memSize + sizeof(Byte*)));
  COPY_BYTES(alloInt, _blockSize);

  for(uint32_t i = 0; i < floor(((double)memSize / (sizeof(Byte**) + _blockSize))); i++) {
    alloPtr = (Byte**)(_mem->iMem + (sizeof(Byte*) + _blockSize) * i);
    if(i < (floor(((double)memSize / (sizeof(Byte**) + _blockSize))) - 1))
    COPY_BYTES(alloPtr, &_mem->iMem[(sizeof(Byte*) + _blockSize) * (i + 1)]);
    else *alloPtr = NULL;
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
