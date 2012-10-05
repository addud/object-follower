//
// IrSeeker.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "IrSeeker.h"
using namespace ecrobot;


//=============================================================================
// Constructor
IrSeeker::IrSeeker(ePortS port)
:
mI2c(I2c(port)) // activate I2C
{}

//=============================================================================
// get the currently measured direction of the infrared signal (0 to 9)
S16 IrSeeker::getDirection(void) const
{
	U8 data[6];

	this->get(data);

	return (static_cast<S16>(data[0]) & 0x000f);
}

