//
// SonarSensor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef SONARSENSOR_H_
#define SONARSENSOR_H_

#include "I2c.h"

namespace ecrobot
{
/**
 * NXT Sonar(Ultrasonic) sensor class.
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
class SonarSensor: public I2c
// Sonar sensor supports various commands to interact with the NXT,
// thus it is derived from I2C to allow user to use send/receive I2c member functions
{
public:
	/**
	 * Constructor (activate I2C).
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port Sonar sensor connected port
	 * @return -
	 */
	explicit SonarSensor(ePortS port);

	/**
	 * Get distance in cm.
	 * @param -
	 * @return distance in cm
	 */
	S16 getDistance(void) const;

	/**
	 * Get raw I2C data.
	 * @param data
	 * Data representation from the sensor:<BR>
	 * data[0]: distance
	 * @return -
	 */
	inline void get(U8 data[1]) const { receive(0x42, data, 1); }

};
}

#endif
