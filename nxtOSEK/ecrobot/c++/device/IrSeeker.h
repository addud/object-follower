//
// IrSeeker.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef IRSEEKER_H_
#define IRSEEKER_H_

#include "I2c.h"

namespace ecrobot
{
/**
 * HiTechnic IR Seeker (http://www.hitechnic.com/) class.
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
class IrSeeker
{
public:
	/**
	 * Constructor (activate I2C).
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port IR Seeker connected port
	 * @return -
	 */
	explicit IrSeeker(ePortS port);

	/**
	 * Get the currently measured direction of the infrared signal.
	 * @param -
	 * @return Infrared signal direction
	 */
	S16 getDirection(void) const;

	/**
	 * Get raw I2C data.
	 * @param data
	 * Data representation from the sensor, per Hi-Technic's documentation:<BR>
	 * data[0]: Direction 8 bits<BR>
	 * data[1]: Intensity1 8 bits<BR>
	 * data[2]: Intensity2 8 bits<BR>
	 * data[3]: Intensity3 8 bits<BR>
	 * data[4]: Intensity4 8 bits<BR>
	 * data[5]: Intensity5 8 bits
	 * @return -
	 */
	inline void get(U8 data[6]) const { mI2c.receive(0x42, data, 6); }

private:
	I2c mI2c; // composite
};
}

#endif
