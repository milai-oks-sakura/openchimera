#ifndef _UTIL_MACRO_
#define _UTIL_MACRO_

#define _UNPACK(x) x
#define _TO_STR(x) #x
#define STRING(x) _TO_STR(x)
#define _CONCAT(a, b) a##b
#define CONCAT(a, b) STRING(_CONCAT(a, b))
#define CONCAT_STR(a, b) _UNPACK(a)##_UNPACK(b)

#endif