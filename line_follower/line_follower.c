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

#define DKp 	1
#define DKd 	0
#define DKi 	0

#define LKp		0.1		//G:0.15
#define LKd		0.25		//G:0.15
#define LKi		0.04//1//2  	//G:0.0

//Controls how big the steering difference can be
#define STEERING_LIMIT		30


//Controlling how much each of the PID parts are allowed to contribute
#define allowedI 10.0
#define allowedD 20

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

#define STEERING_SPEED		30			//G:58
#define SPEED_REF			speed_ref 	// G:-75
#define SPEED_ZERO			60
//#define MAXSPEED			45
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
DeclareTask( IdleTask);
DeclareTask( LightTask);

static float lightValue;
static float lightD = 0;
static float oldLightP = 0;
static float lastLightPValue = 0;
static float maxLightP = 0;
static float oldLightValue = 0;
static int derivCounter = 0;
static int oldLightCounter = 0;
static U8 turn;
static S16 revolution, speed_ref = 65;
static U16 g_white_ref = 514, g_black_ref = 603, g_blur_ref = 555,
		interval_calib = 100;

U8 brakespd;

static U8 startCalibration = FALSE;

// global variables used to display information
S16 DpartLCD, distanceLCD, buttonLCD, IpartLCD, correctionLCD, bufferLCD,
		angleLCD, turnLCD, lightLCD, lighterrorLCD;
char *calibrationLCD;

void display_values(void) {
	char *message = NULL;
	U8 line = 0;

	//Display
	display_clear(1);
	display_goto_xy(0, line++);
	message = "Calib ";
	display_string(message);
	display_string(calibrationLCD);

	display_goto_xy(0, line++);
	message = "Revolut: ";
	display_string(message);
	display_int(revolution, 4); // display speed

	display_goto_xy(0, line++);
	message = "light: ";
	display_string(message);
	display_int(lighterrorLCD, 4); // display light value

	display_goto_xy(0, line++);
	message = "lightD: ";
	display_string(message);
	display_int(DpartLCD, 4); //Display D part of PID
	
	display_goto_xy(0, line++);
	message = "lightP: ";
	display_string(message);
	display_int(IpartLCD, 4); // display I part of PID

	display_goto_xy(0, line++);
	message = "BLUR: ";
	display_string(message);
	display_int(g_blur_ref, 4);

	display_goto_xy(0, line++);
	message = "WHITE: ";
	display_string(message);
	display_int(g_white_ref, 4); // display distance

	display_goto_xy(0, line++);
	message = "BLACK: ";
	display_string(message);
	display_int(g_black_ref, 4); // display distance

	display_update();

}

/*Light sensor commands*/
void ecrobot_device_initialize() {
	//Intializing the light sensor
	ecrobot_set_light_sensor_active(PORT_LIGHT_SENSOR);
	ecrobot_init_sonar_sensor(PORT_SONAR);
	nxt_motor_set_count(PORT_MOTOR_STEERING, 0);
	interval_calib = MIN((g_blur_ref - g_white_ref),(g_black_ref - g_blur_ref));
}
void ecrobot_device_terminate() {
	//Terminating the light sensor
	ecrobot_set_light_sensor_inactive(PORT_LIGHT_SENSOR);
	ecrobot_term_sonar_sensor(PORT_SONAR);
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, 0, 1);
	nxt_motor_set_speed(PORT_MOTOR_STEERING, 0, 1);
}
/*Initializing counter*/
void user_1ms_isr_type2(void) {
	if (startCalibration == FALSE) {
		(void) SignalCounter(SysTimerCnt);
	}
}

//Used by LightTask and ButtonTask
void WheelsControl(S8 spd, U8 brake, S16 revolution) {
	
	//Added SPEED_REF instead of 68, and changed the sign of it in ButtonTask
	
	//For going straight
	//nxt_motor_set_speed(PORT_MOTOR_RIGHT, SPEED_REF + 2, brake);
	//nxt_motor_set_speed(PORT_MOTOR_LEFT, SPEED_REF, brake);
	
	
	nxt_motor_set_speed(PORT_MOTOR_RIGHT, SPEED_REF + revolution, brake);
	nxt_motor_set_speed(PORT_MOTOR_LEFT, SPEED_REF - revolution, brake);
}

