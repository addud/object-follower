/*
 * File: Joystick_app.c
 *
 * Real-Time Workshop code generated for Simulink model Joystick_app.
 *
 * Model version                        : 1.477
 * Real-Time Workshop file version      : 7.0  (R2007b)  02-Aug-2007
 * Real-Time Workshop file generated on : Sat Mar 22 00:27:07 2008
 * TLC version                          : 7.0 (Jul 26 2007)
 * C source code generated on           : Sat Mar 22 00:27:07 2008
 */

#include "Joystick_app.h"
#include "Joystick_app_private.h"

/* Block signals (auto storage) */
BlockIO rtB;

/* Block states (auto storage) */
D_Work rtDWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates rtPrevZCSigState;

/* Start for exported function: Fcn1 */
void Fcn1_Start(void)
{
  /* Start for S-Function (fcncallgen): '<S2>/Function-Call Generator' */
}

/* Output and update for exported function: Fcn1 */
void Fcn1(void)
{
  /* local block i/o variables */
  real32_T rtb_Sum[3];
  int16_T rtb_DataTypeConversion2[3];
  int16_T rtb_DeadZone1;
  int16_T rtb_UnaryMinus;
  int16_T rtb_Saturation[2];
  int8_T rtb_DataTypeConversion4[2];
  uint8_T rtb_Switch[2];
  uint8_T rtb_TmpHiddenBufferAtBluetoothT[32];
  boolean_T rtb_RelationalOperator[2];

  {
    int32_T i;
    boolean_T tmp;

    /* S-Function (fcncallgen): '<S2>/Function-Call Generator' incorporates:
     *  DataTypeConversion: '<S6>/Data Type Conversion1'
     *  Gain: '<S9>/Gain'
     *  Gain: '<S9>/Gain1'
     *  RelationalOperator: '<S4>/Relational Operator'
     *  Sum: '<S9>/Sum'
     *  UnitDelay: '<S4>/Unit Delay'
     *  UnitDelay: '<S9>/Unit Delay'
     *  Update for UnitDelay: '<S4>/Unit Delay'
     *  Update for UnitDelay: '<S9>/Unit Delay'
     */

    /* S-Function Block: <S4>/Acceleration Sensor Read */
    ecrobot_get_accel_sensor(NXT_PORT_S1, rtB.AccelerationSensorRead);
    for (i = 0; i < 3; i++) {
      /* Sum: '<S9>/Sum' */
      rtb_Sum[i] = 1.000000015E-001F * (real32_T)rtB.AccelerationSensorRead[i] +
        8.999999762E-001F * rtDWork.UnitDelay_DSTATE[i];
    }

    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S4>/Constant1'
     *  DataStoreRead: '<S7>/Data Store Read'
     *  DataTypeConversion: '<S6>/Data Type Conversion2'
     *  DataTypeConversion: '<S6>/Data Type Conversion3'
     *  Saturate: '<S6>/Saturation'
     */
    if (ecrobot_get_touch_sensor(NXT_PORT_S2) != 0U) {
      for (i = 0; i < 3; i++) {
        /* DataTypeConversion: '<S6>/Data Type Conversion2' */
        rtb_DataTypeConversion2[i] = (int16_T)rtb_Sum[i];
      }

      /* DeadZone: '<S6>/Dead Zone' */
      {
        /*
         * the declaration of rtTmp must employ the volatile qualifer
         * to keep the comparisons to the upper and lower limits from
         * being optimized out by very smart optimizers which would not
         * account for overflow but would simply deduce that u - ul < u
         * when ul > 0
         */
        volatile int16_T rtTmp;
        if (rtb_DataTypeConversion2[1] >= 10) {
          rtTmp = rtb_DataTypeConversion2[1] - 10;
          if (10 < 0 && rtTmp < rtb_DataTypeConversion2[1]) {
            rtTmp = MAX_int16_T;
          }

          rtb_UnaryMinus = rtTmp;
        } else if (rtb_DataTypeConversion2[1] > (-10)) {
          rtb_UnaryMinus = 0;
        } else {
          rtTmp = rtb_DataTypeConversion2[1] - (-10);
          if ((-10) > 0 && rtTmp > rtb_DataTypeConversion2[1]) {
            rtTmp = MIN_int16_T;
          }

          rtb_UnaryMinus = rtTmp;
        }
      }

      /* S-Function (sfix_abs): '<S6>/Unary Minus' */

      /* Unary Minus Block: '<S6>/Unary Minus'
       * Input0  Data Type:  Integer        S16
       * Output0 Data Type:  Integer        S16
       */
      rtb_UnaryMinus = -rtb_UnaryMinus;

      /* DeadZone: '<S6>/Dead Zone1' */
      {
        /*
         * the declaration of rtTmp must employ the volatile qualifer
         * to keep the comparisons to the upper and lower limits from
         * being optimized out by very smart optimizers which would not
         * account for overflow but would simply deduce that u - ul < u
         * when ul > 0
         */
        volatile int16_T rtTmp;
        if (rtb_DataTypeConversion2[0] >= 20) {
          rtTmp = rtb_DataTypeConversion2[0] - 20;
          if (20 < 0 && rtTmp < rtb_DataTypeConversion2[0]) {
            rtTmp = MAX_int16_T;
          }

          rtb_DeadZone1 = rtTmp;
        } else if (rtb_DataTypeConversion2[0] > (-20)) {
          rtb_DeadZone1 = 0;
        } else {
          rtTmp = rtb_DataTypeConversion2[0] - (-20);
          if ((-20) > 0 && rtTmp > rtb_DataTypeConversion2[0]) {
            rtTmp = MIN_int16_T;
          }

          rtb_DeadZone1 = rtTmp;
        }
      }

      /* Product: '<S6>/Divide1' incorporates:
       *  Constant: '<S6>/Constant1'
       */
      rtb_Saturation[0] = (int16_T)(rtb_DeadZone1 >> 1);
      rtb_Saturation[1] = (int16_T)(rtb_UnaryMinus >> 1);
      for (i = 0; i < 2; i++) {
        rtb_Switch[i] = (uint8_T)rt_SATURATE(rtb_Saturation[i], -100, 100);
      }
    } else {
      for (i = 0; i < 2; i++) {
        rtb_Switch[i] = rtConstP.Constant1_Value_j[i];
      }
    }

    for (i = 0; i < 2; i++) {
      /* RelationalOperator: '<S4>/Relational Operator' */
      rtb_RelationalOperator[i] = (rtDWork.UnitDelay_DSTATE_i[i] != rtb_Switch[i]);
    }

    /* Outputs for trigger SubSystem: '<S4>/Triggered Subsystem' */
    tmp = false;
    for (i = 0; i < 2; i++) {
      tmp = (tmp || (((rtPrevZCSigState.TriggeredSubsystem_Trig_ZCE[i] ==
                       POS_ZCSIG) != rtb_RelationalOperator[i]) &&
                     (rtPrevZCSigState.TriggeredSubsystem_Trig_ZCE[i] !=
                      UNINITIALIZED_ZCSIG)));
    }

    if (tmp) {
      /* DataStoreWrite: '<S8>/Data Store Write' incorporates:
       *  Constant: '<S8>/Constant2'
       *  DataTypeConversion: '<S8>/Data Type Conversion4'
       *  SignalConversion: '<S8>/TmpHiddenBufferAtBluetooth Tx WriteInport1'
       */
      for (i = 0; i < 2; i++) {
        /* DataTypeConversion: '<S8>/Data Type Conversion4' */
        rtb_DataTypeConversion4[i] = (int8_T)rtb_Switch[i];
        rtb_TmpHiddenBufferAtBluetoothT[i] = rtb_Switch[i];
      }

      rtDWork.straight = rtb_DataTypeConversion4[0];

      /* DataStoreWrite: '<S8>/Data Store Write1' */
      rtDWork.turn = rtb_DataTypeConversion4[1];
      for (i = 0; i < 30; i++) {
        /* SignalConversion: '<S8>/TmpHiddenBufferAtBluetooth Tx WriteInport1' */
        rtb_TmpHiddenBufferAtBluetoothT[i + 2] = rtConstP.Constant2_Value[i];
      }

      /* S-Function Block: <S8>/Bluetooth Tx Write */
      ecrobot_send_bt_packet(rtb_TmpHiddenBufferAtBluetoothT, 32);
    }

    for (i = 0; i < 2; i++) {
      rtPrevZCSigState.TriggeredSubsystem_Trig_ZCE[i] = (int32_T)
        rtb_RelationalOperator[i] ? POS_ZCSIG : ZERO_ZCSIG;
    }

    /* end of Outputs for SubSystem: '<S4>/Triggered Subsystem' */
    for (i = 0; i < 3; i++) {
      /* Update for UnitDelay: '<S9>/Unit Delay' */
      rtDWork.UnitDelay_DSTATE[i] = rtb_Sum[i];
    }

    for (i = 0; i < 2; i++) {
      /* Update for UnitDelay: '<S4>/Unit Delay' */
      rtDWork.UnitDelay_DSTATE_i[i] = rtb_Switch[i];
    }
  }
}

