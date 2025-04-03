#include <Dum/Interface.h>
#include <Dum/List.h>

MEM_Local cal_HeadPos(Memory _mem, Memory _head, MEM_Size limit) {
  for(Size i = 0; i < limit; i++) {
    if((((Byte*)_mem) + i) == (Byte*)_head)
      return i;
  }
  return HEAD_NOT_FOUND;
}

void swap_HEAD(StaticList *_dest){
  _dest->iHead = ( _dest->iData + 0 ); 
}

void swap_MEM(DynamicalList *_dest, Memory _mem, MEM_Size _size) {
  _dest->iData = _mem;
  _dest->iDtSize = _size;
  _dest->iHead = _mem;
}

/*ERROR add_Element(ByteWidth _dtSize, Data _dt, MEM_Size _size, Memory _mem) {
  if(_dtSize < _size) {
    for(ByteWidth i = 0; i < _dtSize; i++)
      MEM_COPY_BYTE((_mem + i), (_dt + i));
  return NO_ERROR;
  } else return ADD_FAILED; 
}*/



