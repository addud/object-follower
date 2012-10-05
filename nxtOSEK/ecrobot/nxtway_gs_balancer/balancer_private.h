/**
 ******************************************************************************
 **	�t�@�C���� : balancer_private.h
 **
 ** ���f���֘A���:
 **   ���f����   : balancer.mdl
 **   �o�[�W���� : 1.893
 **   ����       : y_yama - Tue Sep 25 11:37:09 2007
 **                takashic - Sun Sep 28 17:50:53 2008
 **
 ** Copyright (c) 2009-2011 MathWorks, Inc.
 ** All rights reserved.
 ******************************************************************************
 **/

#ifndef RTW_HEADER_balancer_private_h_
#define RTW_HEADER_balancer_private_h_
#include "rtwtypes.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L32N32F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I32L32N32F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

/* Imported (extern) block parameters */
extern F32 A_D;                   /* Variable: A_D
                                        * Referenced by blocks:
                                        * '<S11>/Constant1'
                                        * '<S11>/Gain2'
                                        * ���[�p�X�t�B���^�W��(���E�ԗւ̕��ω�]�p�x�p)
                                        */
extern F32 A_R;                   /* Variable: A_R
                                        * Referenced by blocks:
                                        * '<S8>/Constant1'
                                        * '<S8>/Gain2'
                                        * ���[�p�X�t�B���^�W��(���E�ԗւ̖ڕW���ω�]�p�x�p)
                                        */
extern F32 K_F[4];                /* Variable: K_F
                                        * '<S1>/FeedbackGain'
                                        * �T�[�{����p��ԃt�B�[�h�o�b�N�W��
                                        */
extern F32 K_I;                   /* Variable: K_I
                                        * '<S1>/IntegralGain'
                                        * �T�[�{����p�ϕ��W��
                                        */
extern F32 K_PHIDOT;              /* Variable: K_PHIDOT
                                        * '<S3>/Gain2'
                                        * �ԑ̖̂ڕW���ʉ�]���x(d��/dt)�W��
                                        */
extern F32 K_THETADOT;            /* Variable: K_THETADOT
                                        * '<S3>/Gain1'
                                        * ���E�ԗւ̕��ω�]���x(d��/dt)�W��
                                        */
extern const F32 BATTERY_GAIN;    /* PWM�o�͎Z�o�p�o�b�e���d���␳�W�� */
extern const F32 BATTERY_OFFSET;  /* PWM�o�͎Z�o�p�o�b�e���d���␳�I�t�Z�b�g */

#endif                                 /* RTW_HEADER_balancer_private_h_ */

/*======================== TOOL VERSION INFORMATION ==========================*
 * MATLAB 7.7 (R2008b)30-Jun-2008                                             *
 * Simulink 7.2 (R2008b)30-Jun-2008                                           *
 * Real-Time Workshop 7.2 (R2008b)30-Jun-2008                                 *
 * Real-Time Workshop Embedded Coder 5.2 (R2008b)30-Jun-2008                  *
 * Stateflow 7.2 (R2008b)30-Jun-2008                                          *
 * Stateflow Coder 7.2 (R2008b)30-Jun-2008                                    *
 * Simulink Fixed Point 6.0 (R2008b)30-Jun-2008                               *
 *============================================================================*/

/*======================= LICENSE IN USE INFORMATION =========================*
 * matlab                                                                     *
 * real-time_workshop                                                         *
 * rtw_embedded_coder                                                         *
 * simulink                                                                   *
 *============================================================================*/
/******************************** END OF FILE ********************************/
