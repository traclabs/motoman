#ifndef FAKE_MOTOPLUS_TYPES_H__
#define FAKE_MOTOPLUS_TYPES_H__


#include <stdint.h>     // (u)int*_t

#include "mpconstants.h"


// MotoPlus types //////////////////////////////////////////////////////////////

// essentially VxWorks types

typedef int           BOOL;
typedef char          CHAR;
typedef unsigned char UCHAR;
typedef int16_t       SHORT;
typedef uint16_t      USHORT;
typedef int32_t       INT;
typedef uint32_t      UINT;
typedef int32_t       LONG;
typedef uint32_t      ULONG;
typedef int16_t       INT16;
typedef uint16_t      UINT16;
typedef int32_t       INT32;
typedef uint32_t      UINT32;

typedef int STATUS;

// TODO: should args be longs?
typedef int (*FUNCPTR) (int, int, int, int, int, int, int, int, int, int);

typedef int CTRLG_T;

typedef struct
{
  USHORT err_no;
  CHAR reserved[2];
} MP_STD_RSP_DATA;


#endif // FAKE_MOTOPLUS_TYPES_H__
