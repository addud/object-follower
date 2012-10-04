#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "NxtCam.h"

#define PORT_SONAR 				NXT_PORT_S3
#define PORT_TOUCH_SENSOR		NXT_PORT_S2
//#define PORT_LIGHT_SENSOR 		NXT_PORT_S1
#define PORT_MOTOR_LEFT			NXT_PORT_B
#define PORT_MOTOR_RIGHT		NXT_PORT_A
#define PORT_MOTOR_STEERING		NXT_PORT_C
#define PORT_CAMERA					NXT_PORT_S1

#define COLORID				0

#define TRANSMITION_FACTOR  2.5

#define DKp 	1
#define DKd 	0
#define DKi 	0

#define LKp		0.1		//G:0.10
#define LKd		0.0		//G:0
#define LKi		0.015//0.015	//G:0.15

#define TKp		0.25	//0.25
#define TKi		0

#define CKp		0.00002

#define SLOWDOWN_POINT		20//20
#define BRAKE_POINT			30//30
#define DISTANCE_REF 		(SLOWDOWN_POINT + BRAKE_POINT)

#define LIGHT_REF			g_blur_ref
#define LIGHT_MAX			(g_blur_ref - interval_calib)
#define LIGHT_MIN			(g_blur_ref + interval_calib)
#define WHITE_MARGIN		20		//G:20
#define BLACK_MARGIN		10		//G:10
#define INTFACT				(100.0 / interval_calib)

#define BLURLIMIT			5			//G:5
#define STEERING_LIMIT		100
#define STEERING_SPEED		58			//G:58
#define SPEED_REF			speed_ref 	// G:-75
#define SPEED_ZERO			60
#define MAXSPEED			45
#define INFINITE_DISTANCE_BUFFER_LENGTH 	4
#define INFINITE_DISTANCE					255

#define LIMIT_REDUCTION		30000

#define TURN_RIGHT		1
#define TURN_LEFT		0

#define MAX(a,b)         ((a < b) ?  (b) : (a))
#define MIN(a,b)         ((a > b) ?  (b) : (a))
#define ABS(x)           (((x) < 0) ? -(x) : (x))

/*Declaring the timer counter*/
DeclareCounter( SysTimerCnt);

/*Declaring all tasks*/
DeclareTask( ButtonTask);
DeclareTask( DistanceTask);
DeclareTask( LightTask);
DeclareTask( IdleTask);

static U16 lightValue;
static U8 turn,spd_brake;
static S16 revolution, speed_reduction_light=0, speed_ref = -75, spd_correction;
static U16 g_white_ref = 460, g_black_ref = 630, g_blur_ref = 505,
		interval_calib = 100;

U8 brakespd;



static U8 startCalibration = FALSE;

// global variables used to display information
S16 speedLCD, distanceLCD, buttonLCD, disterrorLCD, correctionLCD, bufferLCD,
		angleLCD, turnLCD, lightLCD, lighterrorLCD;
char *calibrationLCD;

void motor_command(S16 rev_tgt) {

	S8 sign = 0;
	S16 tmp_rev = 0, spdturn = 0;
	static S16 spdturnI = 0;

	// get steering value
	tmp_rev = nxt_motor_get_count(PORT_MOTOR_STEERING);

	if (rev_tgt >= tmp_rev) {
		spdturn = rev_tgt - tmp_rev;
	} else {
		spdturn = tmp_rev - rev_tgt;
	}
	spdturnI = spdturnI + spdturn;

	if (((tmp_rev <= rev_tgt) && (turn == TURN_RIGHT)) || ((tmp_rev >= rev_tgt)
			&& (turn == TURN_LEFT))) {
		nxt_motor_set_speed(PORT_MOTOR_STEERING, 0, 1);

	} else {
		if (turn == TURN_LEFT) {
			sign = 1;
		} else {
			sign = -1;
		}

		nxt_motor_set_speed(PORT_MOTOR_STEERING, (sign * (STEERING_SPEED
				+ ((TKp * spdturn) + (TKi * spdturnI)))), 0);
	}

	//angleLCD = tmp_rev;
}
void display_values(void) {
	char *message = NULL;
	U8 line = 0;
	int rectindex,area=333;

	static int nxtcamtransaccounter=0;
	static S8 tracking_enabled = -1;
	static U8* data;

	int i,sum=0;

	if (tracking_enabled!=0){

	tracking_enabled = send_nxtcam_command(PORT_CAMERA,ENABLE_TRACKING);
	return;
	}

	//Display
	display_clear(1);
	display_goto_xy(0, line++);
	message = "Tracking ";
	display_string(message);
	display_int(tracking_enabled,4);

	data = getdata();

	for (i=0;i<41;i++) {
		sum+=data[i];
	}

	display_goto_xy(0, line++);
	message = "Sum: ";
	display_string(message);
	display_int(sum,4);

	rectindex = getbiggestrect(COLORID,50);

	display_goto_xy(0, line++);
	message = "Index: ";
	display_string(message);
	display_int(rectindex,4);

	if (rectindex>=0) {

		area =getArea(rectindex);

	}

	display_goto_xy(0, line++);
	message = "Index: ";
	display_string(message);
	display_int(area,4);

	nxtcamtransaccounter = request(PORT_CAMERA);

	display_update();

}

