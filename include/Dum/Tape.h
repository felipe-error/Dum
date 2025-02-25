#ifndef TAPE
#define TAPE

#define DUM_EXTYPE
#include <Dum/Interface.h>
#include <Dum/Pool.h>

struct form {
 Bysize iSize;
 Bysize *iTypes;
 Bysize *iTSlots;
 Bysize *ITSize;
};
typedef struct form ByForm;
struct tape {
  Bystring iName;
  ByForm iForm;
  Address iHead;
  ByPool iMem;
};
typedef struct tape ByTape;

#endif // !TAPE
