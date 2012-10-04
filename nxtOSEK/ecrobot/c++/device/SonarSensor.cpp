//
// SonarSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "SonarSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
SonarSensor::SonarSensor(ePortS port)
:
I2c(port) // activate I2C
{}

//=============================================================================
// get distance in cm (0 to 255)
S16 SonarSensor::getDistance(void) const
{
	U8 data;

	this->get(&data);

	return (static_cast<S16>(data) & 0x00ff);
}

