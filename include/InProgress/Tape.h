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
  Memory iMem;
  Memory mHead;
  MEM_Size mSize;
};
typedef struct tape TAPE;

extern void Swap_MEM_in_TAPE(TAPE *_dest, Memory _mem, MEM_Size _size);

extern Supply Fetch_Element(STATIC_char);

extern ERROR Add_Section(TAPE *_ptr, TAPE _src, STATIC_char _secName, ByteWidth _secSize);

#define INIT_TAPE(tape)             \
INIT_StaticList((tape).iSections);  \
(tape).iMem = NULL; (tape).mHead = NULL; (tape).mSize = 0 

#define TAPE_SWAPPER(tape, mem, memsize) \
Swap_MEM_in_TAPE(&tape, mem, memsize)

#define TAPE_TOTAL(tape) ((tape).mSize)
#define TAPEPTR_TOTAL(tape) ((tape)->mSize)

#define TAPE_SIZE(tape) \
(Cal_HeadPos((tape).iMem, (tape).mHead, (tape).mSize))
#define TAPEPTR_SIZE(tape) \
(Cal_HeadPos((tape)->iMem, (tape)->mHead, (tape)->mSize))

#define TAPE_SCRAPS(tape) \
(TAPE_TOTAL(tape) / TAPE_SIZE(tape)) 
#define TAPEPTR_SCRAPS(tape) \
(TAPEPTR_TOTAL(tape) / TAPEPTR_SIZE(tape)) 

#define TAPE_ADD(tape, sectionname, sectionsize) \
(Add_Section(&(tape), (tape), (sectionname), (sectionsize)));                
#define TAPE_FETCH(tape, text)  

#endif // !TAPE_SYSTEM
