#ifndef BY_LIST
#define BY_LIST

#include <Dum/Interface.h>

struct stVec {
  Expected iData[1];
  MEM_Size iDtSize;
  Expected *iHead;
};
typedef struct stVec StaticList;
struct dyVec {
  Expected *iData;
  MEM_Size iDtSize;
  Expected *iHead;
};
typedef struct dyVec DynamicalList;

extern MEM_Local cal_HeadPos(Memory _mem, Memory _head, MEM_Size limit);

extern void swap_MEM(DynamicalList *_dest, Memory _mem, MEM_Size _size);
extern void swap_MEM_and_COPY(DynamicalList *_dest, Memory _mem, MEM_Size _size);

extern ERROR add_Element_in_List(ByteWidth _dtSize, Data _dt, MEM_Size _size, Memory *_mem);

#define MAKE_StaticList(name, type, limit) \
typedef struct { type iData[limit]; MEM_Size iDtSize; type *iHead; } name 

#define MAKE_DynamicalList(name, type) \
typedef struct { type *iData; MEM_Size iDtSize; type *iHead; } name   


#define INIT_StaticList(list) \
(list).iDtSize = sizeof((list).iData); (list).iHead = ((list).iData + 0)  
#define INIT_DynamicalList(list) \
(list).iDtSize = 0; (list).iData = NULL; (list).iHead = NULL

#define List_LIMIT(list) \
((list).iDtSize)

#define List_SIZE(list) \
(cal_HeadPos((Memory)(list).iData, (Memory)(list).iHead, (list).iDtSize))

#define SCRAPS(list) \
(List_LIMIT(list) - List_SIZE(list))  

#define GET_ARRAY(list) \
(list.iData)
#define List_ADD(list, data, type) \
(add_Element_In_List(sizeof(type), data, SCRAPS(list), (Memory*)&list.iHead))


#endif // !BY_LIST