/*Light sensor commands*/
void ecrobot_device_initialize() {
	//Intializing the light sensor
//	ecrobot_set_light_sensor_active(PORT_LIGHT_SENSOR);
//	ecrobot_init_sonar_sensor(PORT_SONAR);
	nxt_motor_set_count(PORT_MOTOR_STEERING, 0);
	init_nxtcam(PORT_CAMERA);
	interval_calib = MIN((g_blur_ref - g_white_ref),(g_black_ref - g_blur_ref));
}
void ecrobot_device_terminate() {
	//Terminating the light sensor
//	ecrobot_set_light_sensor_inactive(PORT_LIGHT_SENSOR);
//	ecrobot_term_sonar_sensor(PORT_SONAR);
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_STEERING, 0, 1);
	term_nxtcam(PORT_CAMERA);
}
/*Initializing counter*/
void user_1ms_isr_type2(void) {
	if (startCalibration == FALSE) {
		(void) SignalCounter(SysTimerCnt);
	}
}

void WheelsControl(S8 spd, U8 brake) {

	//disterrorLCD = brake;

	speedLCD = spd;

	//spd=0;

	spd = spd - speed_reduction_light;

	if (brake) {
		spd = SPEED_REF;
	}

	nxt_motor_set_speed(PORT_MOTOR_RIGHT, (SPEED_REF - spd), brake);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, (SPEED_REF - spd), brake);
}

void DistPID() {

	static S32 distance_buffer[INFINITE_DISTANCE_BUFFER_LENGTH];
	static U8 i;

	S32 cur_distance, dist_err, temp_dist_reading;

	S32 speed_correction;
	U32 distancebuffer_sum;
	U8 j = 0;
	U8 brake_tmp = 0;

	temp_dist_reading = ecrobot_get_sonar_sensor(PORT_SONAR);

	//we're using a ring buffer of INFINITE_DISTANCE_BUFFER_LENGTH elements to store the last readings
	distance_buffer[i] = temp_dist_reading;
	i++;
	i &= ~(INFINITE_DISTANCE_BUFFER_LENGTH);
	distanceLCD = temp_dist_reading;
	distancebuffer_sum = 0;
	for (j = 0; j < INFINITE_DISTANCE_BUFFER_LENGTH; j++) {
		distancebuffer_sum += distance_buffer[j];
	}
	bufferLCD = distancebuffer_sum;

	//if the reading is -1, the sensor is not ready, so we skip this control cycle
	if (temp_dist_reading >= 0) {
		//if the last INFINITE_DISTANCE_BUFFER_LENGTH readings were not all equal to INFINITE_DISTANCE (255)
		//and the current reading is not INFINITE_DISTANCE (255) then we can accept it and control according to it
		//otherwise we don't accept the current reading and skip this cycle of the control loop
		if (((distancebuffer_sum < (INFINITE_DISTANCE
				* INFINITE_DISTANCE_BUFFER_LENGTH)) && (temp_dist_reading
				< INFINITE_DISTANCE))

		||
		//if the last INFINITE_DISTANCE_BUFFER_LENGTH readings wereall equal to INFINITE_DISTANCE (255)
				//then we must proceed forward according to the reading
				(distancebuffer_sum == (INFINITE_DISTANCE
						* INFINITE_DISTANCE_BUFFER_LENGTH)))

		{
			cur_distance = temp_dist_reading;

			dist_err = cur_distance - DISTANCE_REF;

			disterrorLCD = dist_err;

			if (dist_err < 0) {

				//this is a classic PID controller formula, with the backwards moving correction (Kret)
				speed_correction = (S32)(DKp * dist_err);

				if (cur_distance < BRAKE_POINT) {
					brake_tmp = 1;
				} else {
					brake_tmp = 0;
				}

			} else {
				speed_correction = 0;
				brake_tmp = 0;
			}
			spd_brake = brake_tmp;
			spd_correction = speed_correction;

		}
	}
}

void LightPID(U16 lightValue) {
	static S16 oldLightP;
	static S32 lightI;
	S16 lightP, lightD;

	lightP = (lightValue - LIGHT_REF) * INTFACT; // -100 < lightP < 100  fixed interval calibration PID
	lighterrorLCD = lightP;
	if (lightP <= 0) {
		turn = TURN_RIGHT;
	} else {
		turn = TURN_LEFT;
	}
	turnLCD = turn;

	lightD = lightP - oldLightP;

	// accumulate only when reference is far away
	if ((lightValue == LIGHT_MIN) || (lightValue == LIGHT_MAX)) {
		if (ABS(lightI) < 3600000000) {
			lightI = lightI + lightP;
		}
	} else {
		lightI = 0;
	}

	if(ABS(lightI) > LIMIT_REDUCTION)
	{
		speed_reduction_light = ABS(CKp * lightI);
//		WheelsControl(0,1);
//		spd_brake = 1;

	} else {
		speed_reduction_light = 0;
	}

	// PID formula
	revolution = LKp * lightP + LKd * lightD + LKi * lightI;

	if (revolution > STEERING_LIMIT) {
		revolution = STEERING_LIMIT;
	}
	if (revolution < -STEERING_LIMIT) {
		revolution = -STEERING_LIMIT;
	}

	angleLCD = revolution;

	oldLightP = lightP;

}

