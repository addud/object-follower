//
// RcxLightSensor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef RCXLIGHTSENSOR_H_
#define RCXLIGHTSENSOR_H_

#include "Sensor.h"

namespace ecrobot
{
/**
 * RCX Light sensor class.
 */
class RcxLightSensor: public Sensor 
{
public:
	/**
	 * Constructor (supply 9V to the sensor).
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port RCX light sensor connected port
	 * @return -
	 */
	explicit RcxLightSensor(ePortS port);

	/**
	 * Get brightness.
	 * @param -
	 * @return Brightness value (greater value means brighter)
	 */
	S16 getBrightness(void) const;
};
}

#endif
