#ifndef BY_VECTOR
#define BY_VECTOR

#include <Dum/Interface.h>

typedef Byte Expected;

struct stVec {
  Expected iData[1];
  Size vSize;
};
typedef struct stVec StaticVector;
struct dyVec {
  Expected *iDtBegin;
  Expected *iDtEnd;
  Size vSize;
};
typedef struct dyVec DynamicalVector;

#define MAKE_StaticVector(name, type, limit) \
typedef struct { type iData[limit]; Size vSize; } StaticVector_##name

#define MAKE_DynamicalVector(name, type) \
typedef struct { type *iDtBegin; type *iDtEnd; Size vSize; } DynamicalVector_##name

#endif // !BY_VECTOR
