#ifndef TAPES
#define TAPES

#define DUM_EXTYPE
#include <Dum/Interface.h>
#include <Dum/Pool.h>

#ifndef TAPES_TYPES

struct key {
 Bystring iName;
 Bysize iSize;
 Bysize *iTypes;
 Bysize *iTUnits;
};
typedef struct key ByKey;
struct tape {
  ByKey *iSegments;
  ByPool *iMem;
};
typedef struct tape ByTape;

#endif // !TAPES_TYPES

#endif // !TAPES
