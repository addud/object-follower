//
// NxtColorSensor.cpp
//
// Takashi Chikamasa, Jon C. Martin, Robert W. Kramer, Marcel Hein and Benjamin Bode
//

#include "NxtColorSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
NxtColorSensor::NxtColorSensor(ePortS port, eSensorMode mode)
:
mPort(port),
mSensorMode(mode)
{
	AssertDeviceConstructor("NXT Color Assert");
	ecrobot_set_nxtcolorsensor(mPort, static_cast<U8>(NxtColorSensor::_DEACTIVATE));
	ecrobot_set_nxtcolorsensor(mPort, static_cast<U8>(mSensorMode));
}

//=============================================================================
// Destructor
NxtColorSensor::~NxtColorSensor(void)
{
	ecrobot_term_nxtcolorsensor(mPort);
}

//=============================================================================
// Background process to communicate with NXT Color Sensor
void NxtColorSensor::processBackground(void)
{
	ecrobot_process_bg_nxtcolorsensor();
}

//=============================================================================
// Set sensor mode
void NxtColorSensor::setSensorMode(eSensorMode mode)
{
	mSensorMode = mode;
	ecrobot_set_nxtcolorsensor(mPort, static_cast<U8>(mSensorMode));
}

//=============================================================================
// Get raw sensor data in the light sensor modes.
S16 NxtColorSensor::get(void) const
{
	return static_cast<S16>(ecrobot_get_nxtcolorsensor_light(mPort));
}

//=============================================================================
// Get brightness in the light sensor modes.
S16 NxtColorSensor::getBrightness(void) const
{
	return static_cast<S16>(1023 - this->get());
}

//=============================================================================
// get color number in the color sensor mode.
NxtColorSensor::eColorNumber NxtColorSensor::getColorNumber(void) const
{
	return static_cast<eColorNumber>(ecrobot_get_nxtcolorsensor_id(mPort));
}

//=============================================================================
// get raw sensor data (red/green/blue) in the color sensor mode.
void NxtColorSensor::getRawColor(S16 rgb[3]) const
{
	ecrobot_get_nxtcolorsensor_rgb(mPort, rgb);
}

