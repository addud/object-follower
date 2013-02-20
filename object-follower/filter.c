/* ---------------------------------------------------------------------------
 ** filter.c
 **
 ** This file provides filtering methods for the values read from the camera
 **
 ** Author: Adrian Dudau
 ** -------------------------------------------------------------------------*/

#include <stdlib.h>
#include "filter.h"

#define STOPPER 0                                      /* Smaller than any datum */
#define MEDIAN_FILTER_SIZE    (15)						/* Size of the filter window */

/* ---------------------------------------------------------------------------
 ** Implements a median filter for the values read from the camera.
 ** It is currently designed for use with a single stream of values
 ** (from one camera).
 ** It needs to be redesigned for use with multiple cameras
 ** -------------------------------------------------------------------------*/

data_t median_filter(data_t datum) {
	struct pair {
		struct pair *point; /* Pointers forming list linked in sorted order */
		data_t value; /* Values to sort */
	};
	static struct pair buffer[MEDIAN_FILTER_SIZE] = { 0 }; /* Buffer of nwidth pairs */
	static struct pair *datpoint = buffer; /* Pointer into circular buffer of data */
	static struct pair small = { NULL, STOPPER }; /* Chain stopper */
	static struct pair big = { &small, 0 }; /* Pointer to head (largest) of linked list.*/

	struct pair *successor; /* Pointer to successor of replaced data item */
	struct pair *scan; /* Pointer used to scan down the sorted list */
	struct pair *scanold; /* Previous value of scan */
	struct pair *median; /* Pointer to median */
	unsigned int i;

// if (datum == STOPPER)
// {
//   datum = STOPPER + 1;                             /* No stoppers allowed. */
// }

	if ((++datpoint - buffer) >= MEDIAN_FILTER_SIZE) {
		datpoint = buffer; /* Increment and wrap data in pointer.*/
	}

	datpoint->value = datum; /* Copy in new datum */
	successor = datpoint->point; /* Save pointer to old value's successor */
	median = &big; /* Median initially to first in chain */
	scanold = NULL; /* Scanold initially null. */
	scan = &big; /* Points to pointer to first (largest) datum in chain */

	/* Handle chain-out of first item in chain as special case */
	if (scan->point == datpoint) {
		scan->point = successor;
	}
	scanold = scan; /* Save this pointer and   */
	scan = scan->point; /* step down chain */

	/* Loop through the chain, normal loop exit via break. */
	for (i = 0; i < MEDIAN_FILTER_SIZE; ++i) {
		/* Handle odd-numbered item in chain  */
		if (scan->point == datpoint) {
			scan->point = successor; /* Chain out the old datum.*/
		}

		if (scan->value < datum) /* If datum is larger than scanned value,*/
		{
			datpoint->point = scanold->point; /* Chain it in here.  */
			scanold->point = datpoint; /* Mark it chained in. */
			datum = STOPPER;
		};

		/* Step median pointer down chain after doing odd-numbered element */
		median = median->point; /* Step median pointer.  */
		if (scan == &small) {
			break; /* Break at end of chain  */
		}
		scanold = scan; /* Save this pointer and   */
		scan = scan->point; /* step down chain */

		/* Handle even-numbered item in chain.  */
		if (scan->point == datpoint) {
			scan->point = successor;
		}

		if (scan->value < datum) {
			datpoint->point = scanold->point;
			scanold->point = datpoint;
			datum = STOPPER;
		}

		if (scan == &small) {
			break;
		}

		scanold = scan;
		scan = scan->point;
	}
	return median->value;
}

int alfabeta_filter(int dm) {
	//Alfa Beta filter values
	static float dk_1 = 0, vk_1 = 0;
	float a = 0.2, b = 0.00005, dt = 0.05;
	float dk, vk, rk;

	dk = dk_1 + ( vk_1 * dt );
	vk = vk_1;

	rk = dm - dk;

	dk += a * rk;
	vk += ( b * rk ) / dt;

	dk_1 = dk;
	vk_1 = vk;

	return dk;
}

