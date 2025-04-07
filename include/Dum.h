#ifndef DUM_ALL

#include <DumInterface.h>


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

void swap_MEM_in_TAPE();
ERROR add_Element_in_TAPE(); 

Data fetch_Element_in_TAPE();

#define INIT_TAPE(tape)

#define TAPE_ADD()
#define TAPE_FETCH()

#endif // !TAPE_SYSTEM

#define DUM_ALL
#endif // !DUM_ALL
