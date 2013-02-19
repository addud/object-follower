#include <stdlib.h>
#include "kernel.h"
#include "ecrobot_interface.h"

#define PORT_MOTOR_LEFT			NXT_PORT_B
#define PORT_MOTOR_RIGHT		NXT_PORT_A
#define PORT_DISTSENSOR			NXT_PORT_S1

//Distance to an object before initiating turn
#define DESIRED_DISTANCE 40

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

	//Flag for object detection, 1 => object detected
	int objectFlag = 0;
	//Random movement speeds
	int randomSpeedLeft = 0;
	int randomSpeedRight = 0;

	//Random movement time counter
	int randomCounter = 0;

	//Keep track of the turning direction
	int direction = LEFT;
	
	while(1)
	{
		//Get the distance from the sound sensor
		distance = ecrobot_get_sonar_sensor(PORT_DISTSENSOR);
		
		//Obstacle detection
		if (distance<=DESIRED_DISTANCE)
		{
			//If a turn is not initiated, turn left or right
			if (objectFlag == 0 && (rand() % 101)>=50)
			{
				direction = LEFT;
			}
			else if (objectFlag == 0)
			{
				direction = RIGHT;
			}
			objectFlag = 1;
		}

		//If no object is present, reset the flag
		else if (distance>DESIRED_DISTANCE)
		{
			objectFlag = 0;
		}
		
		//An object is present, send command to motors for turning
		if (objectFlag==1)
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
		}

		//If no object is present:
		else
		{
			//Setting a random speed to the motors every 2 seconds (randomCounter*periodTime)
			if (randomCounter == 40){
				srand(randomSpeedRight);
				randomSpeedLeft = (rand() % 20) - 5;
				srand(randomSpeedLeft);
				randomSpeedRight = (rand() % 20) - 5;
				randomCounter = 0;
			}
			else{
				randomCounter++;
			}

			//If the left wheel are going backwards, lets reverse instead!
			if (randomSpeedLeft < 0 && randomSpeedLeft > -6){
				randomSpeedLeft = -140 + randomSpeedLeft;
				randomSpeedRight = -140 + randomSpeedRight;
			}

			nxt_motor_set_speed(PORT_MOTOR_LEFT,70 + randomSpeedLeft,0);
			nxt_motor_set_speed(PORT_MOTOR_RIGHT,70 + randomSpeedRight,0);

		}
		systick_wait_ms(periodTime);
	}
	
	TerminateTask();
}
