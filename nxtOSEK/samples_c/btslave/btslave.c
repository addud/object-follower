/* btslave.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(EventDispatcher); 
DeclareTask(EventHandler);
DeclareTask(IdleTask);
DeclareEvent(TouchSensorOnEvent);
DeclareEvent(TouchSensorOffEvent); 

/* below macro enables run-time Bluetooth connection */
#define RUNTIME_CONNECTION

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
#ifndef RUNTIME_CONNECTION
  ecrobot_init_bt_slave("LEJOS-OSEK");
#endif
}

void ecrobot_device_terminate()
{
	ecrobot_term_bt_connection();
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

/* EventDispatcher executed every 5ms */
TASK(EventDispatcher)
{
  static U8 bt_receive_buf[32]; 
  static U8 TouchSensorStatus_old = 0;
  U8 TouchSensorStatus; 

  /* read packet data from the master device */  
  ecrobot_read_bt_packet(bt_receive_buf, 32);
  if (bt_receive_buf[0] == 1)
  {
  	ecrobot_set_motor_speed(NXT_PORT_B, 100);
  }
  else
  {
  	ecrobot_set_motor_speed(NXT_PORT_B, 0);
  }  	

  TouchSensorStatus = ecrobot_get_touch_sensor(NXT_PORT_S4);
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
  static U8 bt_send_buf[32]; 

  while(1)
  {
    WaitEvent(TouchSensorOnEvent); /* Task is in waiting status until the Event comes */ 
    ClearEvent(TouchSensorOnEvent);
  	/* send packet data to the master device */
  	bt_send_buf[0] = 1;
	ecrobot_send_bt_packet(bt_send_buf, 32);

    WaitEvent(TouchSensorOffEvent); /* Task is in waiting status until the Event comes */
    ClearEvent(TouchSensorOffEvent);
  	/* send packet data to the master device */
  	bt_send_buf[0] = 0;
	ecrobot_send_bt_packet(bt_send_buf, 32);
  }

  TerminateTask();
}

/* IdleTask */
TASK(IdleTask)
{
  static SINT bt_status = BT_NO_INIT;
  
  while(1)
  {  
#ifdef RUNTIME_CONNECTION
    ecrobot_init_bt_slave("LEJOS-OSEK");
#endif

    if (ecrobot_get_bt_status() == BT_STREAM && bt_status != BT_STREAM)
    {
      display_clear(0);
      display_goto_xy(0, 0);
      display_string("[BT]");
      display_update();
    }
    bt_status = ecrobot_get_bt_status();
  }	
}
