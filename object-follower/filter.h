/* ---------------------------------------------------------------------------
 ** filter.h
 **
 ** This file provides filtering methods for the values read from the camera
 **
 ** Author: Adrian Dudau
 ** -------------------------------------------------------------------------*/

#ifndef __FILTER_H
#define __FILTER_H

/* Type of filtered data - must be numeric */
typedef U16 data_t;

data_t MedianFilter(data_t datum);

#endif /* __FILTER_H */
