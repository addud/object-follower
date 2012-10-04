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

#define TRANSMITION_FACTOR  2.5

//for our case we're implementing only a PD controller, since the sampling rate of the proximity sensor
//is to low for the integrative component to have any benficial effect on the control
#define Kp 1
#define Kd 0
#define Ki 0

#define LKp	0.12//0.2
#define LKd	0.08 //1.5//1
#define LKi	0.15

#define CAR_OFFSET			20
#define DISTANCE_REF 		(20 + CAR_OFFSET)
#define MAX_DISTANCE_ERROR	40

#define LIGHT_REF			((g_white_ref + g_black_ref) / 2)//570 //520
#define LIGHT_MAX			g_white_ref //470
#define LIGHT_MIN			g_black_ref//660 //570

#define STEERING_LIMIT		100

#define SPEED_ZERO			0
#define STEERING_SPEED		75
#define MAXSPEED			45
#define SPEED_BACKWARDS 	-85
#define INFINITE_DISTANCE_BUFFER_LENGTH 	4
#define INFINITE_DISTANCE						255

#define TURN_RIGHT		1
#define TURN_LEFT		0

/*Declaring the timer counter*/
DeclareCounter(SysTimerCnt);

// declare all events
DeclareEvent(TouchOnEvent);
DeclareEvent(TouchOffEvent);
DeclareEvent(AlgoLightEvent);
DeclareEvent(AlgoDistEvent);
DeclareEvent(SysSpeedEvent);
DeclareEvent(SysStearEvent);


/*Declaring all tasks*/
DeclareTask(SysTask);
DeclareTask(ButtonTask);
DeclareTask(IdleTask);
DeclareTask(DataTask);
DeclareTask(AlgoTask);

static U16 lightValue;
static U16 distanceValue;
static S8 speed;
static U8 turn, angle;
static S16 revolution;
static U16 g_white_ref=470, g_black_ref=660, g_blur_ref;

static U8 startCalibration = 0;

// global variables used to display information
S16 speedLCD, distanceLCD, buttonLCD, disterrorLCD, correctionLCD, bufferLCD, angleLCD, turnLCD, lightLCD, lighterrorLCD;
char *calibrationLCD;

void display_values(void)
{
	char *message = NULL;
	U8 line = 0;

		//Display
		display_clear(1);
		display_goto_xy(0,line++);
		message = "Calib ";
    	display_string(message);
    	display_string(calibrationLCD);
    	display_goto_xy(0,line++);
		message = "Instant Rev: ";
		display_string(message);
    	display_int(nxt_motor_get_count(PORT_MOTOR_STEERING),4); // display speed
    	display_goto_xy(0,line++);
    	message = "light: ";
		display_string(message);
    	display_int(lightLCD, 4); // display distance error
    	display_goto_xy(0,line++);
    	message = "LighErr: ";
		display_string(message);
    	display_int(lighterrorLCD, 4); // display speed correction
    	display_goto_xy(0,line++);
    	message = "Revolution: ";
		display_string(message);
    	display_int(angleLCD, 4);
    	display_goto_xy(0,line++);

    	message = "WHITE: ";
		display_string(message);
    	display_int(LIGHT_MAX, 4); // display distance
    	display_goto_xy(0,line++);

    	message = "BLACK: ";
		display_string(message);
    	display_int(LIGHT_MIN, 4); // display distance
    	display_goto_xy(0,line++);

    	display_update();

}

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
	if( startCalibration == FALSE)
	{
		(void)SignalCounter(SysTimerCnt);
	}
}

S8 DistPID(U16 distValue)
{
	static S16 oldDistP, distI;
	S16 distP, distD;
	S8 speed = 0;

	distP = distValue - DISTANCE_REF;
	if( distP > MAX_DISTANCE_ERROR)
		distP = MAX_DISTANCE_ERROR; // sensor not very accurate
	disterrorLCD = distP;
	distD = (distP - oldDistP) / 2;
	distI = distI + (distP * 2);
	speed = Kp * distP + Kd * distD + Ki * distI;
	correctionLCD = speed;

	oldDistP = distP;

	return speed;
}

void LightPID(U16 lightValue)
{
	static S16 oldLightP, lightI;
	S16 lightP, lightD;
	U8 LKD = 0;

	lightP = lightValue - LIGHT_REF;
	if(lightP <= 0)
	{
		turn = TURN_RIGHT;
	}
	else
	{
		turn = TURN_LEFT;
	}
	turnLCD = turn;

	lightD = lightP - oldLightP;
	lighterrorLCD = lightP;
	if(lightI > 0)
	{
		LKD = LKd; // apply derivative only when track is recovered to steer more
	}
	else
	{
		LKD = 0;
	}
	// accumulate only when reference is far away
	if((lightValue == LIGHT_MIN) || (lightValue == LIGHT_MAX))
	{
		lightI = lightI + lightP;
	}
	else
	{
		lightI = 0;
	}
	// PID formula
	revolution = LKp * lightP + LKd * lightD + LKi * lightI;

	if(revolution > STEERING_LIMIT)
		revolution = STEERING_LIMIT;
	if(revolution < -STEERING_LIMIT)
		revolution = -STEERING_LIMIT;

	angleLCD = revolution;

	oldLightP = lightP;

}

