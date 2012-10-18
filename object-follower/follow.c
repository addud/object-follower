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

#define DESIRED_SIZE	50

//Maximum total speeed fed to a motor
#define MAX_SPEED		90
//Normal speed of without any adjustments from the PID controllers
#define NORMAL_SPEED	70
//Maximum speed where the robot does not move forward
#define STALL_SPEED		50

/*Mutex lock for shared object data*/
DeclareResource(dataMutex);

/*Declaring the timer counter*/
DeclareCounter( SysTimerCnt);

/*Declaring all tasks*/
//DeclareTask( ButtonTask);
DeclareTask( DistanceTask);
DeclareTask( IdleTask);
//DeclareTask(MotorControlTask);

typedef struct {
	int area;
	int x;
	int size;
} object_data_t;

static U8 startCalibration = FALSE;

// global variables used to display information
static int sizeLCD, xLCD, yLCD, speedLCD, devspeedLCD;

object_data_t objData = { 0, 0, 0 };

void display_values(void) {
	char *message = NULL;
	U8 line = 0;

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

	display_goto_xy(0, line++);
	message = "speed:";
	display_string(message);
	display_int(speedLCD, 4);

	display_goto_xy(0, line++);
	message = "dev speed:";
	display_string(message);
	display_int(devspeedLCD, 4);

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

object_data_t getData() {
	object_data_t temp;

	GetResource(dataMutex);
	temp = objData;
	ReleaseResource(dataMutex);
	return temp;
}

int getDistance(int area) {
	int a = 0, b = 0;
	int distance;

	//Possible to create a decreasing linear func?????????????????????
	distance = a * area + b;

	return distance;
}

//Function that returns the angle (in degrees) between the car and the object
int getAngle(int hyp, int kat) {
	double angleRad;
	int angleDeg;

	//Use the distance and "object distance from center" = kat
	angleRad = asin((double) kat / hyp);
	angleDeg = (int) (angleRad * 180) / 3.14;

	return angleDeg;
}

signed int getXVal() {
	//Return the x coordinate from rectangle 1
	return getX(1);
}

//PID constants
#define Kp 0.5
#define Ki 0
#define Kd 0

//Returns the calculated deviation from the normal speed
int speedPIDController(int d) {
	// Static vars where the PID values
	// are accumulated
	static int integral = 0;
	static int prevError = 0;

	int error = (DESIRED_SIZE - d);
	integral += error;
	int derivative = error - prevError;
	int out = (Kp * error) + (Ki * integral) + (Kd * derivative);
	prevError = error;

	return out;
}

/**********************************************************************/

TASK(MotorControlTask) {
	//The current object data
	object_data_t data;
	//Distance to the object
	int distance;
	int size;
	//Angle between the follower and the object
	int angle;
	int turnDirection;
	//Divider of power between turning and going forward
	int scaler;
	int onlyTurnThrs = 50;
	//Maximum value to give to a motor
	int new_speed;
	//Motor speed values
	int leftMotorValue;
	int rightMotorValue;

	data = getData();
	distance = getDistance(data.area);
	angle = getAngle(distance, abs(data.x));
	size = data.size;

	if (data.x < 0) {
		turnDirection = -1;
	} else {
		turnDirection = 1;
	}

	//We are going to implement the turning as a deviation from the normal speed given by the speed PID

//	if (angle > onlyTurnThrs) {
//		scaler = 1;
//		//Just guessing this!!!!!!!!!!!!!!!!!!!
//		new_speed = MAX_SPEED;
//	} else {
//		scaler = angle / onlyTurnThrs;
//		//PID not in use yet
//		new_speed = speedPIDController(distance);
//		new_speed = (new_speed > MAX_SPEED) ? new_speed : MAX_SPEED;
//	}

	//If no object is detected, don't calculate new speed
	if (size > 0) {
		int speed_deviation = speedPIDController(size);
		devspeedLCD = speed_deviation;

		new_speed = NORMAL_SPEED + speed_deviation;
		//Trimming
		new_speed = (new_speed > MAX_SPEED) ? MAX_SPEED : new_speed;

	} else {
		new_speed = STALL_SPEED;
		devspeedLCD = 0;
	}
	speedLCD = new_speed;

//Commented this as we don't have direction control yet
//
//	//Calculating the individual motor values in percent
//	leftMotorValue = turnDirection * scaler * motorMaxValue
//			+ (1 - scaler) * motorMaxValue;
//	rightMotorValue = (-turnDirection) * scaler * motorMaxValue
//			+ (1 - scaler) * new_speed;

	leftMotorValue = rightMotorValue = new_speed;

	//Setting the appropriate speed to the motors
//	nxt_motor_set_speed(PORT_MOTOR_LEFT, leftMotorValue, 0);
//	nxt_motor_set_speed(PORT_MOTOR_RIGHT, rightMotorValue, 0);

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
			objData.size = size;
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

	TerminateTask();
}
