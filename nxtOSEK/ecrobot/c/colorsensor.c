    /** colorsensor.c for TOPPERS/ATK(OSEK)
     * Sensor control for LEGO Mindstorms Colorsensor
	 *
     * When the correct byte of data is send, these bytes of data are received:
	 * A4, 56, 00, 00, 32, B1, 00, 00, 2E, 76, 00, 00, 0E, 98, 80, 00, 99, 6E, 00, 00, 92, 49, 00, 00, 43, 5E, 00,
	 * 00, 4F, 1A, 80, 00, 1B, 3E, 00, 00, EC, 19, 00, 00, 65, 01, 00, 00, 21, A6, 80, 00, F0, 80, 29, 00, 0043 
	 *
	 * Example for colorsensor mode:
	 *
	 * 
	 *	TASK(OSEK_Task_Background)
	 *	{	
	 *		colorsensor_init(NXT_PORT_S2, COLORSENSOR);
	 *	
	 *		while(1)
	 *		{
	 *			color = colorsensor_color_get(NXT_PORT_S2);
	 *		
	 *			display_clear(0);
	 *			if(color == RED)
	 *			{
	 *				display_goto_xy(0, 5);
	 *				display_string("red");
	 *			}
	 *			
	 *			else if(color == GREEN)
	 *			{
	 *				display_goto_xy(0, 5);
	 *				display_string("green");
	 *			}
	 *			
	 *			else if(color == DARK_BLUE)
	 *			{
	 *				display_goto_xy(0, 5);
	 *				display_string("dark blue");
	 *			}
	 *			
	 *			else if(color == WHITE)
	 *			{
	 *				display_goto_xy(0, 5);
	 *				display_string("white");
	 *			}
	 *			
	 *			else if(color == YELLOW)
	 *			{
	 *				display_goto_xy(0, 5);
	 *				display_string("yellow");
	 *			}
	 *			
	 *			else if(color == BLACK)
	 *			{
	 *				display_goto_xy(0, 5);
	 *				display_string("black");
	 *			}
	 *			
	 *			else if(color == LIGHT_BLUE)
	 *			{
	 *				display_goto_xy(0, 5);
	 *				display_string("light blue");
	 *			}
	 *			display_update();	
	 *		}
	 *	}
     */ 
	 
// #include "kernel.h"
// #include "kernel_id.h"
#include "ecrobot_interface.h"
// #undef _SENSORS_H
#include "sensors1.h"
#include "colorsensor.h"


static int rgb_buf[3];

/**
 * @author Marcel Hein, Benjamin Bode
 * @brief Sends a 1 byte hex value
 * @note Do not use. Internal function
 * @param [in] port -> NXT_PORT_S1, NXT_PORT_S2, NXT_PORT_S3, NXT_PORT_S4
 * @param [in] value -> COLORSENSOR, LIGHTSENSOR_BLUE, LIGHTSENSOR_RED, LIGHTSENSOR_GREEN
 * @return 
 */
static void colorsensor_send(int port, unsigned char value)
{
	sp_set_mode(port, SP_DIGI0, SP_MODE_OUTPUT);
	sp_set_mode(port, SP_DIGI1, SP_MODE_OUTPUT);
	for(volatile int i = 0; i<200; i++){}
	
	sp_set(port, SP_DIGI0, 0);
    systick_wait_ms(100);
	for(volatile int i = 0; i<8; i++)
	{
		for(volatile int j = 0; j<200; j++){}
		sp_set(port, SP_DIGI0, 1);
	
		if((value &0x80) == 0x80)
		{
		   sp_set(port, SP_DIGI1, 1);
	    }
		else
		{
		   sp_set(port, SP_DIGI1, 0);
		}  
		value = value << 1;
		
		for(volatile int j = 0; j<200; j++){}
		sp_set(port, SP_DIGI0, 0);
	}
	
	sp_set_mode(port, SP_DIGI1, SP_MODE_INPUT);
}

/**
 * @author Marcel Hein, Benjamin Bode
 * @brief Returns a 1 byte hex value. Received data does not matter, it is probably just device information
 * @note Do not use. Internal function
 * @param [in] port -> NXT_PORT_S1, NXT_PORT_S2, NXT_PORT_S3, NXT_PORT_S4
 * @param [out] data -> see top for details
 * @return 
 */
static void colorsensor_recv(int port, unsigned int *data)
{
    unsigned int value =0;

    for (volatile int i = 0; i<8; i++)
	{
		for(volatile int j = 0; j<100; j++){}
		sp_set(port, SP_DIGI0, 1);
		for(volatile int j = 0; j<100; j++){}
		sp_set(port, SP_DIGI0, 0);
		value = value<<1;
		value |= sp_get(port, SP_DIGI1);
	}

	*data=value;
}

/**
 * @author Marcel Hein, Benjamin Bode
 * @brief Initializes the sensor with the specified mode
 * @param [in] port -> NXT_PORT_S1, NXT_PORT_S2, NXT_PORT_S3, NXT_PORT_S4
 * @param [in] address -> COLORSENSOR, LIGHTSENSOR_BLUE, LIGHTSENSOR_RED, LIGHTSENSOR_GREEN
 * @return 
 */
void colorsensor_init(int port, unsigned char address)
{	
	unsigned int data;

    sp_reset(port); // initializes only specified port. (other port might be initialized for different sensors)

	colorsensor_send(port, address);
	for(volatile int i = 0; i<3200; i++){}
	
    for (volatile int i = 0; i<52; i++)
	{ 
    	colorsensor_recv(port, &data);
     	for(volatile int j = 0; j<3800; j++){}
    }

	colorsensor_recv(port, &data);
	colorsensor_recv(port, &data);
}

