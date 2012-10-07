//
// LightSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "LightSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
LightSensor::LightSensor(ePortS port, bool lamp)
:
Sensor(port)
{
	this->setLamp(lamp);
}

//=============================================================================
// Destructor
LightSensor::~LightSensor(void)
{
	unset_digi0(Sensor::getPort()); // turn off lamp
}

//=============================================================================
// get brightness (greater value means brighter)
S16 LightSensor::getBrightness(void) const
{
	return (1023 - Sensor::get());
}

//=============================================================================
// turn on/off lamp
void LightSensor::setLamp(bool lamp)
{ 
	if (lamp == true)
	{
		set_digi0(Sensor::getPort());
	}
	else
	{
		unset_digi0(Sensor::getPort());
	}
}
