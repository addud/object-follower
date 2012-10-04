/* nxtgt.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(TaskInitialize);
DeclareTask(TaskControl);
DeclareTask(TaskSonar);
DeclareTask(TaskLCD);

/* Definitions */
#define MOTOR_STEERING     NXT_PORT_A
#define MOTOR_LEFT         NXT_PORT_B
#define MOTOR_RIGHT        NXT_PORT_C
#define STEERING_LIMIT             40 /* degree */
#define STEERING_P_GAIN             2 /* proportinal gain */
#define DIFF_GAIN_MAX            0.7F /* 1.0-DIFF_GAIN_MAX: max. differential effect */
#define NEUTRAL_DEAD_ZONE           2 /* degree */
#define PWM_OFFSET                 10 /* friction compensator */
#define EDC_ON                     -1 /* Electronic Differential Control: ON */
#define EDC_OFF                     1 /* Electronic Differential Control: OFF */

static S8 EDC_flag;    				   /* EDC flag */

/* Prototypes */
S32 FrictionComp(S32 ratio, S32 offset);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_set_light_sensor_active(NXT_PORT_S1);
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	ecrobot_init_sonar_sensor(NXT_PORT_S2);
	ecrobot_init_bt_connection();
}

void ecrobot_device_terminate()
{
	nxt_motor_set_speed(MOTOR_STEERING, 0, 1);
	nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(MOTOR_LEFT, 0, 1);
	ecrobot_set_light_sensor_inactive(NXT_PORT_S1);
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	ecrobot_term_sonar_sensor(NXT_PORT_S2);
	ecrobot_term_bt_connection();
}

void user_1ms_isr_type2(void)
{
	StatusType ercd;

	ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
	if(ercd != E_OK)
  	{
    	ShutdownOS(ercd);
  	}
}

/* TaskInitialize */
TASK(TaskInitialize)
{
	nxt_motor_set_speed(MOTOR_STEERING, 0, 1);
	nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(MOTOR_LEFT, 0, 1);
	nxt_motor_set_count(MOTOR_STEERING, 0);
	nxt_motor_set_count(MOTOR_RIGHT, 0);
	nxt_motor_set_count(MOTOR_LEFT, 0);

	EDC_flag = EDC_OFF; 

	TerminateTask();
}

/* TaskControl executed every 10msec */
TASK(TaskControl)
{
	S32 analog_stick_left;  /* speed command data from GamePad */
	S32 analog_stick_right; /* steering command data from GamePad */
	S32 steering_angle;
	S32 steering_err;
	S32 steering_speed;
	S32 diff_gain;
  	U8 touch_sensor;
  	static U8 touch_sensor_state = 0;
	static U8 bt_receive_buf[32];  /* buffer size is fixed as 32 */ 
  	
	/* receive NXTGamePad command
     * byte0 speed_data    -100(forward max.) to 100(backward max.)
     * byte1 steering_data -100(left max.) to 100(right max.)
     */
  	ecrobot_read_bt_packet(bt_receive_buf, 32);
	analog_stick_left = -(S32)(*(S8 *)(&bt_receive_buf[0])); /* reverse the direction */
	analog_stick_right = (S32)(*(S8 *)(&bt_receive_buf[1]));

	/* read Touch Sensor to switch Electronic Differential Control */
  	touch_sensor = ecrobot_get_touch_sensor(NXT_PORT_S4);
  	if (touch_sensor == 1 && touch_sensor_state == 0)
  	{
    	EDC_flag = ~EDC_flag + 1; /* toggle */
  	}
  	touch_sensor_state = touch_sensor;

	/* steering control */
	steering_angle = nxt_motor_get_count(MOTOR_STEERING);
	steering_err = (STEERING_LIMIT*analog_stick_right)/100 - steering_angle;
	steering_speed = STEERING_P_GAIN*steering_err;
	nxt_motor_set_speed(MOTOR_STEERING, FrictionComp(steering_speed,PWM_OFFSET), 1);

	/* wheel motors control with Electronic Differential Control */
	diff_gain = 10; 
	if (steering_angle > NEUTRAL_DEAD_ZONE) /* turn right */
	{
    	if (EDC_flag == EDC_ON)
    	{
      		diff_gain = (S32)((1.0F - (float)steering_angle*DIFF_GAIN_MAX/STEERING_LIMIT)*10);
    	}
    	nxt_motor_set_speed(MOTOR_RIGHT, FrictionComp((analog_stick_left*diff_gain)/10,PWM_OFFSET), 1);
    	nxt_motor_set_speed(MOTOR_LEFT, FrictionComp(analog_stick_left,PWM_OFFSET), 1);
  	}
  	else if (steering_angle < -NEUTRAL_DEAD_ZONE) /* turn left */
  	{
    	if (EDC_flag == EDC_ON)
    	{
      		diff_gain = (S32)((1.0F + (float)steering_angle*DIFF_GAIN_MAX/STEERING_LIMIT)*10);
    	}
    	nxt_motor_set_speed(MOTOR_RIGHT, FrictionComp(analog_stick_left,PWM_OFFSET), 1);
    	nxt_motor_set_speed(MOTOR_LEFT, FrictionComp((analog_stick_left*diff_gain)/10,PWM_OFFSET), 1);
  	}
  	else /* go straight */
  	{
    	nxt_motor_set_speed(MOTOR_RIGHT, FrictionComp(analog_stick_left,PWM_OFFSET), 1);
    	nxt_motor_set_speed(MOTOR_LEFT, FrictionComp(analog_stick_left,PWM_OFFSET), 1);
  	}

	/* send NXT status data to NXT GamePad */
	ecrobot_bt_data_logger((S8)analog_stick_left, (S8)analog_stick_right);

  	TerminateTask();
}

/* TaskSonar executed every 50msec */
TASK(TaskSonar)
{
	S32 sonar;

  	/* Sonar Sensor is invoked just for data logging */
	sonar = ecrobot_get_sonar_sensor(NXT_PORT_S2);

  	TerminateTask();
}

/* TaskLCD executed every 500msec */
TASK(TaskLCD)
{
  	ecrobot_status_monitor("NXT GT");

  	TerminateTask();
}

/* Sub functions */
S32 FrictionComp(S32 ratio, S32 offset)
{
  	if (ratio > 0)
  	{
    	return ((100-offset)*ratio/100 + offset);
  	}
  	else if (ratio < 0)
  	{
    	return ((100-offset)*ratio/100 - offset);
  	}
  	else
  	{
    	return ratio;
  	}
}
