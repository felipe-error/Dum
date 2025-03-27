#ifndef TAPE_SYSTEM
#define TAPE_SYSTEM

#define DUM_EXTYPE
#include <Dum/Interface.h>
#include <Dum/Pool.h>
#include <Dum/Vector.h>
struct section {
  TEXT_char iName;
  ByteWidth iSize;
};
typedef struct section Section;
MAKE_StaticVector(Section_list, Section, 256);

struct tape {
  Section_list iSections; 
  TEXT_char iName;
};
typedef struct tape TAPE;


#endif // !TAPE_SYSTEM
