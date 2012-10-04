#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define PORT_SONAR 				NXT_PORT_S3
#define PORT_TOUCH_SENSOR		NXT_PORT_S2
#define PORT_LIGHT_SENSOR 		NXT_PORT_S1
#define PORT_MOTOR_LEFT			NXT_PORT_B
#define PORT_MOTOR_RIGHT		NXT_PORT_A
#define PORT_MOTOR_STEERING		NXT_PORT_C

DeclareCounter(SysTimerCnt);

DeclareTask(TestTask);
DeclareTask(IdleTask);

/*Light sensor commands*/
void ecrobot_device_initialize()
{
	//Intializing the light sensor
	ecrobot_set_light_sensor_active(PORT_LIGHT_SENSOR);
	ecrobot_init_sonar_sensor(PORT_SONAR);
	nxt_motor_set_count(PORT_MOTOR_STEERING, 0);
}
void ecrobot_device_terminate()
{
	//Terminating the light sensor
	ecrobot_set_light_sensor_inactive(PORT_LIGHT_SENSOR);
	ecrobot_term_sonar_sensor(PORT_SONAR);
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_STEERING, 0, 1);
}
/*Initializing counter*/
void user_1ms_isr_type2(void)
{

	(void)SignalCounter(SysTimerCnt);
}

/*This task control the motors of the car*/
TASK(TestTask)
{
#define revolution 90
#define TURN_RIGHT  1
#define TURN_LEFT	0
#define STEERING_SPEED	80

	S16 tmp_rev = 0;
	static S8 sign = 1;
	static U8 turn = TURN_RIGHT;

	//static S16 revolution = 90;

	sign = sign * (-1);

	nxt_motor_set_speed(PORT_MOTOR_STEERING, (sign * STEERING_SPEED), 0);

#if 0
	if (((tmp_rev <= revolution) && (turn == TURN_RIGHT)) ||
				((tmp_rev >= revolution) && ( turn == TURN_LEFT)))
		{
			nxt_motor_set_speed(PORT_MOTOR_STEERING, 0, 1);

		}
		else
		{
			if( turn == TURN_LEFT)
			{
				sign = 1;
				turn = TURN_RIGHT;
			}
			else
			{
				sign = -1;
				turn = TURN_LEFT;
			}
			nxt_motor_set_speed(PORT_MOTOR_STEERING, (sign * STEERING_SPEED), 0);
		}
#endif
	TerminateTask();

}


/*This task control the motors of the car*/
TASK(IdleTask)
{

	TerminateTask();

}