TASK(LightTask)
{
//	motor_command(revolution);
//
//	//read the light value
//	lightValue = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
//
//	// min & max values
//	if(lightValue > LIGHT_MIN) // dark line treshold
//	{
//		lightValue = LIGHT_MIN;
//	}
//	else if(lightValue < LIGHT_MAX) // white reflaction treshold
//	{
//		lightValue = LIGHT_MAX;
//	}
//	else if(
//			(lightValue < (LIGHT_REF + BLURLIMIT)) &&
//			(lightValue > (LIGHT_REF - BLURLIMIT)) )
//	{
//		lightValue = LIGHT_REF;
//	}
//	else
//	{
//		;
//	}
//	lightLCD = lightValue;
//
//
//	LightPID(lightValue);
//
//	// control speed 1ms
//	WheelsControl(spd_correction, spd_brake);

	TerminateTask();
}

TASK(DistanceTask)
{
//	DistPID();

	TerminateTask();
}
TASK(ButtonTask)
{

//	static U8 old_touch_state = 1;
//	static enum
//	{
//		WHITE,
//		BLACK,
//		BLUR,
//		SPEED65,
//		SPEED68,
//		SPEED70,
//		SPEED73,
//		SPEED74,
//		SPEED75,
//		SPEED76,
//		SPEED77,
//		SPEED78,
//		SPEED80,
//		DONE
//	}calibration_state = WHITE;
//	U8 cur_touch_state = 0;
//	S32 light_value;
//
//	startCalibration = ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR);
//	calibrationLCD = "WHITE";
//
//	while(startCalibration == TRUE)
//	{
//		cur_touch_state = ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR);
//
//		if(ecrobot_is_ENTER_button_pressed())
//		{
//			calibration_state = DONE; // go to default state
//			calibrationLCD = "DONE";
//		}
//
//		light_value = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
//		lightLCD = light_value;
//
//		if(cur_touch_state > old_touch_state)
//		{
//			switch (calibration_state)
//			{
//				case WHITE:
//				g_white_ref = light_value + WHITE_MARGIN;
//				calibration_state = BLACK;
//				calibrationLCD = "BLACK";
//				break;
//				case BLACK:
//				g_black_ref = light_value - BLACK_MARGIN;
//				calibration_state = BLUR;
//				calibrationLCD = "BLUR";
//				break;
//				case BLUR:
//				g_blur_ref = light_value;
//				speed_ref = -65;
//				calibration_state = SPEED68; // go to speed state
//				calibrationLCD = "SPEED65";
//				break;
//				case SPEED68:
//				speed_ref = -68;
//				calibration_state = SPEED70; // go to default state
//				calibrationLCD = "SPEED68";
//				break;
//				case SPEED70:
//				speed_ref = -70;
//				calibration_state = SPEED73; // go to default state
//				calibrationLCD = "SPEED70";
//				break;
//				case SPEED73:
//				speed_ref = -73;
//				calibration_state = SPEED74; // go to default state
//				calibrationLCD = "SPEED73";
//				break;
//				case SPEED74:
//				speed_ref = -74;
//				calibration_state = SPEED75; // go to default state
//				calibrationLCD = "SPEED74";
//				break;
//				case SPEED75:
//				speed_ref = -75;
//				calibration_state = SPEED76; // go to default state
//				calibrationLCD = "SPEED75";
//				break;
//				case SPEED76:
//				speed_ref = -76;
//				calibration_state = SPEED77; // go to default state
//				calibrationLCD = "SPEED76";
//				break;
//				case SPEED77:
//				speed_ref = -77;
//				calibration_state = SPEED78; // go to default state
//				calibrationLCD = "SPEED77";
//				break;
//				case SPEED78:
//				speed_ref = -78;
//				calibration_state = SPEED80; // go to default state
//				calibrationLCD = "SPEED78";
//				break;
//				case SPEED80:
//				speed_ref = -80;
//				calibration_state = DONE; // go to default state
//				calibrationLCD = "SPEED80";
//				break;
//				default:
//				interval_calib = MIN((g_blur_ref - g_white_ref),(g_black_ref - g_blur_ref));
//				startCalibration = FALSE;
//				break;
//			}
//		}
//		old_touch_state = cur_touch_state;
//
//		display_values();
//
//		// 10 ms loop
//		systick_wait_ms(10);
//
//	}
//	WheelsControl(0,0);
	TerminateTask();
}

/*Display several information in the screen*/
TASK(IdleTask)
{
	display_values();

	TerminateTask();
}
