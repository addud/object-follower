//
// TouchSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "TouchSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
TouchSensor::TouchSensor(ePortS port)
:
Sensor(port)
{}

//=============================================================================
// get Touch Sensor status
bool TouchSensor::isPressed(void) const
{
	return static_cast<bool>(Sensor::get() < 512);
}

