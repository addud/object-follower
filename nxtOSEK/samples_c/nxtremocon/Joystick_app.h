/*
 * File: Joystick_app.h
 *
 * Real-Time Workshop code generated for Simulink model Joystick_app.
 *
 * Model version                        : 1.477
 * Real-Time Workshop file version      : 7.0  (R2007b)  02-Aug-2007
 * Real-Time Workshop file generated on : Sat Mar 22 00:27:07 2008
 * TLC version                          : 7.0 (Jul 26 2007)
 * C source code generated on           : Sat Mar 22 00:27:07 2008
 */

#ifndef RTW_HEADER_Joystick_app_h_
#define RTW_HEADER_Joystick_app_h_
#ifndef Joystick_app_COMMON_INCLUDES_
# define Joystick_app_COMMON_INCLUDES_
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtlibsrc.h"
#endif                                 /* Joystick_app_COMMON_INCLUDES_ */

#include "Joystick_app_types.h"

/* Includes for objects with custom storage classes. */
#include "ecrobot_interface.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((void*) 0)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((void) 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* Block signals (auto storage) */
typedef struct {
  int16_T AccelerationSensorRead[3];   /* '<S4>/Acceleration Sensor Read' */
} BlockIO;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T UnitDelay_DSTATE[3];        /* '<S9>/Unit Delay' */
  uint8_T UnitDelay_DSTATE_i[2];       /* '<S4>/Unit Delay' */
  int8_T straight;                     /* '<S1>/Data Store Memory' */
  int8_T turn;                         /* '<S1>/Data Store Memory1' */
} D_Work;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState TriggeredSubsystem_Trig_ZCE[2];/* '<S4>/Triggered Subsystem' */
} PrevZCSigStates;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: frequency
   * '<S10>/Chart'
   */
  uint16_T SFunction_p1[32];

  /* Computed Parameter: Value
   * '<S4>/Constant1'
   */
  uint8_T Constant1_Value_j[2];

  /* Computed Parameter: Value
   * '<S8>/Constant2'
   */
  uint8_T Constant2_Value[30];
} ConstParam;

/* Block signals (auto storage) */
extern BlockIO rtB;

/* Block states (auto storage) */
extern D_Work rtDWork;

/* Constant parameters (auto storage) */
extern const ConstParam rtConstP;

/* Model entry point functions */
extern void Joystick_app_initialize(void);
extern void Fcn2(void);
extern void Fcn1(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('joystick_ctrl/Joystick_app')    - opens subsystem joystick_ctrl/Joystick_app
 * hilite_system('joystick_ctrl/Joystick_app/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : joystick_ctrl
 * '<S1>'   : joystick_ctrl/Joystick_app
 * '<S4>'   : joystick_ctrl/Joystick_app/Acceleration Sensor Read
 * '<S5>'   : joystick_ctrl/Joystick_app/Play Control
 * '<S6>'   : joystick_ctrl/Joystick_app/Acceleration Sensor Read/GetData
 * '<S7>'   : joystick_ctrl/Joystick_app/Acceleration Sensor Read/Touch Sensor Read
 * '<S8>'   : joystick_ctrl/Joystick_app/Acceleration Sensor Read/Triggered Subsystem
 * '<S9>'   : joystick_ctrl/Joystick_app/Acceleration Sensor Read/GetData/LPF
 * '<S10>'  : joystick_ctrl/Joystick_app/Play Control/Enabled Subsystem
 * '<S11>'  : joystick_ctrl/Joystick_app/Play Control/Touch Sensor Read
 * '<S12>'  : joystick_ctrl/Joystick_app/Play Control/Enabled Subsystem/Chart
 */
#endif                                 /* RTW_HEADER_Joystick_app_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
