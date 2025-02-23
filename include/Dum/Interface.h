#ifndef DUM_INTERFACE
#define DUM_INTERFACE

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef INTEFACE_TYPES 
#define INTEFACE_TYPES

typedef uint64_t Byte8;
typedef uint32_t Byte4;
typedef uint16_t Byte2;
typedef uint8_t  Byte;
typedef void     By404, *Address;

#ifdef DUM_EXTYPE

typedef char Bychar, const *Bystring;
typedef bool Bybool;
typedef int16_t Byshort;
typedef float Byfloat;
typedef int32_t Byint;
typedef uint32_t Bysize;
typedef double Bydouble;
typedef int64_t Bylong;

#endif // HBYTE_EXTRA

#endif // !INTEFACE_TYPES

#ifndef DEF_MACROS
#define DEF_MACROS

#endif // !DEF_MACROS

#ifndef FUNC_MACROS
#define FUNC_MACROS

#define COPY_BYTES(dest_, src_) (*(dest_) = (src_))

#endif // !FUNC_MACROS

#endif // !DUM_INTERFACE