/* Start for exported function: Fcn2 */
void Fcn2_Start(void)
{
  /* Start for S-Function (fcncallgen): '<S3>/Function-Call Generator' */
}

/* Output and update for exported function: Fcn2 */
void Fcn2(void)
{
  /* local block i/o variables */
  uint32_T rtb_freq;
  int8_T rtb_DataStoreRead1;
  int8_T rtb_DataStoreRead;

  /* S-Function (fcncallgen): '<S3>/Function-Call Generator' */

  /* Outputs for enable SubSystem: '<S5>/Enabled Subsystem' incorporates:
   *  DataStoreRead: '<S11>/Data Store Read'
   */
  if (ecrobot_get_touch_sensor(NXT_PORT_S2) > 0U) {
    /* DataStoreRead: '<S10>/Data Store Read1' */
    rtb_DataStoreRead1 = rtDWork.straight;

    /* DataStoreRead: '<S10>/Data Store Read' */
    rtb_DataStoreRead = rtDWork.turn;

    /* Stateflow: '<S10>/Chart' incorporates:
     *  S-Function (sfix_abs): '<S10>/Unary Minus'
     */
    {
      int32_T sf_data;
      uint8_T sf_zone;
      uint8_T sf_scale_index;
      sf_data = (int32_T)rtb_DataStoreRead;
      if (sf_data > 80) {
        sf_zone = 7U;
      } else if (sf_data > 60) {
        sf_zone = 6U;
      } else if (sf_data > 30) {
        sf_zone = 5U;
      } else if (sf_data >= -10) {
        sf_zone = 4U;
      } else if (sf_data > -30) {
        sf_zone = 3U;
      } else if (sf_data > -60) {
        sf_zone = 2U;
      } else if (sf_data > -80) {
        sf_zone = 1U;
      } else {
        sf_zone = 0U;
      }

      sf_scale_index = sf_zone;
      sf_data = (int32_T)((int8_T)(-rtb_DataStoreRead1));
      if (sf_data > 80) {
        sf_zone = 3U;
      } else if (sf_data >= -20) {
        sf_zone = 2U;
      } else if (sf_data > -80) {
        sf_zone = 1U;
      } else {
        sf_zone = 0U;
      }

      rtb_freq = (uint32_T)(rtConstP.SFunction_p1[sf_zone + (sf_scale_index << 2)]);
    }

    /* S-Function Block: <S10>/Sound Tone Write */
//    sound_freq(rtb_freq, 65U);
  }

  /* end of Outputs for SubSystem: '<S5>/Enabled Subsystem' */
}

/* Model initialize function */
void Joystick_app_initialize(void)
{
  /* Registration code */

  /* block I/O */
  (void) memset(((void *) &rtB),0,
                sizeof(BlockIO));

  /* states (dwork) */
  (void) memset((char_T *) &rtDWork,0,
                sizeof(D_Work));

  /* Start for S-Function (fcncallgen): '<Root>/__FcnCallGen__0' */
  Fcn1_Start();
  Fcn2_Start();

  {
    int idx;
    for (idx = 0; idx < 2; idx ++) {
      rtPrevZCSigState.TriggeredSubsystem_Trig_ZCE[idx] = UNINITIALIZED_ZCSIG;
    }
  }
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