/**
 * @author Marcel Hein, Benjamin Bode
 * @brief Terminates the sensor
 * @param [in] port -> NXT_PORT_S1, NXT_PORT_S2, NXT_PORT_S3, NXT_PORT_S4
 * @return 
 */
void colorsensor_term(int port)
{
	 sp_set(port, SP_DIGI0, 1);
	 for(volatile int i = 0; i<200; i++){}
	 sp_set(port, SP_DIGI0, 0);
	 for(volatile int i = 0; i<200; i++){}
	 sp_set(port, SP_DIGI0, 1);
	 for(volatile int i = 0; i<200; i++){}
	 sp_set(port, SP_DIGI0, 0);

	 colorsensor_init(port, LIGHTSENSOR_NONE); // turn off the light
}

/**
 * @author Marcel Hein, Benjamin Bode
 * @brief Returns the raw A/D value
 * @param [in] port -> NXT_PORT_S1, NXT_PORT_S2, NXT_PORT_S3, NXT_PORT_S4
 * @return 0 to 1023
 */
int colorsensor_light_get(int port)
{
	volatile int dummy;
	int value;

	sp_set_mode(port, SP_DIGI1, SP_MODE_ADC);
	dummy = sp_read(port, SP_DIGI1);
	while(1)
	{
		if (((*AT91C_ADC_SR & sensor_pins[port].ADCChan) == sensor_pins[port].ADCChan))
		{
			value = sp_read(port, SP_DIGI1);
            break;			
		}
	}

	return value;
}

/**
 * @author Marcel Hein, Benjamin Bode
 * @brief Generates the clock signal to activate the colorsensor and saves rgb values
 * @param [in] port -> NXT_PORT_S1, NXT_PORT_S2, NXT_PORT_S3, NXT_PORT_S4
 */
void colorsensor_light_full(int port)
{
	volatile int dummy;

    sp_set(port, SP_DIGI0, 1);
	dummy = sp_read(port, SP_DIGI1);
	while(1)
	{
		if (((*AT91C_ADC_SR & sensor_pins[port].ADCChan) == sensor_pins[port].ADCChan))
		{
			rgb_buf[0] = sp_read(port, SP_DIGI1); // red
            break;
		}
	}

	sp_set(port, SP_DIGI0, 0);
	dummy = sp_read(port, SP_DIGI1);
	while(1)
	{
		if (((*AT91C_ADC_SR & sensor_pins[port].ADCChan) == sensor_pins[port].ADCChan))
		{
			rgb_buf[1] = sp_read(port, SP_DIGI1); // green
            break;
		}
	}

	sp_set(port, SP_DIGI0, 1);
	dummy = sp_read(port, SP_DIGI1);
	while(1)
	{
		if (((*AT91C_ADC_SR & sensor_pins[port].ADCChan) == sensor_pins[port].ADCChan))
		{
			rgb_buf[2] = sp_read(port, SP_DIGI1); // blue
            break;
		}
	}

	sp_set(port, SP_DIGI0, 0);
}

/**
 * @author Marcel Hein, Benjamin Bode
 * @brief Generates the clock signal to activate the colorsensor and returns the color in RGB
 * @param [in] port -> NXT_PORT_S1, NXT_PORT_S2, NXT_PORT_S3, NXT_PORT_S4
 * @param rgb: Red/Green/Blue
 */
void colorsensor_rgb_get(int port, short int rgb[3])
{
	rgb[0] = (short int)rgb_buf[0];
	rgb[1] = (short int)rgb_buf[1];
	rgb[2] = (short int)rgb_buf[2];
}

/**
 * @author Marcel Hein, Benjamin Bode
 * @brief Generates the clock signal to activate the colorsensor and returns the color
 * @param [in] port -> NXT_PORT_S1, NXT_PORT_S2, NXT_PORT_S3, NXT_PORT_S4
 * @return WHITE, RED, GREEN, DARK_BLUE, YELLO, ORANGE, BLACK, LIGHT_BLUE
 */
int colorsensor_color_get(int port)
{   
	volatile int dummy;
	int red,green,blue;
	
    dummy = colorsensor_light_get(port);
    colorsensor_light_full(port);
    red = rgb_buf[0];
    green = rgb_buf[1];
    blue = rgb_buf[2];

	// analyse color based on rgb data
    int color = UNKNOWN_COLOR;
	if(red > green && green > blue && green > blue*1.1)
	{
	   if (green > 350)
   	   {
   	   		color = YELLOW;
	   }
	   else
	   {
			color = ORANGE;
   	   }
   	}
	else if(red > blue && red > green && red > green*1.5)
	{
		if (green > blue && green > 240)
		{
			color = ORANGE;
		}
		else
		{
			color = RED;
		}
	}
    else if(green < blue && green < red && blue < red)
	{
		if( (red+green+blue) > 900)
		{
			color = WHITE;
		}
		
		else
		{
			color = BLACK;
		}
	}
	else if(green > blue && green > red)
	{
		color = GREEN;
	}
	else if(blue > red && blue > green && green > red)
	{
		color = LIGHT_BLUE;
	}
	else if(blue > red && blue > green && red > green)
	{
		color = DARK_BLUE;
	}

    return color;
}

