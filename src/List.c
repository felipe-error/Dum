#include <Dum/Interface.h>
#include <Dum/List.h>

MEM_Local Cal_HeadPos(Memory _mem, Memory _head, MEM_Size limit) {
  for(Size i = 0; i < limit; i++) {
    if((((Byte*)_mem) + i) == (Byte*)_head)
      return i;
  }
  return HEAD_NOT_FOUND;
}

void Swap_MEM_in_LIST(DynamicalList *_dest, Memory _mem, MEM_Size _size) {
  _dest->iData = _mem;
  _dest->iDtSize = _size;
  _dest->iHead = _mem;
}

void Swap_MEM_and_COPY_in_LIST(DynamicalList *_dest, Memory _mem, MEM_Size _size) {
  if(!((_mem == NULL) && (_size <= 0))) {
    for(Size i = 0; i < (_dest->iDtSize); i++) {
      if(i < _size) 
        MEM_COPY_BYTE((((Byte*)_mem) + i), (((Byte*)_dest) + i)),
	_dest->iHead = (((Byte*)_mem) + i);
    }
    _dest->iData = _mem;
    _dest->iDtSize = _size;
  } else {
     _dest->iData = NULL;
     _dest->iDtSize = 0;
     _dest->iHead = NULL;
  }	
} 

ERROR Add_Element(ByteWidth _dtSize, Data _dt, MEM_Size _size, Memory *_mem) {
  if(_dtSize < _size) {
    for(ByteWidth i = 0; i < _dtSize; i++)
      MEM_COPY_BYTE((((Byte*)*_mem) + i), (((Byte*)_dt) + i));
    *_mem = (((Byte*)*_mem) + _dtSize);
    return NO_ERROR;
  } else return ADD_FAILED; 
}

ERROR Remove_Element(MEM_Local _index, ByteWidth _dtSize, MEM_Size _memSize, Memory *_head, Memory *_mem) {
  if(_index < _memSize) {
    for(Size i = 0; i < _dtSize; i++)
      MEM_COPY_BYTE((((Byte*)*_mem) + i), (((Byte*)*_mem) + (_memSize + i)));
    *_head = (((Byte*)*_mem) + (_memSize - _dtSize)); 
    return NO_ERROR;
  } else return 0;
}



