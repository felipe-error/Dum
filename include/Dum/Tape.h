#ifndef TAPE_SYSTEM
#define TAPE_SYSTEM

#define DUM_EXTYPE
#include <Dum/Interface.h>
#include <Dum/Pool.h>
#include <Dum/List.h>
struct section {
  TEXT_char iName;
  ByteWidth iSize;
  MEM_Local iLocal;
};
typedef struct section Section;
MAKE_StaticList(Section_list, Section, Section_LIMIT);

struct tape {  
  Section_list iSections;
  uint sCount;
  Memory iMem;
  Memory mHead;
  MEM_Size mSize;
};
typedef struct tape TAPE;

void Swap_MEM_in_TAPE(TAPE *_dest, Memory _mem, MEM_Size _size);

Supply Fetch_Element_in_TAPE();

#define INIT_TAPE(tape)                                    \
INIT_StaticList((tape).iSections); (tape).sCount = 0;      \
(tape).iMem = NULL; (tape).mHead = NULL; (tape).mSize = 0 

#define TAPE_SWAPPER(tape, mem, memsize)

#define TAPE_TOTAL(tape) ((tape).mSize)
#define TAPE_SIZE(tape) (())

#define TAPE_ADD(tape, data, dtsize) \
(Add_Element(dtsize,  data, tapem))
#define TAPE_FETCH(tape, text)  

#endif // !TAPE_SYSTEM
