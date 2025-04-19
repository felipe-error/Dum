#include "Dum/Interface.h"
#include "Dum/List.h"
#include <Dum/Tape.h>

void Swap_MEM_in_TAPE(TAPE *_dest, Memory _mem, MEM_Size _size) {
  _dest->iMem = _mem;
  _dest->mHead = _mem;
  _dest->mSize = _size;
}

void Jump_TAPE(ByteWidth _getSize, MEM_Local _headLocal, MEM_Size _memSize, 
Memory *_head, Memory _mem) {
  if(_getSize < (_memSize - _headLocal)) { 
    *_head = (((Byte*)_mem) + (_headLocal + _getSize));
  } 
}

ERROR Add_Section(TAPE *_ptr, TAPE _src, STATIC_char _secName, ByteWidth _secSize) {
  if(_secSize < TAPE_SCRAPS(_src)) { 
    Section data = { 
	    .iName = _secName,
            .iSize = _secSize,
            .iLocal = TAPE_SIZE(_src) 
    };
    LIST_ADD(_ptr->iSections, &data, sizeof(data));
    _ptr->mHead = (((Byte*)_src.iMem) + (TAPE_SIZE(_src) + _secSize));

    return NO_ERROR;
  } else return 0;
}

