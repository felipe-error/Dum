#ifndef TAPE_SYSTEM
#define TAPE_SYSTEM

#define DUM_EXTYPE
#include <Dum/Interface.h>
#include <Dum/Pool.h>

struct section {
  TEXT_char iName;
};
typedef struct section Section;
struct tape {
  TEXT_char iName;
  Section *iSections;
};
typedef struct tape TAPE;


#endif // !TAPE_SYSTEM
