#include <stdlib.h>
#include "kernel.h"
#include "ecrobot_interface.h"

#define PORT_MOTOR_LEFT			NXT_PORT_B
#define PORT_MOTOR_RIGHT		NXT_PORT_A
#define PORT_DISTSENSOR			NXT_PORT_S2

#define DESIRED_DISTANCE 40
#define TURN_ITERATIONS 10

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
	//Keep track of the turning state
	int turning=TURN_ITERATIONS;
	
	while(1)
	{
		distance = ecrobot_get_sonar_sensor(PORT_DISTSENSOR);
		
		if ((turning>0 && turning<=TURN_ITERATIONS) || distance<=DESIRED_DISTANCE)
		{	
			if ((rand() % 101)>=50)
			{
				//Turn right
				nxt_motor_set_speed(PORT_MOTOR_LEFT,50,0);
				nxt_motor_set_speed(PORT_MOTOR_RIGHT,0,1);
			}
			else
			{
				//Turn left
				nxt_motor_set_speed(PORT_MOTOR_LEFT,0,1);
				nxt_motor_set_speed(PORT_MOTOR_RIGHT,50,0);
			}
			turning++;
		}
		else if (turning>=TURN_ITERATIONS)
		{
			//Setting a constant speed to the motors
			nxt_motor_set_speed(PORT_MOTOR_LEFT,50,0);
			nxt_motor_set_speed(PORT_MOTOR_RIGHT,50,0);
			turning=0;
		}
		systick_wait_ms(periodTime);
	}
	
	TerminateTask();
}
