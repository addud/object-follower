//
// ColorSensor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef COLORSENSOR_H_
#define COLORSENSOR_H_

#include "I2c.h"

namespace ecrobot
{
/**
 * HiTechnic Color sensor (http://www.hitechnic.com/) class.
 *
 * [ How to use with TOPPERS/ATK1(OSEK) ]<BR>
 * I2C (derived/compositted) class and Clock class internally use RTOS features.
 * Thus, user needs to implement a C function and RTOS provided events.<BR><BR>
 * + Invoke SleeperMonitor function in user_1msec_isr_type2 hook.<BR>
 * &nbsp;&nbsp;void user_1ms_isr_type2(void)<BR>
 * &nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;SleeperMonitor(); // needed for I2C devices and Clock class<BR>
 * &nbsp;&nbsp;}<BR>
 * <BR>
 * + Define EventSleepI2C and EventSleep Events in user oil file.<BR>
 * &nbsp;&nbsp;EVENT EventSleepI2C<BR>
 * &nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;MASK = AUTO;<BR>
 * &nbsp;&nbsp;};<BR><BR>
 * &nbsp;&nbsp;EVENT EventSleep<BR>
 * &nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;MASK = AUTO;<BR>
 * &nbsp;&nbsp;};<BR><BR>
 * &nbsp;&nbsp;TASK TaskMain<BR>
 * &nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;AUTOSTART = TRUE<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;APPMODE = appmode1;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;};<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;PRIORITY = 1;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;ACTIVATION = 1;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;SCHEDULE = FULL;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;STACKSIZE = 512;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;EVENT = EventSleepI2C; <- Here it is<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;EVENT = EventSleep; <- Here it is<BR>
 * &nbsp;&nbsp;};<BR>
 * <BR>
 * [ How to use with TOPPERS/JSP(ITRON) ]<BR>
 * In case of using this class with TOPPERS/JSP(ITRON), RTOS specific definitions for the class are not needed.
 */
class ColorSensor
{
public:
	/**
	 * Constructor (activate I2C).
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port Color sensor connected port
	 * @return -
	 */
	explicit ColorSensor(ePortS port);

	/**
	 * Get color number per Hi-Technic color number chart.
	 * @param -
	 * @return Color number (0:Black to 17:White)
	 */
	U8 getColorNumber(void) const;
	
	/**
	 * Get raw color data.
	 * @param rgb rgb[0]: red<BR>
	 *            rgb[1]: green<BR>
	 *            rgb[2]: blue
	 * @return -
	 */
	void getRawColor(S16 rgb[3]) const;
	
	/**
	 * Get raw I2C data.
	 * @param data
	 * Data representation from the sensor, per Hi-Technic's documentation:\n
	 * data[0]: color number<BR>
	 * data[1]: red saturation<BR>
	 * data[2]: green saturation<BR>
	 * data[3]: blue saturation<BR>
	 * data[4]: raw red upper 2 bits<BR>
	 * data[5]: raw red lower 8 bits<BR>
	 * data[6]: raw green upper 2 bits<BR>
	 * data[7]: raw green lower 8 bits<BR>
	 * data[8]: raw blue upper 2 bits<BR>
	 * data[9]: raw blue lower 8 bits<BR>
	 * data[10]: color index (2 bits per r/g/b)<BR>
	 * data[11]: normalized red<BR>
	 * data[12]: normalized green<BR>
	 * data[13]: normalized blue
	 * @return -
	 */
	inline void get(U8 data[14]) const { mI2c.receive(0x42, data, 14); }


private:
	I2c mI2c; // composite
};
}

#endif
