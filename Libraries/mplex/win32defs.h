/* Win32 compiler dependencies */

# include <sys/types.h>

#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define ssize_t size_t

#ifndef MAXPATHLEN
#define MAXPATHLEN _MAX_PATH
#endif

#define __inline__ inline

#ifndef _INT_TYPES_H_
#define _INT_TYPES_H_
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
#endif

#include <windows.h>