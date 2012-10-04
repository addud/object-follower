//
// GyroSensor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef GYROSENSOR_H_
#define GYROSENSOR_H_

#include "Sensor.h"

namespace ecrobot
{
/**
 * HiTechnic Gyro sensor (http://www.hitechnic.com/) class.
 */
class GyroSensor: public Sensor
{
public:
	/**
	 * Default gyro sensor offset value.
	 */
	static const S16 DEFAULT_OFFSET = 605;
	
	/**
	 * Constructor.
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port Gyro sensor connected port
	 * @return -
	 */
	explicit GyroSensor(ePortS port);

	/**
	 * Set gyro sensor offset.
	 * @param offset Offset value (The sensor value at 0[deg/sec])
	 * @return -
	 */
	void setOffset(S16 offset);

	/**
	 * Get angler velocity.
	 * @param -
	 * @return Angler velocity [deg/sec]
	 */
	S16 getAnglerVelocity(void) const;

private:
	S16 mOffset;
};
}

#endif
