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

#define COLORID					0

#define MIN_DETECTED_AREA		-1

#define SIZE_REFERENCE			50
#define POSITION_REFERENCE		83

//Maximum total speed fed to a motor
#define MAX_SPEED				100
//Normal speed of without any adjustments from the PID controllers
#define NORMAL_SPEED			50
//Maximum speed where the robot does not move forward
#define STALL_SPEED				50
//Speed used for spinning
#define SPIN_SPEED 				65

/*Mutex lock for shared object data*/
DeclareResource(dataMutex);

/*Declaring the timer counter*/
DeclareCounter( SysTimerCnt);

/*Declaring all tasks*/
DeclareTask( DistanceTask);
DeclareTask( IdleTask);
DeclareTask(MotorControlTask);

typedef struct {
	int position;
	int size;
} object_data_t;

static U8 startCalibration = FALSE;

// global variables used to display information
static int sizeLCD, areaLCD, xLCD, speedLCD, devspeedLCD, diradjLCD, lmotLCD,
		rmotLCD;

object_data_t objData = { 0, 0 };

void display_values(void) {
	char *message = NULL;
	U8 line = 0;

	display_goto_xy(0, line++);
	message = "size:";
	display_string(message);
	display_int(sizeLCD, 4);

	display_goto_xy(0, line++);
	message = "area:";
	display_string(message);
	display_int(areaLCD, 5);

	display_goto_xy(0, line++);
	message = "pos:";
	display_string(message);
	display_int(xLCD, 4);

	display_goto_xy(0, line++);
	message = "speed:";
	display_string(message);
	display_int(speedLCD, 4);

	display_goto_xy(0, line++);
	message = "dev speed:";
	display_string(message);
	display_int(devspeedLCD, 4);

	display_goto_xy(0, line++);
	message = "dir dev:";
	display_string(message);
	display_int(diradjLCD, 4);

	display_goto_xy(0, line++);
	message = "left motor:";
	display_string(message);
	display_int(lmotLCD, 4);

	display_goto_xy(0, line++);
	message = "right motor:";
	display_string(message);
	display_int(rmotLCD, 4);

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

//PID constants for speed control
//#define dKp 0.2
#define dKp 0.2
#define dKi 0
#define dKd 0

//Returns the calculated adjustment according to desired direction
//It is applied on top of the NORMAL_SPEED + new_speed
int directionPIDController(int d) {
	// Static vars where the PID values are accumulated
	static int integral = 0;
	static int prevError = 0;

	int error = (POSITION_REFERENCE - d);
	integral += error;
	int derivative = error - prevError;
	int out = (dKp * error) + (dKi * integral) + (dKd * derivative);
	prevError = error;

	return out;
}

int getDistance(size) {
	int distance = -3 * size + 140;
	return distance;
}

/**********************************************************************/

TASK(MotorControlTask) {

	//The current object data
	object_data_t data;

	//Distance to the object
	int position, size;
	int new_speed, direction_adjustment;

	//Motor speed values
	int leftMotorValue;
	int rightMotorValue;

	//Alfa Beta filter values
	float dk_1 = 0, vk_1 = 0, a = 0.85, b = 0.005, dt = 0.05;
	float dk, vk, rk, dm;

	data = getData();
	size = data.size;
	position = data.position;

	//Get the distance!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	dm = getDistance(size) - 20;

	dk = dk_1 + ( vk_1 * dt );
	vk = vk_1;

	rk = dm - dk;

	dk += a * rk;
	vk += ( b * rk ) / dt;

	dk_1 = dk;
	vk_1 = vk;

	if (size > 0 && position > 0) {

		//If an object was detected we apply the alfa-beta filter

		int speed_deviation = vk;
		devspeedLCD = speed_deviation;

		new_speed = NORMAL_SPEED + speed_deviation;
		//Trimming
		new_speed = (new_speed > MAX_SPEED) ? MAX_SPEED : new_speed;

		direction_adjustment = directionPIDController(position);

		speedLCD = new_speed;
		diradjLCD = direction_adjustment;

		leftMotorValue = new_speed - direction_adjustment;
		//Trimming
		leftMotorValue =
				(leftMotorValue > MAX_SPEED) ? MAX_SPEED : leftMotorValue;

		rightMotorValue = new_speed + direction_adjustment;
		//Trimming
		rightMotorValue =
				(rightMotorValue > MAX_SPEED) ? MAX_SPEED : rightMotorValue;

	} else {

		//If no object is detected, we enter spinning mode

		speedLCD = 0;
		diradjLCD = 0;
		devspeedLCD = 0;
		rightMotorValue = SPIN_SPEED;
		leftMotorValue = -SPIN_SPEED;
	}

	lmotLCD = leftMotorValue;
	rmotLCD = rightMotorValue;

	//Setting the appropriate speed to the motors
	nxt_motor_set_speed(PORT_MOTOR_LEFT, leftMotorValue, 0);
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, rightMotorValue, 0);

	TerminateTask();
}

TASK(DistanceTask) {

	static S8 tracking_enabled = -1;

	U8 rectindex;

	int area, size, x;

	if (tracking_enabled != 0) {
		tracking_enabled = send_nxtcam_command(PORT_CAMERA, ENABLE_TRACKING);
	} else {

		request(PORT_CAMERA);

		rectindex = getbiggestrect(0, MIN_DETECTED_AREA);

		if (rectindex >= 0) {

			area = getArea(rectindex);

			area = median_filter(area);

			size = fisqrt(area);

			x = getX(rectindex);

			//Update the struct containing object data
			GetResource(dataMutex);
			objData.position = x;
			objData.size = size;
			ReleaseResource(dataMutex);

			sizeLCD = size;
			areaLCD = area;
			xLCD = x;

		}

	}

	TerminateTask();
}

/*Display several information in the screen*/

TASK(IdleTask) {
	display_values();

	TerminateTask();
}
