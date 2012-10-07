#include <stdlib.h>
#include <string.h>
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

/*Declaring the timer counter*/
DeclareCounter( SysTimerCnt);

/*Declaring all tasks*/
DeclareTask( ButtonTask);
DeclareTask( DistanceTask);
DeclareTask( IdleTask);

static U8 startCalibration = FALSE;

static int size_ref = 100;

// global variables used to display information
static int sizeLCD;
char *calibrationLCD;

void display_values(void) {
	char *message = NULL;
	U8 line = 0;

	display_goto_xy(0, line++);
	message = "size: ";
	display_string(message);
	display_int(sizeLCD, 4);

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

TASK(DistanceTask) {

	static S8 tracking_enabled = -1;

	U8 rectindex;

	int area, size,x,y;

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

		}

	}

	TerminateTask();
}

TASK(ButtonTask) {

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

/*Display several information in the screen*/TASK(IdleTask) {
	display_values();

	TerminateTask();
}
