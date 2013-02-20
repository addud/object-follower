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

/* Camera color id of the tracked object */
#define COLORID					0

/* Minimum dectected area recognized as an object by the camera */
#define MIN_DETECTED_AREA		-1

/* References for the control algorithms */
#define SIZE_REFERENCE			50
#define POSITION_REFERENCE		83
#define DESIRED_DISTANCE		20

/* Maximum total speed fed to a motor */
#define MAX_SPEED				100
/* Minimum total speed fed to a motor */
#define MIN_SPEED				-100
/* Normal speed of without any adjustments from the PID controllers */
#define NORMAL_SPEED			50
/* Maximum speed where the robot does not move forward */
#define STALL_SPEED				50
/* Speed used for spinning */
#define SPIN_SPEED 				65

/* Mutex lock for shared object data */
DeclareResource(dataMutex);

/* Declaring all tasks */
DeclareTask(AcquisitionTask);
DeclareTask(ControlTask);
DeclareTask(DisplayTask);

typedef struct {
	int position;
	int size;
} object_data_t;

/* Global variables used to display information */
static int sizeLCD, areaLCD, xLCD, speedLCD, devspeedLCD, diradjLCD, lmotLCD,
		rmotLCD;

/* Resource containing acquired data. Protected by mutex */
object_data_t objData = { 0, 0 };


/* Device initialization */
void ecrobot_device_initialize() {
	init_nxtcam(PORT_CAMERA);
}
void ecrobot_device_terminate() {
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, 0, 1);
	term_nxtcam(PORT_CAMERA);
}

/* Acquire data from sensors */
TASK(AcquisitionTask) {

	static S8 tracking_enabled = -1;
	int rectindex, area, size, x;

	if (tracking_enabled != 0) {
		//Enable object tracking
		tracking_enabled = send_nxtcam_command(PORT_CAMERA, ENABLE_TRACKING);
	} else {

		//Requests data from the camera
		request(PORT_CAMERA);

		rectindex = getbiggestrect(COLORID, MIN_DETECTED_AREA);

		if (rectindex >= 0) {
			//Read data from the camera
			area = getArea(rectindex);
			//Filter the sample
			area = median_filter(area);
			//Extract the object size from the area
			size = fisqrt(area);
			//Get the position of the tracked object
			x = getX(rectindex);

			//Update the struct containing object data
			GetResource(dataMutex);
			objData.position = x;
			objData.size = size;
			ReleaseResource(dataMutex);

			//Prepare data for display
			sizeLCD = size;
			areaLCD = area;
			xLCD = x;

		}

	}

	TerminateTask();
}

/*********** Functions used by the Control Task **************/

/* Gets data from the mutex protected structure */
object_data_t getData() {
	object_data_t temp;

	GetResource(dataMutex);
	temp = objData;
	ReleaseResource(dataMutex);
	return temp;
}

/* Calculates distance to the tracked object based on object size
 * Empirical approximation.
 */
int getDistance(int size) {
	int distance = -2 * size + 102;
	return distance;
}

/* PID constants for speed control */
#define sKp 1.5
#define sKi 0
#define sKd 0

/* Returns the calculated adjustment according to desired speed
 * It is applied on top of the NORMAL_SPEED
 */
int speedPIDController(int d) {
	// Static vars where the PID values are accumulated
	static int integral = 0;
	static int prevError = 0;

	int error = (d - DESIRED_DISTANCE);
	integral += error;
	int derivative = error - prevError;
	int out = (sKp * error) + (sKi * integral) + (sKd * derivative);
	prevError = error;

	return out;
}

/* PID constants for direction control */
#define dKp 0.2
#define dKi 0
#define dKd 0

/* Returns the calculated adjustment according to desired direction
 * It is applied on top of the NORMAL_SPEED + new_speed
 */
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

int speedFilter(int size) {
	//Alfa Beta filter values
	float dk_1 = 0, vk_1 = 0, a = 0.85, b = 0.010, dt = 0.05;
	float dk, vk, rk;
	int dm;

	dm = getDistance(size);

	dk = dk_1 + ( vk_1 * dt );
	vk = vk_1;

	rk = dm - dk;

	dk += a * rk;
	vk += ( b * rk ) / dt;

	dk_1 = dk;
	vk_1 = vk;

	return dk;
}

int turnFilter(int size) {
	//Alfa Beta filter values
	float dk_1 = 0, vk_1 = 0, a = 0.85, b = 0.010, dt = 0.05;
	float dk, vk, rk;
	int dm;

	dm = getDistance(size);

	dk = dk_1 + ( vk_1 * dt );
	vk = vk_1;

	rk = dm - dk;

	dk += a * rk;
	vk += ( b * rk ) / dt;

	dk_1 = dk;
	vk_1 = vk;

	return dk;
}

/* Apply control algorithm on the acquired data and then output to motors */
TASK(ControlTask) {

	//The current object data
	object_data_t data;

	//Distance to the object
	int position, size;
	int new_speed, direction_adjustment;
	int distEstimate;
	int directionEstimate;

	//Motor speed values
	int leftMotorValue;
	int rightMotorValue;

	data = getData();
	size = data.size;
	position = data.position;

	//Estimate the distance and deviation form the tracker
	distEstimate = speedFilter(size);
	directionEstimate = turnFilter(position);

	if (size > 0 && position > 0) {

		//If an object was detected we apply the alfa-beta filter

		int speed_deviation = speedPIDController(distEstimate);
		devspeedLCD = speed_deviation;

		//Calculate new speed based on the distance to the object
		new_speed = (speed_deviation >= 0) ? NORMAL_SPEED + speed_deviation : -NORMAL_SPEED + speed_deviation;
		//Trimming
		new_speed = (new_speed > MAX_SPEED) ? MAX_SPEED : new_speed;
		new_speed = (new_speed < MIN_SPEED) ? MIN_SPEED : new_speed;

		//Calculate speed adjustment to adjust direction
		direction_adjustment = directionPIDController(directionEstimate);

		//Update display values
		speedLCD = new_speed;
		diradjLCD = direction_adjustment;

		leftMotorValue = new_speed - direction_adjustment;

		//Trimming
		leftMotorValue = (leftMotorValue > MAX_SPEED) ? MAX_SPEED : leftMotorValue; //Never going to happen?
		leftMotorValue = (leftMotorValue < MIN_SPEED) ? MIN_SPEED : leftMotorValue;

		rightMotorValue = new_speed + direction_adjustment;

		//Trimming
		rightMotorValue = (rightMotorValue > MAX_SPEED) ? MAX_SPEED : rightMotorValue;
		rightMotorValue = (rightMotorValue < MIN_SPEED) ? MIN_SPEED : rightMotorValue;

	} else {

		//If no object is detected, we enter spinning mode
		rightMotorValue = SPIN_SPEED;
		leftMotorValue = -SPIN_SPEED;

		//Update display values
		speedLCD = 0;
		diradjLCD = 0;
		devspeedLCD = 0;
	}

	//Update display values
	lmotLCD = leftMotorValue;
	rmotLCD = rightMotorValue;

	//Setting the appropriate speed to the motors
	nxt_motor_set_speed(PORT_MOTOR_LEFT, leftMotorValue, 0);
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, rightMotorValue, 0);

	TerminateTask();
}

/*********** Functions used by the Display Task **************/

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

/*Display useful information on the screen*/
TASK(DisplayTask) {
	display_values();

	TerminateTask();
}
