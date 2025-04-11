#ifndef DUM_INTERFACE
#define DUM_INTERFACE

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef INTERFACE_TYPES 
#define INTERFACE_TYPES

typedef uint64_t           Byte8;
typedef uint32_t           Byte4, uint, ByteWidth;
typedef uint16_t           Byte2;
typedef uint8_t            Byte, Expected;
typedef void               By404,  *Address, *Memory, *Data;
typedef const char*        TEXT_char;
typedef const char* const  STATIC_char;
typedef int8_t             SMALL, int8;
typedef int16_t            SHORT, int16;
typedef int16_t            INT, ERROR, int32;
typedef int64_t            LONG, int64;
typedef size_t             Size, MEM_Local, MEM_Size;

struct supply {
  Data iDt;
  MEM_Size iSize;
};
typedef struct supply Supply;

#endif // !INTEFACE_TYPES

#ifndef INTERFACE_MACROS
#define INTERFACE_MACROS

// Global Macros
#define Section_LIMIT 128

// ERROR's/UTIL CONST's
#define NO_ERROR 0
#define HEAD_NOT_FOUND 0
#define ADD_FAILED 1

#define INVALID_BLOCK NULL
#define FETCH_FAILED NULL

#define COPY_BYTES(dest, src) (*(dest) = (src))

#define ALLOC_MEM(dest, count_) ((dest) = calloc(count_, sizeof(Byte)))
#define FREE(des_) (free(des_))

#define ALLOC_ENDPOINTS(dest, count_) (dest = calloc(count_, sizeof(Byte**))) 

// Navegation In MEM
#define ACCESS_MEM(head) ((head) + sizeof(Byte*))
#define JUMP_INTO_MEM(mem, blockSize, count) ((mem) + ((blockSize + sizeof(Byte*)) * count))

// MEM Operations
#define INTERABLE_MEM(mem) ((Byte*)mem)
#define MEM_COPY_BYTE(dest, src) (*(dest) = *(src))
#define MEM_COPY_SHORT(dest, src) (*(short*)(dest) = (src))
#define MEM_COPY_INT(dest, src) (*(int*)(dest) = (src))
#define MEM_COPY_FLOAT(dest, src) (*(float*)(dest) = (src))
#define MEM_COPY_DOUBLE(dest, src) (*(double*)(dest) = (src))
#define MEM_COPY_LONG(dest, src) (*(long long*)(dest) = (src))
#define MEM_COPY_PTR(dest, src) (*(Byte**)(dest) = (src))

#define MEM_COPY_GENERIC(dest, src, type) (*(type*)dest = (src))


#define MEM_READ_BYTE(head) (*(head))
#define MEM_READ_SHORT(head) (*(short*)(head))
#define MEM_READ_INT(head) (*(int*)(head))
#define MEM_READ_FLOAT(head) (*(float*)(head))
#define MEM_READ_DOUBLE(head) (*(double*)(head))
#define MEM_READ_LONG(head) (*(long long*)(head))
#define MEM_READ_PTR(head) (*(void**)(head))

#define MEM_READ_GENERIC(head, type) (*(type*)dest)

#endif // !INTERFACE_MACROS

#endif // !DUM_INTERFACE
