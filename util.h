#ifndef __UTIL_H
#define __UTIL_H

#include <stdint.h>

#ifdef bool
#undefine bool
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define ARR_LEN(n) (sizeof(n) / sizeof(n[0]))

typedef uint8_t       bool;
typedef uint8_t       U8;
typedef uint32_t      U32;

#endif
