/*****************************************************************************
 * FILE: ecrobot_main.c
 *
 * MODEL: joystick_ctrl.mdl
 *
 * APP SUBSYSTEM: Joystick_app
 *
 * PLATFORM: LEJOS+OSEK
 *
 * DATE: 22-Mar-2008 00:27:20
 *
 * TOOL VERSION:
 *   Simulink: 7.0 (R2007b) 02-Aug-2007
 *   Real-Time Workshop: 7.0 (R2007b) 02-Aug-2007
 *   Real-Time Workshop Embedded Coder: 5.0 (R2007b) 02-Aug-2007
 *****************************************************************************/
/*============================================================================
 * RTW-EC generated functions for Function-Call Subsystems:
 *   Fcn1: executed at every 0.01[sec]
 *   Fcn2: executed at every 0.05[sec]
 *
 * RTW-EC generated model initialize function:
 *   Joystick_app_initialize
 *===========================================================================*/
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "Joystick_app.h"

/*============================================================================
 * OSEK declarations
 *===========================================================================*/
DeclareCounter(SysTimerCnt);
DeclareTask(OSEK_Task_ECRobotInitialize);
DeclareTask(OSEK_Task_Fcn1);
DeclareTask(OSEK_Task_Fcn2);
DeclareTask(OSEK_Task_ECRobotLCDMonitor);

/*============================================================================
 * Function: ecrobot_device_initialize
 */
void ecrobot_device_initialize(void)
{
  const U8 bd_addr[7] = {0x00, 0x16, 0x53, 0x04, 0x7E, 0x2D, 0x00};
  /* Initialize ECRobot used devices */
  ecrobot_init_accel_sensor(NXT_PORT_S1);
  ecrobot_init_bt_master(bd_addr, "1234");
}

/*============================================================================
 * Function: ecrobot_device_terminate
 */
void ecrobot_device_terminate(void)
{
  /* Terminate ECRobot used devices */
  ecrobot_term_accel_sensor(NXT_PORT_S1);
  ecrobot_term_bt_connection();
}

/*============================================================================
 * Function: Invoked from a category 2 ISR
 */
void user_1ms_isr_type2(void)
{
  StatusType ercd;

  /* Increment System Timer Count */
  ercd = SignalCounter(SysTimerCnt);
  if (ercd != E_OK)
  {
    ShutdownOS(ercd);
  }
}

/*============================================================================
 * OSEK Hooks: empty functions
 */
void StartupHook(void){}

void ShutdownHook(StatusType ercd){}

void PreTaskHook(void){}

void PostTaskHook(void){}

void ErrorHook(StatusType ercd){}

/*============================================================================
 * Task: OSEK_Task_Initialize
 */
TASK(OSEK_Task_ECRobotInitialize)
{
  /* Call Initialize Function(s) */
  Joystick_app_initialize();
  TerminateTask();
}

/*============================================================================
 * Task: OSEK_Task_Fcn1
 */
TASK(OSEK_Task_Fcn1)
{
  /* Call Fcn1 every 10[msec] */
  Fcn1();

  TerminateTask();
}

/*============================================================================
 * Task: OSEK_Task_Fcn2
 */
TASK(OSEK_Task_Fcn2)
{
  /* Call Fcn2 every 50[msec] */
  Fcn2();

  TerminateTask();
}

/*============================================================================
 * Task: OSEK_Task_ECRobotLCDMonitor
 */
TASK(OSEK_Task_ECRobotLCDMonitor)
{
  /* Call this function every 500[msec] */
  ecrobot_status_monitor("Joystick_app");

  TerminateTask();
}

/******************************** END OF FILE ********************************/