void WhealsControl(S8 spd, U8 turn, S16 angle)
{
	if( spd >= 0)
		spd += SPEED_ZERO;
	else
		spd -= SPEED_ZERO;

	speedLCD = spd;
	spd = -75;
#if 0
	if(turn == TURN_RIGHT)
	{
		nxt_motor_set_speed(PORT_MOTOR_RIGHT, (spd - angle), 0);
		nxt_motor_set_speed(PORT_MOTOR_LEFT, spd, 0);
	}
	else  // TURN_LEFT
	{
		nxt_motor_set_speed(PORT_MOTOR_RIGHT, spd, 0);
		nxt_motor_set_speed(PORT_MOTOR_LEFT, (spd - angle), 0);
	}
#else
		nxt_motor_set_speed(PORT_MOTOR_RIGHT, spd, 0);
		nxt_motor_set_speed(PORT_MOTOR_LEFT, spd, 0);
#endif

}

/*This task control the motors of the car*/
TASK(SysTask)
{

	WaitEvent(SysStearEvent | SysSpeedEvent);

	WhealsControl(speed, turn, angle);

	TerminateTask();

}

TASK(AlgoTask)
{
	EventMaskType eventmask = 0;

	WaitEvent(AlgoLightEvent | AlgoDistEvent);
	GetEvent(AlgoTask, &eventmask);

	//cheack each event mask and clear it
	if (eventmask & AlgoLightEvent)
	{
		ClearEvent(AlgoLightEvent);
		LightPID(lightValue);
		SetEvent(SysTask,SysStearEvent);

	}

	//cheack each event mask and clear it
	if (eventmask & AlgoDistEvent)
	{
		ClearEvent(AlgoDistEvent);
		//if(distanceValue < 255)
		//	speed = DistPID(distanceValue);
		//else
		//	speed = MAXSPEED;
		SetEvent(SysTask,SysSpeedEvent);
	}

	TerminateTask();
}

TASK(DataTask)
{
	static U8 cnt100ms;
	S16 tmp_rev = 0;
	S8 sign = 0;

	// get steering value
	tmp_rev = nxt_motor_get_count(PORT_MOTOR_STEERING);

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
		}
		else
		{
			sign = -1;
		}
		nxt_motor_set_speed(PORT_MOTOR_STEERING, (sign * STEERING_SPEED), 0);
	}
	angleLCD = tmp_rev;

	lightValue = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
	// min & max values
	if(lightValue > LIGHT_MIN) // dark line treshold
	{
		lightValue = LIGHT_MIN;
	}
	else if(lightValue < LIGHT_MAX) // white reflaction treshold
	{
		lightValue = LIGHT_MAX;
	}
	else
	{
		;
	}
	lightLCD = lightValue;

	SetEvent(AlgoTask, AlgoLightEvent);

	if(cnt100ms == 10)
	{
		distanceValue = ecrobot_get_sonar_sensor(PORT_SONAR);
		distanceLCD = distanceValue;
		SetEvent(AlgoTask, AlgoDistEvent);
		cnt100ms = 0;
	}

	cnt100ms++;
	TerminateTask();
}

TASK(ButtonTask)
{

#if 0
	static U8 last_touch_state = 0;
	U8 touch_state = 0;

		touch_state = ecrobot_get_touch_sensor(PORT_TOCUH_SENSOR);

		if( touch_state > last_touch_state )
		{
			// current state has changed from NOT Pressed to Pressed
			SetEvent(SysTask, TouchOnEvent);
			buttonLCD = 1;
		}
		else
		{
			SetEvent(SysTask, TouchOffEvent);
			buttonLCD = 0;
		}

		last_touch_state = touch_state;

	TerminateTask();
#else

	static U8 old_touch_state = 1;
	static enum
	{
		WHITE,
		BLACK,
		BLUR
	} calibration_state = WHITE;
	U8 cur_touch_state = 0;
	S32 light_value;

	U16 display_cnt=0;

	startCalibration = ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR);
	calibrationLCD = "WHITE";

		while(startCalibration == TRUE)
		{
			cur_touch_state = ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR);

			light_value = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
			lightLCD = light_value;

			if(cur_touch_state > old_touch_state)
			{
				switch (calibration_state)
				{
					case WHITE:
						g_white_ref = light_value + 10;
						calibration_state = BLACK;
						calibrationLCD = "BLACK";
						break;
					case BLACK:
						g_black_ref = light_value - 10;
						calibration_state = BLUR;
						calibrationLCD = "BLUR";
						break;
					case BLUR:
						g_blur_ref = light_value;
						calibration_state = WHITE;
						calibrationLCD = "WHITE";
						startCalibration = FALSE;
						break;
					default:
						break;
				}
			}
			old_touch_state = cur_touch_state;

			if (display_cnt++ > 1000)
			{
				display_cnt = 0;
				display_values();
			}

		}
	TerminateTask();
#endif
}

/*Display several information in the screen*/
TASK(IdleTask)
{
	display_values();

	TerminateTask();
}
