/* genericI2Ctest.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* Prototypes */
void init_genericI2C_sensor(U8 port_id);
void get_mindsensor_accel_sensor(U8 port_id, S16 *buf);
void term_genericI2C_sensor(U8 port_id);

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);
DeclareTask(Task2);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize(){}
void ecrobot_device_terminate()
{
	term_genericI2C_sensor(NXT_PORT_S4);
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

/* Task1 executed only once at initialization */
TASK(Task1)
{
	init_genericI2C_sensor(NXT_PORT_S4);

	TerminateTask();
}

/* Task2 executed every 50msec */
TASK(Task2)
{
	S16 accl_data[6];
	
	get_mindsensor_accel_sensor(NXT_PORT_S4, accl_data);

	display_clear(0);

	display_goto_xy(0, 0);
   	display_string("I2C Test");

   	display_goto_xy(0, 1);
   	display_string("X TILT:");
   	display_int(accl_data[0], 0);

   	display_goto_xy(0, 2);
   	display_string("Y TILT:");
   	display_int(accl_data[1], 0);

   	display_goto_xy(0, 3);
   	display_string("Z TILT:");
   	display_int(accl_data[2], 0);

   	display_goto_xy(0, 4);
   	display_string("X ACCL:");
   	display_int(accl_data[3], 0);

   	display_goto_xy(0, 5);
   	display_string("Y ACCL:");
   	display_int(accl_data[4], 0);

   	display_goto_xy(0, 6);
   	display_string("Z ACCL:");
   	display_int(accl_data[5], 0);

   	display_update();

	TerminateTask();
}

/*
 * Initialize the specified port to be used for I2C communication
 * NOTE: user defined I2C sensor initialize function should be implemented
 *       in user defined an OSEK initialization Task (not in LEJOS OSEK device init hook).
 *       because device init hook is invoked in a loop while the button instruction screen is appeared.
 */
void init_genericI2C_sensor(U8 port_id)
{
	nxt_avr_set_input_power(port_id,2);
	i2c_enable(port_id);
}

/*
 * This is an implementation example of I2C sensor data acquisition for
 * mindsensor acceleration sensor. mindsensor acceleration sensor returns
 * tilt data and acceleration data in three axes.
 * 
 * This API implementation for I2C communication might be different from
 * I2C sensor communication examples in other NXT programming languages.
 * Others use a wait until data transaction is finished after sending a request.
 * However, it might not be acceptable for real-time control application. So we
 * introduce one sampling delay to avoid waiting for the completion of the data acqusition.
 */  
void get_mindsensor_accel_sensor(U8 port_id, S16 *buf)
{
	 int i,j;
	 static S16 tilt_state[3];
	 static S16 accel_state[3];
	 static U8 data[9] = {0,0,0,0,0,0,0,0,0};
	/*
	 * Data spec. of mindsensor acceleration sensor
	 * 
	 * 0x42 data[0]: X axis Tilt data
	 * 0x43 data[1]: Y axis Tilt data
	 * 0x44 data[2]: Z axis Tilt data
	 * 0x45 data[3]: X axis Accel LSB
	 * 0x46 data[4]: X axis Accel MSB
	 * 0x47 data[5]: Y axis Accel LSB
	 * 0x48 data[6]: Y axis Accel MSB
	 * 0x49 data[7]: Z axis Accel LSB
	 * 0x4A data[8]: Z axis Accel MSB
	 */

	if (i2c_busy(port_id) == 0) /* check the status of I2C comm. */
	{
		j=0;
		for (i=0; i<8; i++)
		{
			if (i<3)
			{
				tilt_state[i] = (S16)data[i];
			}
			else
			{
				accel_state[j++] = ((S16)data[i+1]<<8) + (S16)data[i];
				i++;
			}
   		}
	   /* i2c_start_transaction just triggers an I2C transaction,
		* actual data transaction between ARM7 and an Acceleration
		* Sensor is done by an ISR after this, so there is one execution cycle
		* delay for consistent data acquistion
		*/
		i2c_start_transaction(port_id,1,0x42,1,data,9,0);
	}
	
	for (i=0; i<3; i++)
	{
		buf[i] = tilt_state[i];
		buf[i+3] = accel_state[i];
   	}
}

/*
 * Terminate I2C communication on the specified port
 */
void term_genericI2C_sensor(U8 port_id)
{
	i2c_disable(port_id);
}
