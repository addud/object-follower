#ifndef _NXTASSERT_
#define _NXTASSERT_

#include "nxtConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#undef assert
#define assert(exp) nxtAssert(exp)

#ifndef NXT_ASSERT
	#define nxtAssert(p)  	((void)0)
#else
	extern void __nxtAssert(const char *file, int line, const char *exp);
	#define nxtAssert(__e) ((__e) ? (void)0 : __nxtAssert(__FILE__, __LINE__, #__e))
#endif

#ifdef __cplusplus
}
#endif

#endif

