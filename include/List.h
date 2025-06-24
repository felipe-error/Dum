#ifndef LIST_SYSTEM
#define LIST_SYSTEM

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
typedef struct dyVec DynamicalList, GenericList;

extern MEM_Local Cal_HeadPos(Memory _mem, Memory _head, MEM_Size limit);

extern void Swap_MEM_in_LIST(DynamicalList *_dest, Memory _mem, MEM_Size _size);
extern void Swap_MEM_and_COPY_in_LIST(DynamicalList *_dest, Memory _mem, MEM_Size _size);

extern ERROR Add_Element(ByteWidth _dtSize, Data _dt, MEM_Size _size, Memory *_mem);
extern ERROR Remove_Element(MEM_Local index, ByteWidth _dtSize, MEM_Size _memSize, 
Memory *_head, Memory _mem);

#define MAKE_StaticList(name, type, limit) \
typedef struct { type iData[limit]; MEM_Size iDtSize; type *iHead; } name 

#define MAKE_DynamicalList(name, type) \
typedef struct { type *iData; MEM_Size iDtSize; type *iHead; } name   


#define INIT_StaticList(list) \
(list).iDtSize = sizeof((list).iData); (list).iHead = ((list).iData + 0)  
#define INIT_DynamicalList(list) \
(list).iDtSize = 0; (list).iData = NULL; (list).iHead = NULL

#define LIST_SWAPPER(list, mem, memsize) \
Swap_MEM_in_LIST((DynamicalList*)&list, mem, memsize)

#define LIST_LIMIT(list) \
((list).iDtSize)
#define LISTPTR_LIMIT(list) \
((list)->iDtSize)

#define LIST_SIZE(list) \
(Cal_HeadPos((Memory)(list).iData, (Memory)(list).iHead, (list).iDtSize))
#define LISTPTR_SIZE(list) \
(Cal_HeadPos((Memory)(list)->iData, (Memory)(list)->iHead, (list)->iDtSize))

#define LIST_SCRAPS(list) \
(LIST_LIMIT(list) - LIST_SIZE(list)) 
#define LISTPTR_SCRAPS(list) \
(LISTPTR_LIMIT(list) - LISTPTR_SIZE(list))  

#define DATA_LIST(list, type) \
((type*)list.iData)
#define DATA_LISTPTR(list, type) \
((type*)list->iData)

#define LIST_ADD(list, data, dtsize) \
(Add_Element(dtsize, data, LIST_SCRAPS(list), (Memory*)&list.iHead))
#define LISTPTR_ADD(list, data, dtsize) \
(Add_Element(dtsize, data, LISTPTR_SCRAPS(list), (Memory*)&list->iHead))

#define LIST_REMOVE(list, index, type) \
Remove_Element((index * sizeof(type)), sizeof(type), LIST_SIZE(list), \
(Memory*)&list.iHead, (Memory)list.iData)
#endif // !LIST_SYSTEM
