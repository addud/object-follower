#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define PRIO_IDLE		10
#define PRIO_DIST		15
#define PRIO_BUTTON	20

#define PORT_SONAR 				NXT_PORT_S3
#define PORT_TOCUH_SENSOR		NXT_PORT_S2
#define PORT_LIGHT_SENSOR 		NXT_PORT_S1
#define PORT_MOTOR_LEFT			NXT_PORT_B
#define PORT_MOTOR_RIGHT		NXT_PORT_A

#define RETURN_SPEED_FACTOR  2

//for our case we're implementing only a PD controller, since the sampling rate of the proximity sensor
//is to low for the integrative component to have any benficial effect on the control
#define Kp 1.1
#define Kd 0.4
#define Ki 0

#define CAR_OFFSET			20
#define DISTANCE_REF 		(20 + CAR_OFFSET) 
#define MAX_DIST_ERROR 		45
#define SPEED_ZERO			55
#define SPEED_BACKWARDS 	-85
#define INFINITE_DISTANCE_BUFFER_LENGTH 	4
#define INFINITE_DISTANCE						255
/*Declaring the timer counter*/
DeclareCounter(SysTimerCnt);
/*Declare the driving command as a resource, so we can lock within a task*/
DeclareResource(dc_t_access);
/*Declaring all tasks*/
DeclareTask(MotorcontrolTask);
DeclareTask(ButtonpressTask);
DeclareTask(DisplayTask);
DeclareTask(DistanceTask); 

/*This structure works as the driving command, it is accesed from the tasks*/
typedef struct  {
    U32 duration;
    S32 speed;
    int priority;
} dc_t;
dc_t dc = {0, 0, PRIO_IDLE};

// global variables used to display information
S16 speedLCD, distanceLCD, buttonLCD, disterrorLCD, correctionLCD, bufferLCD;

/*Light sensor commands*/
void ecrobot_device_initialize() 
{
	//Intializing the light sensor
	ecrobot_set_light_sensor_active(PORT_LIGHT_SENSOR);
	ecrobot_init_sonar_sensor(PORT_SONAR);
}
void ecrobot_device_terminate() 
{
	//Terminating the light sensor
	ecrobot_set_light_sensor_inactive(PORT_LIGHT_SENSOR);
	ecrobot_term_sonar_sensor(PORT_SONAR);
}
/*Initializing counter*/
void user_1ms_isr_type2(void) 
{
	(void)SignalCounter(SysTimerCnt);
}

/*This function recieves new commands for the car and change them in the driving command structure*/
void change_driving_command(int priority, S32 speed, U32 duration)
{
	GetResource(dc_t_access);
	if( priority >= dc.priority )
	{
		dc.priority = priority;
		dc.speed = speed;
		dc.duration = duration;
	}
	ReleaseResource(dc_t_access);
}

/*Speed correction*/
void correct_speed(S32 speed_correction)
{
	S32 speed;
	
	if (speed_correction > 0) 
	{
		speed = speed_correction + SPEED_ZERO;
		if (speed > 100)
		{
			speed = 100;
		}
	} 
	else
	{
		speed = speed_correction - SPEED_ZERO;
		if (speed < -100)
		{
			speed = -100;
		}
	} 
	
	change_driving_command(PRIO_DIST, speed, 0);
}

/*This task control the motors of the car, using the driving command structure*/
TASK(MotorcontrolTask)
{
	U32 speed;
	
	GetResource(dc_t_access);

	/*If the duration positive then we substract 50ms*/
	if( dc.duration > 0 )
	{
		dc.duration -= 50;
	}
	/*When the duration is non-positive goes to IDLE*/
	else
	{
		if (dc.priority == PRIO_BUTTON)
		{		
			dc.priority = PRIO_IDLE;
			dc.speed = 0;			
		}
	}
	
	speed = dc.speed;
	ReleaseResource(dc_t_access);	
			
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, speed, 0);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, speed, 0);
	
	speedLCD = speed; 

	TerminateTask();
}

/*This task command the car to move backwards if the button sensor is pressed*/
TASK(ButtonpressTask)
{

	static U8 last_touch_state = 0;
	U8 tmp_touch_state = 0;
		

		tmp_touch_state = ecrobot_get_touch_sensor(PORT_TOCUH_SENSOR);
		
		if( tmp_touch_state > last_touch_state )
		{
			change_driving_command(PRIO_BUTTON, SPEED_BACKWARDS, 1000);
			buttonLCD = 1;
		}
		else
		{
			buttonLCD = 0;
		}
		
		last_touch_state = tmp_touch_state;
    
	TerminateTask();
}

