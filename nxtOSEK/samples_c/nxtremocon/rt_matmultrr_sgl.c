/* Copyright 1994-2006 The MathWorks, Inc.
 *
 * File: rt_matmultrr_sgl.c     $Revision: 1.3.4.1 $
 *
 * Abstract:
 *      Real-Time Workshop support routine for matrix multiplication
 *      of two real single precision float operands
 *
 */

#include "rtlibsrc.h"

/*
 * Function: rt_MatMultRR_Sgl
 * Abstract:
 *      2-input matrix multiply function
 *      Input 1: Real, single-precision
 *      Input 2: Real, single-precision
 */
void rt_MatMultRR_Sgl(real32_T       *y,
                      const real32_T *A,
                      const real32_T *B,
                      const int_T      dims[3])
{
  int_T k;
  for(k=dims[2]; k-- > 0; ) {
    const real32_T *A1 = A;
    int_T i;
    for(i=dims[0]; i-- > 0; ) {
      const real32_T *A2 = A1;
      const real32_T *B1 = B;
      real32_T acc = (real32_T)0.0;
      int_T j;
      A1++;
      for(j=dims[1]; j-- > 0; ) {
        acc += *A2 * *B1;
        B1++;
        A2 += dims[0];
      }
      *y++ = acc;
    }
    B += dims[1];
  }
}

/* [EOF] rt_matmultrr_sgl.c */
