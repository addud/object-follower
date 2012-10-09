//
// CompassSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "CompassSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
CompassSensor::CompassSensor(ePortS port)
:
mI2c(I2c(port)) // activate I2C
{}

//=============================================================================
// get heading (0 to 359, south is 180)
S16 CompassSensor::getHeading(void) const
{
	U8 data[5];
	
	this->get(data);
	
	return (static_cast<S16>(data[3]) | (static_cast<S16>(data[4]) << 8));
}

//=============================================================================
// start sensor calibration
void CompassSensor::beginCalibration(void)
{
	U8 cmd = 0x43;

	mI2c.send(0x41, &cmd, 1);
}

//=============================================================================
// end sensor calibration (true:calibration was successful)
bool CompassSensor::endCalibration(void)
{
	U8 cmd = 0x0;

	mI2c.send(0x41, &cmd, 1);

	// if 0 was retured, it was succeeded. Otherwise it was failed.
	return !cmd;
}

