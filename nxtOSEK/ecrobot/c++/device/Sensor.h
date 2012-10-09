//
// Sensor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Port.h"

extern "C"
{
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * A/D sensor abstract class.
 */
class Sensor
{
public:	
	/**
	 * Get raw A/D value.
	 * @param -
	 * @return raw A/D value (0 to 1023)
	 */
	inline S16 get(void) const { return static_cast<S16>(sensor_adc(Sensor::getPort())); }

protected:
	/**
	 * Get the sensor connected port.
	 * @param -
	 * @return Sensor connected port
	 */
	inline ePortS getPort(void) const { return mPort; }

	/**
	 * Constructor.
	 * @param port Sensor connected port
	 * @param power Power mode
	 * @return -
	 */
	explicit Sensor(ePortS port, ePower power=POWER_OFF): mPort(port)
	{
		AssertDeviceConstructor("Sensor Assert");
		nxt_avr_set_input_power(port, power);
	}

	/**
	 * Destructor (power off the sensor).
	 * @param -
	 * @return -
	 */
	virtual ~Sensor(void) { nxt_avr_set_input_power(mPort, POWER_OFF); }

private:
	ePortS mPort;
};
}

#endif
