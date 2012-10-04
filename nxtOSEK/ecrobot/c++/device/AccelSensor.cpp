//
// AccelSensor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "AccelSensor.h"
using namespace ecrobot;


//=============================================================================
// Constructor
AccelSensor::AccelSensor(ePortS port)
:
mI2c(I2c(port)) // activate I2C
{}

//=============================================================================
// get acceleration in 3 axes(x/y/z)
void AccelSensor::getAccel(S16 axes[3]) const
{
	U8 data[6];

	this->get(data);

	for (SINT i=0; i<3; i++)
	{
		axes[i] = static_cast<S16>(data[i]);
		if (axes[i] > 127)
		{
			axes[i] -= 256;
		}
		/* convert to 10 bit value */
		axes[i] = ((axes[i] << 2) | (static_cast<S16>(data[i+3]) & 0x0003));
	}
}

