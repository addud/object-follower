//
// LegoLight.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef LEGOLIGHT_H_
#define LEGOLIGHT_H_

#include "Motor.h"

namespace ecrobot
{
/**
 * Lego Light class.
 */
class LegoLight
{
public:
	/**
	 * Constructor.
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port LEGO light connected port
	 * @return -
	 */
	explicit LegoLight(ePortM port);

	/**
	 * Turn on the light.
	 * @param -
	 * @return -
	 */
	void turnOn(void);

	/**
	 * Turn on the light with brightness level.
	 * @param brightness 0(off)-100(max. brightness level)
	 * @return -
	 */
	void turnOn(U8 brightness);

	/**
	 * Turn off the light.
	 * @param -
	 * @return -
	 */
	void turnOff(void);

private:
	Motor mMotor; // composition
};
}

#endif
