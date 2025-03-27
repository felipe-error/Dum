#ifndef BY_VECTOR
#define BY_VECTOR

#include <Dum/Interface.h>

struct stVec {
  Expected iData[1];
  Expected *iHead;
};
typedef struct stVec StaticVector, stVec;
struct dyVec {
  Expected *iDtBegin;
  Expected *iDtEnd;
  Expected *iHead;
};
typedef struct dyVec DynamicalVector, dyVec;

extern Size get_ArraySize(Memory _begin, Memory _end);

extern Size StaticVector_Limit(StaticVector *_get) { return 0; }
extern Size DynamicalVector_Limit(DynamicalVector *_get) { return 1; } 

extern void swap_MEM(DynamicalVector *_dest, Memory _mem);
extern void swap_MEM_and_COPY(DynamicalVector *_dest, Memory _mem, Size _memSize);

#define MAKE_StaticVector(name, type, limit) \
typedef struct { type iData[limit]; Expected iHead; } name

#define MAKE_DynamicalVector(name, type) \
typedef struct { type *iDtBegin; type *iDtEnd; } name   

#define Vector_LIMIT(vector, type) (_Generic((vector),                    \
StaticVector* : StaticVector_Limit,                                       \
DynamicalVector* : DynamicalVector_Limit                                  \
)(vector) / sizeof(type))
#define Vector_SIZE(vector, type) (get_ArraySize(_Generic((vector),       \
StaticVector* : (vector.iData + sizeof(type)),                            \
DynamicalVector* : (vector.iDtBegin + sizeof(type))                       \
), vector.iHead) / sizeof(type))

#define VECTOR(vector, type) ( _Generic((vector),                         \
StaticVector* : (type*)vector.iData,                                      \
DynamicalVector* : (Type*)vector;iDtBegin                                 \
))

#endif // !BY_VECTOR
