//
// GyroSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "GyroSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
GyroSensor::GyroSensor(ePortS port)
:
Sensor(port),
mOffset(DEFAULT_OFFSET)
{}

//=============================================================================
// set sensor offset data at 0 [deg/sec]
void GyroSensor::setOffset(S16 offset)
{
//	mOffset = (1023>offset)? 1023:((offset < 0)? 0:offset);
	mOffset = (offset>1023)? 1023:((offset<0)? 0:offset);
}

//=============================================================================
// get anguler velocity [deg/sec]
S16 GyroSensor::getAnglerVelocity(void) const
{
	return (Sensor::get() - mOffset);
};

