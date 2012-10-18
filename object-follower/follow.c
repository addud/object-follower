#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "kernel.h"
#include "ecrobot_interface.h"
#include "camera.h"
#include "filter.h"
#include "lib.h"

#define PORT_TOUCH_SENSOR		NXT_PORT_S1
#define PORT_MOTOR_LEFT			NXT_PORT_B
#define PORT_MOTOR_RIGHT		NXT_PORT_A
#define PORT_CAMERA				NXT_PORT_S2

#define COLORID				0

#define DESIRED_DISTANCE 40

/*Mutex lock for shared object data*/
DeclareResource(dataMutex);

/*Declaring the timer counter*/
DeclareCounter( SysTimerCnt);

/*Declaring all tasks*/
DeclareTask( ButtonTask);
DeclareTask( DistanceTask);
DeclareTask( IdleTask);
DeclareTask(MotorControlTask);

static U8 startCalibration = FALSE;

static int size_ref = 100;

// global variables used to display information
static int sizeLCD, xLCD, yLCD;
char *calibrationLCD;

typedef struct objectData objectData;

struct objectData
{
	int area;
	int x;
} objData = {0,0};

void display_values(void) {
	char *message = NULL;
	U8 line = 0;
	
	/*
	display_goto_xy(0, line++);
	message = "size:";
	display_string(message);
	display_int(sizeLCD, 4);

	display_goto_xy(0, line++);
	message = "pos:";
	display_string(message);
	display_int(xLCD, 3);
	display_string(",");
	display_int(yLCD, 3);
*/
	display_goto_xy(1,1);
	display_string("Hello");
	display_update();

}

/*Light sensor commands*/
void ecrobot_device_initialize() {
	init_nxtcam(PORT_CAMERA);
}
void ecrobot_device_terminate() {
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, 0, 1);
	term_nxtcam(PORT_CAMERA);
}
/*Initializing counter*/
void user_1ms_isr_type2(void) {
	if (startCalibration == FALSE ) {
		(void) SignalCounter(SysTimerCnt);
	}
}

/**************Functions for MotorControlTask**************************/

objectData getData()
{
	objectData temp;
	
	GetResource(dataMutex);
	temp = objData;
	ReleaseResource(dataMutex);
	return temp;
}

int getDistance(int area)
{
	int a = 0,b = 0;
	int distance;
	
	//Possible to create a decreasing linear func?????????????????????
	distance = a*area + b;
	
	return distance;
}

//Function that returns the angle (in degrees) between the car and the object
int getAngle(int hyp, int kat)
{
	double angleRad;
	int angleDeg;
	
	
	//Use the distance and "object distance from center" = kat
	angleRad = asin((double)kat/hyp);
	angleDeg = (int)(angleRad*180)/3.14;
	
	return angleDeg;
}

signed int getXVal()
{
	//Return the x coordinate from rectangle 1
	return getX(1);
}

//PID constants
#define Kp 1
#define Ki 0
#define Kd 0
//Time between runs, changes with MotorControlTask/periodTime
#define Dt 0.05f

int pidController(int d)
{	
	// Static vars where the PID values
	// are accumulated
	static float integral = 0.0f;
	static float prevError = 0.0f;
	
	
	float error = (d - DESIRED_DISTANCE);
	integral += (error*Dt);
	float derivative = (error - prevError)/Dt;
	int out = (Kp*error) + (Ki*integral) + (Kd*derivative);
	prevError = error;

	out = 80;
	
	return out;
}

/**********************************************************************/

TASK(MotorControlTask)
{
	//Period time of the task in ms
	int periodTime = 50;
	//The current object data
	objectData data;
	//Distance to the object
	int distance;
	//Angle between the follower and the object
	int angle;
	int turnDirection;
	//Divider of power between turning and going forward
	int scaler;
	int onlyTurnThrs = 50;
	//Maximum value to give to a motor
	int motorMaxValue;
	//Motor speed values
	int leftMotorValue;
	int rightMotorValue;
	
	while(1)
	{
		data = getData();
		distance = getDistance(data.area);
		angle = getAngle(distance, abs(data.x));
		
		if (data.x < 0)
			turnDirection = -1;
		else
			turnDirection = 1;
		
		if (angle > onlyTurnThrs){
			scaler = 1;
			//Just guessing this!!!!!!!!!!!!!!!!!!!
			motorMaxValue = 80;
		}
		else{
			scaler = angle/onlyTurnThrs;
			//PID not in use yet
			motorMaxValue = pidController(distance);
		}

		//Calculating the individual motor values in percent
		leftMotorValue = turnDirection*scaler*motorMaxValue+(1-scaler)*motorMaxValue;
		rightMotorValue = (-turnDirection)*scaler*motorMaxValue+(1-scaler)*motorMaxValue;
		
		//Setting the apropriate speed to the motors
		nxt_motor_set_speed(PORT_MOTOR_LEFT,leftMotorValue,0);
		nxt_motor_set_speed(PORT_MOTOR_RIGHT,rightMotorValue,0);
		
		systick_wait_ms(periodTime);
	}
	
	TerminateTask();
}

TASK(DistanceTask) {

	static S8 tracking_enabled = -1;

	U8 rectindex;

	int area, size, x, y;

	if (tracking_enabled != 0) {
		tracking_enabled = send_nxtcam_command(PORT_CAMERA, ENABLE_TRACKING);
	} else {

		request(PORT_CAMERA);

		rectindex = getbiggestrect(0, -1);

		if (rectindex >= 0) {

			area = getArea(rectindex);

			area = median_filter(area);

			size = fisqrt(area);

			sizeLCD = size;

			x = getX(rectindex);
			y = getY(rectindex);
			
			//Update the struct containing object data
			GetResource(dataMutex);
			objData.area = area;
			objData.x = x;
			ReleaseResource(dataMutex);

			xLCD = x;
			yLCD = y;

		}

	}

	TerminateTask();
}

/*Display several information in the screen*/
TASK(IdleTask) {
	display_values();

	systick_wait_ms(100);
}
