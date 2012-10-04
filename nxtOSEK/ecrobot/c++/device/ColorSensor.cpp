//
// ColorSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "ColorSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
ColorSensor::ColorSensor(ePortS port)
:
mI2c(I2c(port)) // activate I2C
{}

//=============================================================================
// get color number
U8 ColorSensor::getColorNumber(void) const
{
	U8 data[14];

	this->get(data);

	return static_cast<U8>(data[0]);
}

//=============================================================================
// get raw color data (red/green/blue)
void ColorSensor::getRawColor(S16 rgb[3]) const
{
	U8 data[14];

	this->get(data);

	rgb[0] = (static_cast<S16>(data[4]) << 8) | (static_cast<S16>(data[5])); // red
	rgb[1] = (static_cast<S16>(data[6]) << 8) | (static_cast<S16>(data[7])); // green
	rgb[2] = (static_cast<S16>(data[8]) << 8) | (static_cast<S16>(data[9])); // blue
}

