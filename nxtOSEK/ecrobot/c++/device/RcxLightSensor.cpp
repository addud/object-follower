//
// RcxLightSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "RcxLightSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
RcxLightSensor::RcxLightSensor(ePortS port)
:
Sensor(port, POWER_LOWSPEED_9V) // supply 9V to the sensor
{}

//=============================================================================
// get brightness (greater value means brighter)
S16 RcxLightSensor::getBrightness(void) const
{
	return (1023 - Sensor::get());
}

