/* eds.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(EventDispatcher); 
DeclareTask(EventHandler);
DeclareTask(TaskLCD);

DeclareEvent(TouchSensorOnEvent); /* Event declaration */
DeclareEvent(TouchSensorOffEvent); /* Event declaration */ 

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
  nxt_motor_set_speed(NXT_PORT_A, 0, 1); 
}

void ecrobot_device_terminate()
{
  nxt_motor_set_speed(NXT_PORT_A, 0, 1); 
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
  StatusType ercd;

  ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
  if(ercd != E_OK)
  {
    ShutdownOS(ercd);
  }
}

/* EventDispatcher executed every 1ms */
TASK(EventDispatcher)
{
  static U8 TouchSensorStatus_old = 0;
  U8 TouchSensorStatus; 

  TouchSensorStatus = ecrobot_get_touch_sensor(NXT_PORT_S1);

  if (TouchSensorStatus == 1 && TouchSensorStatus_old == 0)
  {
    /* Send a Touch Sensor ON Event to the Handler */ 
    SetEvent(EventHandler, TouchSensorOnEvent);
  }
  else if (TouchSensorStatus == 0 && TouchSensorStatus_old == 1)
  {
    /* Send a Touch Sensor OFF Event to the Handler */ 
    SetEvent(EventHandler, TouchSensorOffEvent);
  }

  TouchSensorStatus_old = TouchSensorStatus;

  TerminateTask();
}

/* EventHandler executed by OSEK Events */
TASK(EventHandler)
{
  while(1)
  {
    WaitEvent(TouchSensorOnEvent); /* Task is in waiting status until the Event comes */ 
    ClearEvent(TouchSensorOnEvent);
    nxt_motor_set_speed(NXT_PORT_A, 50, 1);

    WaitEvent(TouchSensorOffEvent); /* Task is in waiting status until the Event comes */
    ClearEvent(TouchSensorOffEvent);
    nxt_motor_set_speed(NXT_PORT_A, 0, 1);
  }

  TerminateTask();
}

/* TaskLCD executed every 500ms */
TASK(TaskLCD)
{
  ecrobot_status_monitor("EDS");

  TerminateTask();
}

