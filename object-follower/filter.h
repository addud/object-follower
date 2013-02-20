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
typedef int data_t;

data_t median_filter(data_t datum);
int alfabeta_filter(int dm);



#endif /* __FILTER_H */

