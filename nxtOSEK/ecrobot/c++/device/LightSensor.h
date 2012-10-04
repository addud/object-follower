//
// LightSensor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

#include "Sensor.h"

namespace ecrobot
{
/**
 * NXT Light sensor class.
 */
class LightSensor: public Sensor
{
public:
	/**
	 * Constructor (turn on the lamp by default).
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port Light sensor connected port
	 * @param lamp Turn on/off the lamp (true:on/false:off)
	 * @return -
	 */
	explicit LightSensor(ePortS port, bool lamp = true);

	/**
	 * Destructor (turn off the lamp if it was on).
	 * @param -
	 * @return -
	 */
	~LightSensor(void);

	/**
	 * Get brightness.
	 * @param -
	 * @return Brightness value (greater value means brighter)
	 */
	S16 getBrightness(void) const;

	/**
	 * Turn on/off the lamp.
	 * @param lamp true:on/false:off
	 * @return -
	 */
	void setLamp(bool lamp);
};
}

#endif
