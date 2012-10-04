//
// NxtColorSensor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin, Robert W. Kramer, Marcel Hein and Benjamin Bode
//

#ifndef NXTCOLORSENSOR_H_
#define NXTCOLORSENSOR_H_

#include "Port.h"

extern "C"
{
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * NXT2.0 Color sensor class.
 */
class NxtColorSensor
{
public:
	/**
 	 * @enum eSensorMode Enum for NXT Color Sensor modes.
 	 */
	enum eSensorMode
	{
		_COLORSENSOR = 0,   /**< activates as a color sensor */
		_LIGHTSENSOR_RED,   /**< activates as a light sensor with red lamp */
		_LIGHTSENSOR_GREEN, /**< activates as a light sensor with green lamp */
		_LIGHTSENSOR_BLUE,  /**< activates as a light sensor with blue lamp */
		_LIGHTSENSOR_WHITE, /**< activates as a light sensor with white lamp */
		_LIGHTSENSOR_NONE,  /**< activates as a light sensor with no lamp */
		_DEACTIVATE         /**< deactivates the sensor */
	};
	
	/**
 	 * @enum eColorNumber Enum for color number of NXT Color Sensor.
 	 */
	enum eColorNumber
	{
		_BLACK = 0,     /**< Black of NXT Color Sensor */
		_BLUE,          /**< Blue of NXT Color Sensor */
		_GREEN,         /**< Green of NXT Color Sensor */
		_YELLOW,        /**< Yellow of NXT Color Sensor */
		_ORANGE,        /**< Orange of NXT Color Sensor */
		_RED,           /**< Red of NXT Color Sensor */
		_WHITE,         /**< White of NXT Color Sensor */
		_UNKNOWN = 99   /**< Unknown color of NXT Color Sensor */
	};

	/**
	 * Constructor.
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port Color sensor connected port
	 * @param mode Sensor mode
	 * @return -
	 */
	explicit NxtColorSensor(ePortS port, eSensorMode mode=_COLORSENSOR);

	/**
	 * Destructor.
	 * @param -
	 * @return -
	 */
	virtual ~NxtColorSensor(void);

	/**
	 * Background process to communicate with the sensor.
	 * Note that this function should be executed repeatedly in a background Task.
	 * @param -
	 * @return -
	 */
	void processBackground(void);

	/**
	 * Set NXT color sensor mode.
	 * @param mode Sensor mode
	 * @return -
	 */
	void setSensorMode(eSensorMode mode);

	/**
	 * Get NXT color sensor mode.
	 * @param -
	 * @return Sensor mode
	 */
	inline eSensorMode getSensorMode(void) const { return mSensorMode; }

	/**
	 * Get raw sensor data in the light sensor modes.
	 * @param -
	 * @return Raw sensor data (0 to 1023)
	 */
	S16 get(void) const;

	/**
	 * Get brightness in the light sensor modes.
	 * @param -
	 * @return Brightness value (greater value means brighter)
	 */
	S16 getBrightness(void) const;

	/**
	 * Get color number in the color sensor mode.
	 * Note that the color number might be unmatch with the real color due to each sensor characteristics, ambient light, angle/distance to color object and other factors.
	 * @param -
	 * @return Color number of NXT Color Sensor
	 */
	eColorNumber getColorNumber(void) const;

	/**
	 * Get raw sensor data in the color sensor mode.
	 * @param rgb rgb[0]: red<BR>
	 *            rgb[1]: green<BR>
	 *            rgb[2]: blue
	 * @return -
	 */
	void getRawColor(S16 rgb[3]) const;

private:
	ePortS mPort;
	eSensorMode mSensorMode;
};
}

#endif
