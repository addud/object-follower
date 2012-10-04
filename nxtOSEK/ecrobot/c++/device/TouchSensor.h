//
// TouchSensor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef TOUCHSENSOR_H_
#define TOUCHSENSOR_H_

#include "Sensor.h"

namespace ecrobot
{
/**
 * NXT Touch sensor class.
 */
class TouchSensor: public Sensor
{
public:
	/**
	 * Constructor.
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port Touch sensor connected port
	 * @return -
	 */
	explicit TouchSensor(ePortS port);

	/**
	 * Get touch sensor status.
	 * @param -
	 * @return true:pressed/false:not pressed
	 */
	bool isPressed(void) const;
};
}

#endif
