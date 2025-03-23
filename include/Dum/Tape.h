#ifndef TAPE
#define TAPE

#define DUM_EXTYPE
#include <Dum/Interface.h>
#include <Dum/Pool.h>

struct form {
  Bystring iName;
  Bysize iType;
  Bysize iSlots;
  Byuint iFree;
};
typedef struct form ByForm;
struct tape {
  Bystring iName;
  ByForm *iForm;
  Bysize iScope;
  Bysize iMemSize;
  ByPool iMem;
  Address iHead;
};
typedef struct tape ByTape;

extern Bysize *frMakeSizeList(Bysize _size, ...);
extern Bystring *frMakeNameList(Bysize _size, ...);
extern Bysize *frMakeEstimationSlots(Bysize _size, ...);

extern ByTape allocTape(Bystring *TyName, Bysize *TySize, Bysize *TySlot, Bysize _size, Bystring _name);
extern By404 desallocTape(ByTape *_des);

extern By404 tpSaveMem(ByTape *_mem);
extern By404 tpSaveInFile(ByTape *_mem);
extern Address tpAlloc(Bystring tyName, ByTape *_mem); 
extern By404 tpDesalloc(Bystring tyName, ByTape *_mem);

#endif // !TAPE
