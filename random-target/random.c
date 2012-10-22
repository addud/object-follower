#include <stdlib.h>
#include "kernel.h"
#include "ecrobot_interface.h"

#define PORT_MOTOR_LEFT			NXT_PORT_B
#define PORT_MOTOR_RIGHT		NXT_PORT_A
#define PORT_DISTSENSOR			NXT_PORT_S1

#define DESIRED_DISTANCE 40
#define TURN_ITERATIONS 10

#define LEFT 0
#define RIGHT 1

/*Declaring the timer counter*/
DeclareCounter( SysTimerCnt);

/*Declaring all tasks*/
DeclareTask(MotorControlTask);

/*Light sensor commands*/
void ecrobot_device_initialize() {
	ecrobot_init_sonar_sensor(PORT_DISTSENSOR);
}
void ecrobot_device_terminate() {
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, 0, 1);
	ecrobot_term_sonar_sensor(PORT_DISTSENSOR);
}
/*Initializing counter*/
void user_1ms_isr_type2(void) {
	(void) SignalCounter(SysTimerCnt);
}

TASK(MotorControlTask)
{
	//Period time of the task in ms
	int periodTime = 50;
	//Distance to the nearest obstacle
	int distance;
	//Flag for object detaction
	int objectFlag = 0;
	//Keep track of the turning state
	int turningFlag=0;
	//Keep track of the turning direction
	int direction = LEFT;
	
	while(1)
	{
		//Get the distance from the sound sensor
		distance = ecrobot_get_sonar_sensor(PORT_DISTSENSOR);
		
		if (distance<=DESIRED_DISTANCE && turningFlag == 0)
		{
			objectFlag = 1;
			if ((rand() % 101)>=50)
			{
				direction = LEFT;
			}
			else
			{
				direction = LEFT;
			}
		}
		else if (distance>DESIRED_DISTANCE)
		{
			objectFlag = 0;
		}
		
		
		if (objectFlag==1 && turningFlag==0)
		{	
			if (direction == RIGHT)
			{
				//Turn right
				nxt_motor_set_speed(PORT_MOTOR_LEFT,70,0);
				nxt_motor_set_speed(PORT_MOTOR_RIGHT,0,1);
			}
			else
			{
				//Turn left
				nxt_motor_set_speed(PORT_MOTOR_LEFT,0,1);
				nxt_motor_set_speed(PORT_MOTOR_RIGHT,70,0);
			}
			turningFlag++;
		}
		else if (objectFlag==0 && turningFlag==1)
		{
			//Setting a constant speed to the motors
			nxt_motor_set_speed(PORT_MOTOR_LEFT,70,0);
			nxt_motor_set_speed(PORT_MOTOR_RIGHT,70,0); 
			turningFlag = 0;
		}
		systick_wait_ms(periodTime);
	}
	
	TerminateTask();
}
