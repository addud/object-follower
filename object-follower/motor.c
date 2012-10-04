#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define DELTA	150
#define TABLELIGHT 485

// declare all events
DeclareEvent(TouchOnEvent);
DeclareEvent(TouchOffEvent);
DeclareEvent(EdgeDetectedEvent);
DeclareEvent(TableDetectedEvent);
// declare tasks
DeclareTask(MotorcontrolTask);
DeclareTask(EventdispatcherTask);

void ecrobot_device_initialize() 
{
	//Intializing the light sensor
	ecrobot_set_light_sensor_active(NXT_PORT_S1);
	nxt_motor_set_count(NXT_PORT_A, 1);
}
void ecrobot_device_terminate() 
{
	//Terminating the light sensor
	ecrobot_set_light_sensor_inactive(NXT_PORT_S1);
}
void user_1ms_isr_type2(void) {}



TASK(MotorcontrolTask)
{

	EventMaskType eventmask = 0;
	
	enum{
	RUN,
	BRAKE,
	IDLE
	}motor_state;
	
	enum{
	ONTABLE,
	ATEDGE,
	} car_location = ONTABLE;
	
	motor_state = IDLE;

	while (1) 
	{
		// wait for the events
		WaitEvent(TouchOnEvent | TouchOffEvent | EdgeDetectedEvent | TableDetectedEvent );
		GetEvent(MotorcontrolTask, &eventmask);
		
		//cheack each event mask and clear it
		if (eventmask & EdgeDetectedEvent) {
			car_location = ATEDGE;
			motor_state = BRAKE;
			ClearEvent(EdgeDetectedEvent);
		}

		if (eventmask & TableDetectedEvent) {
			car_location = ONTABLE;
			ClearEvent(TableDetectedEvent);
		}		
		
		if (eventmask & TouchOnEvent) { 
    			// TouchOnEvent occured 
    			ClearEvent(TouchOnEvent);
			//check car location
    			if (car_location == ONTABLE)
    			{
				// all the conditions for motor to run are met
    				motor_state = RUN;
    			}    		
		}
		
		if (eventmask & TouchOffEvent) { 
    			// TouchOffEvent occured 
    			ClearEvent(TouchOffEvent);
    			motor_state = BRAKE;
 
		}
		

		// motor state - machine 
		switch(motor_state)
		{
		case RUN:
			nxt_motor_set_speed(NXT_PORT_A, 100, 0);
			nxt_motor_set_speed(NXT_PORT_B, 100, 0);
			break;
		case BRAKE:
			nxt_motor_set_speed(NXT_PORT_A, 0, 1);
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
			break;
		default:
			nxt_motor_set_speed(NXT_PORT_A, 0, 0);
			nxt_motor_set_speed(NXT_PORT_B, 0, 0);
			break;
		}
		
		// 10 ms loop	
		systick_wait_ms(10);
		
	}
    

	TerminateTask();
}

TASK(EventdispatcherTask)
{

	static U8 last_touch_state = 0;
	U8 tmp_touch_state = 0;
	U16 tmp_light = 0;
	S16 delta_light = 0;
	char *message, *event = NULL;

	enum{
	ONTABLE,
	ATEDGE,
	} last_car_location, cur_car_location;
	
	last_car_location = ONTABLE;
	
	while (1) 
	{
    
		//Reading the light sensor
		tmp_light = ecrobot_get_light_sensor(NXT_PORT_S1);
		// difference between current light value and reference value(table light)
		delta_light = tmp_light - TABLELIGHT;
		
		// check with the delta threshold to enstablish the car position related to the edge
		if( delta_light < DELTA )
		{
			cur_car_location = ONTABLE;
		}
		else
		{
			cur_car_location = ATEDGE;
		}
		
		// check the current car location, set the event only once
		if( cur_car_location != last_car_location )
		{
			if (cur_car_location == ONTABLE) 
			{
				SetEvent(MotorcontrolTask, TableDetectedEvent);
				event = " TableDetectedEvent ";
			}
			else 
			{
				SetEvent(MotorcontrolTask, EdgeDetectedEvent);
				event = " EdgeDetectedEvent ";
			}
			last_car_location = cur_car_location;
		}  
		
		//Read touch sensor
		tmp_touch_state = ecrobot_get_touch_sensor(NXT_PORT_S2);
		
		// touch sensor interpretation, event is set only once
		if( tmp_touch_state > last_touch_state )
		{
			// current state has changed from NOT Pressed to Pressed
			SetEvent(MotorcontrolTask, TouchOnEvent);
			last_touch_state = tmp_touch_state;
		}
		
		if( tmp_touch_state < last_touch_state )
		{
			// current state has changed from Pressed to NOT Pressed
			SetEvent(MotorcontrolTask, TouchOffEvent);
			last_touch_state = tmp_touch_state;
		}
		
		
		//Display
		display_clear(1);
		display_goto_xy(0,0);
		message = "Light: ";
    		display_string(message);
    		display_int(tmp_light,4);
    		display_goto_xy(0,1);
		message = "Delta: ";
    		display_string(message);
    		display_int(delta_light,4);
    		display_goto_xy(0,2);
		message = "Event: ";
    		display_string(event);
		display_update();
	
		systick_wait_ms(10);
		
	}
    
    
	TerminateTask();
}