/*Display several information in the screen*/
TASK(DisplayTask)
{
	char *message = NULL;

		//Display
		display_clear(1);
		display_goto_xy(0,0);
		message = "Button ";
    	display_string(message);
    	if( buttonLCD )
    	{
    		message = "Pushed ";
    	}
    	else
    	{
    		message = "NOT Pressed ";
    	}
    	display_string(message);
    	display_goto_xy(0,2);
		message = "Speed: ";
		display_string(message);
    	display_int(speedLCD,4); // display speed
    	display_goto_xy(0,3);
    	message = "Distance: ";
		display_string(message);
    	display_int(distanceLCD, 4); // display distance
    	display_goto_xy(0,4);
    	message = "dist_err: ";
		display_string(message);
    	display_int(disterrorLCD, 4); // display distance error
    	display_goto_xy(0,5);
    	message = "speed_correction: ";
		display_string(message);
    	display_int(correctionLCD, 4); // display speed correction
    	display_goto_xy(0,6);
    	message = "buffer sum: ";
		display_string(message);
    	display_int(bufferLCD, 4);//display the proximity sensor readings buffer
		display_update();

    
	TerminateTask();
}

/* This task commands the car to go backwards if it is close to an obstacle, using the proximity sensor,
 * when there is enough distance again then he will go forward*/ 
 
/* Due to the proximity sensor's inaccuracy, we're getting sporadic readings of 255 (infinite distance)   
 * even when we have an obstacle within its range.
 * In order to compensate for this, we are using a buffer of the last INFINITE_DISTANCE_BUFFER_LENGTH 
 * readings. If all the readings in this buffer are equal to INFINITE_DISTANCE (255), then we presume
 * that the car has no obstacle in front of it (the infinite distance readings are real), so we proceed
 * with full speed ahead :)
 */
 
TASK(DistanceTask)
{
	static S32 distance_buffer[INFINITE_DISTANCE_BUFFER_LENGTH ];
	static U8 i;
	
	S32 	cur_distance, 
			old_dist_err = 0, 
			dist_err, 
			temp_dist_reading, 
			derivative, 
			integrative=0;
	
	S32 speed_correction;
	S32 Kret;
	U32 distancebuffer_sum;
	U8 j = 0;
	
	temp_dist_reading = ecrobot_get_sonar_sensor(PORT_SONAR);
	
	//we're using a ring buffer of INFINITE_DISTANCE_BUFFER_LENGTH elements to store the last readings
	distance_buffer[i] = temp_dist_reading;
	i++;
	i &= ~(INFINITE_DISTANCE_BUFFER_LENGTH ); 
	distanceLCD = temp_dist_reading;
	distancebuffer_sum = 0;
	for( j =0; j < INFINITE_DISTANCE_BUFFER_LENGTH ; j++)
	{
		distancebuffer_sum += distance_buffer[j];
	}
	bufferLCD = distancebuffer_sum;
	
	//if the reading is -1, the sensor is not ready, so we skip this control cycle
	if(temp_dist_reading >= 0)
	{
		//if the last INFINITE_DISTANCE_BUFFER_LENGTH readings were not all equal to INFINITE_DISTANCE (255)
		//and the current reading is not INFINITE_DISTANCE (255) then we can accept it and control according to it
		//otherwise we don't accept the current reading and skip this cycle of the control loop 
		if ( ((distancebuffer_sum < (INFINITE_DISTANCE * INFINITE_DISTANCE_BUFFER_LENGTH))  && 
			  (temp_dist_reading < INFINITE_DISTANCE))
			   
			   ||
				//if the last INFINITE_DISTANCE_BUFFER_LENGTH readings wereall equal to INFINITE_DISTANCE (255)
				//then we must proceed forward according to the reading	
	 			(distancebuffer_sum == (INFINITE_DISTANCE * INFINITE_DISTANCE_BUFFER_LENGTH))
	 		)
	 	
		{
			cur_distance = temp_dist_reading;
			
			dist_err = cur_distance - DISTANCE_REF;
			
			//limit the distance error to keep the proportion between going forwards and backwards
			if (dist_err > MAX_DIST_ERROR)
			{
				dist_err = MAX_DIST_ERROR;
			}
			
			disterrorLCD = dist_err;
			derivative = dist_err - old_dist_err;
			integrative += dist_err;
			
			//this is a classic PID controller formula, with the backwards moving correction (Kret)
			speed_correction = (S32)(Kp * dist_err + Kd * derivative + Ki * integrative);
			correctionLCD = speed_correction;
			
			old_dist_err = dist_err;
			
			if (speed_correction > 0) {
				speed_correction = 0;
			}

			correct_speed(speed_correction);
		}
	}
	
	TerminateTask();
}
