#ifndef DUM_INTERFACE
#define DUM_INTERFACE

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef INTERFACE_TYPES 
#define INTERFACE_TYPES

typedef uint64_t Byte8;
typedef uint32_t Byte4;
typedef uint16_t Byte2;
typedef uint8_t  Byte;
typedef void     By404, *Address;
typedef char     Bychar, const *Bystring;
typedef bool     Bybool;
typedef int16_t  Byshort;
typedef float    Byfloat;
typedef int32_t  Byint, Byuint;
typedef size_t   Bysize; 
typedef double   Bydouble;
typedef int64_t  Bylong;


#endif // !INTEFACE_TYPES

#ifndef INTERFACE_MACROS
#define INTERFACE_MACROS

#define COPY_BYTES(dest_, src_) (*(dest_) = (src_))

#define ALLOC_MEM(dest_, count_) ((dest_) = calloc(count_, sizeof(Byte)))
#define FREE(des_) (free(des_))

#define ALLOC_ENDPOINTS(dest_, count_) (dest_ = calloc(count_, sizeof(Byte**))) 

// Navegation In MEM
#define ACCESSIBLE_MEM(head_) ((head_) + sizeof(Byte*))
#define INACCESSIBLE_MEM(head_) ((head_) - sizeof(Byte*))

#define JUMP_INTO_MEM(mem_, blockSize_, count_) ((mem_) + ((blockSize_ + sizeof(Byte*)) * count_))

#define MEM_COPY_BYTE(dest_, src_) (*(dest_) = (src_))
#define MEM_COPY_SHORT(dest_, src_) (*(short*)(dest_) = (src_))
#define MEM_COPY_INT(dest_, src_) (*(int*)(dest_) = (src_))
#define MEM_COPY_FLOAT(dest_, src_) (*(float*)(dest_) = (src_))
#define MEM_COPY_DOUBLE(dest_, src_) (*(double*)(dest_) = (src_))
#define MEM_COPY_LONG(dest_, src_) (*(long long*)(dest_) = (src_))
#define MEM_COPY_PTR(dest_, src_) (*(Byte**)(dest_) = (src_))

#define MEM_READ_BYTE(head_) (*(head_))
#define MEM_READ_SHORT(head_) (*(short*)(head_))
#define MEM_READ_INT(head_) (*(int*)(head_))
#define MEM_READ_FLOAT(head_) (*(float*)(head_))
#define MEM_READ_DOUBLE(head_) (*(double*)(head_))
#define MEM_READ_LONG(head_) (*(long long*)(head_))
#define MEM_READ_PTR(head_) (*(void**)(head_))

#endif // !INTERFACE_MACROS

#endif // !DUM_INTERFACE
