//
// SoundSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "SoundSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
SoundSensor::SoundSensor(ePortS port, bool dba)
:
Sensor(port)
{
	this->setDBA(dba);
}

//=============================================================================
// Destructor
SoundSensor::~SoundSensor(void)
{
	unset_digi0(Sensor::getPort());
	unset_digi1(Sensor::getPort());
}

//=============================================================================
// get sound level in percent
S16 SoundSensor::getLevel(void) const
{
	return static_cast<S16>((static_cast<S32>(1023 - Sensor::get()) * 100) >> 10);
}

//=============================================================================
// set the DBA status
void SoundSensor::setDBA(bool dba)
{
	ePortS port = Sensor::getPort();

	if (dba)
	{
    	set_digi1(port);
    	unset_digi0(port);
	}
	else
	{
		unset_digi1(port);
		set_digi0(port);
	}
}

