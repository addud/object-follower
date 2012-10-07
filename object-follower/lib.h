/* ---------------------------------------------------------------------------
 ** filter.h
 **
 ** This file provides filtering methods for the values read from the camera
 **
 ** Author: Adrian Dudau
 ** -------------------------------------------------------------------------*/


#ifndef LIB_H_
#define LIB_H_

#define MAX(a,b)         ((a < b) ?  (b) : (a))
#define MIN(a,b)         ((a > b) ?  (b) : (a))
#define ABS(x)           (((x) < 0) ? -(x) : (x))

int fisqrt(int val);

#endif /* LIB_H_ */