void LightPID(U16 lightValue) {
	
	static float lightI;
	float lightP;

	lightP = (lightValue - (float)LIGHT_REF) * (float)INTFACT; // -100 < lightP < 100  fixed interval calibration PID
	
	
	if (ABS(maxLightP) < ABS(lightP)) {
		maxLightP = lightP;
	}
	
	lighterrorLCD = maxLightP;
	
	if (lightP <= 0) {
		turn = TURN_RIGHT;
	} else {
		turn = TURN_LEFT;
	}
	turnLCD = turn;
	
	/*
	//Derivative part with limitation
	if (derivCounter >= 19){
		
		//Only change D part if it doesn't exceed its allowed limit
		if (((lightP - lastLightPValue)*10) < -allowedD/LKd){
			lightD = -allowedD/LKd;
		}
		else if (((lightP - lastLightPValue)*10) > allowedD/LKd){
			lightD = allowedD/LKd;
		}
		else {
			lightD = (lightP - lastLightPValue)*10;
		}
		derivCounter = 0;
		lastLightPValue = lightP;
	}
	else{
		derivCounter++;
	}
	*/
	
	//Derivative part without limitation
	if (derivCounter >= 24){
		lightD = (lightP - lastLightPValue)*8;
		derivCounter = 0;
		lastLightPValue = lightP;
	}
	else{
		derivCounter++;
	}

	//Only accumulate enough so that the I part never inlficts
	//more than allowedI to PID
	if (ABS(lightI + lightP/200) < allowedI/LKi) {
			lightI = lightI + lightP/200;
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

	if (oldLightCounter == 19) {	
		oldLightP = lightP;
		oldLightCounter = 0;
	}
	else {
		oldLightCounter++;
	}
	
	DpartLCD = lightD * LKd;
	IpartLCD = lightP * LKp;

}

TASK(LightTask)
{
	
	//read the light value
	lightValue = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
	
	if (oldLightValue == 0) {
		oldLightValue = lightValue;
	}

	// min & max values
	if(lightValue > LIGHT_MIN) // dark line treshold
	{
		lightValue = LIGHT_MIN;
	}
	else if(lightValue < LIGHT_MAX) // white reflaction treshold
	{
		lightValue = LIGHT_MAX;
	}
	else if(
			(lightValue < (LIGHT_REF + BLURLIMIT)) &&
			(lightValue > (LIGHT_REF - BLURLIMIT)) )
	{
		lightValue = LIGHT_REF;
	}
	else
	{
		;
	}
	lightLCD = lightValue;

	LightPID(lightValue);

	WheelsControl(0, 0, revolution);

	TerminateTask();
}


TASK(ButtonTask)
{

	static U8 old_touch_state = 1;
	static enum
	{
		WHITE,
		BLACK,
		BLUR,
		SPEED65,
		SPEED68,
		SPEED70,
		SPEED73,
		SPEED74,
		SPEED75,
		SPEED76,
		SPEED77,
		SPEED78,
		SPEED80,
		DONE
	}calibration_state = WHITE;
	U8 cur_touch_state = 0;
	S32 light_value;

	startCalibration = ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR);
	calibrationLCD = "WHITE";

	while(startCalibration == TRUE)
	{
		cur_touch_state = ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR);

		if(ecrobot_is_ENTER_button_pressed())
		{
			calibration_state = DONE; // go to default state
			calibrationLCD = "DONE";
		}

		light_value = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
		lightLCD = light_value;

		if(cur_touch_state > old_touch_state)
		{
			switch (calibration_state)
			{
				case WHITE:
				g_white_ref = light_value + WHITE_MARGIN;
				calibration_state = BLACK;
				calibrationLCD = "BLACK";
				break;
				case BLACK:
				g_black_ref = light_value - BLACK_MARGIN;
				calibration_state = BLUR;
				calibrationLCD = "BLUR";
				break;
				case BLUR:
				g_blur_ref = light_value;
				speed_ref = 65;
				calibration_state = SPEED68; // go to speed state
				calibrationLCD = "SPEED65";
				break;
				case SPEED68:
				speed_ref = 68;
				calibration_state = SPEED70; // go to default state
				calibrationLCD = "SPEED68";
				break;
				case SPEED70:
				speed_ref = 70;
				calibration_state = SPEED73; // go to default state
				calibrationLCD = "SPEED70";
				break;
				case SPEED73:
				speed_ref = 73;
				calibration_state = SPEED74; // go to default state
				calibrationLCD = "SPEED73";
				break;
				case SPEED74:
				speed_ref = 74;
				calibration_state = SPEED75; // go to default state
				calibrationLCD = "SPEED74";
				break;
				case SPEED75:
				speed_ref = 75;
				calibration_state = SPEED76; // go to default state
				calibrationLCD = "SPEED75";
				break;
				case SPEED76:
				speed_ref = 76;
				calibration_state = SPEED77; // go to default state
				calibrationLCD = "SPEED76";
				break;
				case SPEED77:
				speed_ref = 77;
				calibration_state = SPEED78; // go to default state
				calibrationLCD = "SPEED77";
				break;
				case SPEED78:
				speed_ref = 78;
				calibration_state = SPEED80; // go to default state
				calibrationLCD = "SPEED78";
				break;
				case SPEED80:
				speed_ref = 80;
				calibration_state = DONE; // go to default state
				calibrationLCD = "SPEED80";
				break;
				default:
				interval_calib = MIN((g_blur_ref - g_white_ref),(g_black_ref - g_blur_ref));
				startCalibration = FALSE;
				break;
			}
		}
		old_touch_state = cur_touch_state;

		display_values();

		// 10 ms loop
		systick_wait_ms(10);

	}
	WheelsControl(0,0,0);
	TerminateTask();
}

/*Display several information in the screen*/
TASK(IdleTask)
{
	display_values();

	TerminateTask();
}
