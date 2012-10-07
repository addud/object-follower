//
// PSPNx.cpp
//
// Mindsensor PSPNx wrapper class
//
// 09.28.2008 Jon C. Martin
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "PSPNx.h"
#include <string.h>

// PSPNx
PSPNx::PSPNx(ePortS port, U8 address)
:
mI2c(I2c(port)), // activate I2C
mAddress(address), // what's this?
mCurrentState(0),
mPreviousState(0),
mLeftStick(VectorT<S8>(0,0)), // Keep effective C++ style guide
mRightStick(VectorT<S8>(0,0)) // Keep effective C++ style guide
{
	memset(mRawData, 0, sizeof(U8)*DATA_BUFFER_BYTE_SIZE);
}

// setAnalog
void PSPNx::setAnalog(void)
{
	U8 inData = 's';

	mI2c.send(0x41, &inData, 1);
}

// setDigital
void PSPNx::setDigital(void)
{
	U8 inData = 'A';

	mI2c.send(0x41, &inData, 1);
}

// setEnergize
void PSPNx::setEnergize(bool enable)
{
	U8 inData;

	if(enable)
	{
		inData = 'E';
	}
	else
	{
		inData = 'D';
	}

	mI2c.send(0x41, &inData, 1);
}

// setADPA
void PSPNx::setADPA(bool enable)
{
	U8 inData;

	if(enable)
	{
		inData = 'N';
	}
	else
	{
		inData = 'O';
	}

	mI2c.send(0x41, &inData, 1);
}

// update
void PSPNx::update(void)
{
	//if we can't get a read off of the port, bail unit the next update
	if(!mI2c.receive(0x42, mRawData, DATA_BUFFER_BYTE_SIZE))
	{
		return;	
	}
	
	mPreviousState = mCurrentState;
//	mCurrentState = (*reinterpret_cast<U16*>(mRawData)) ^ 0xffff;
	mCurrentState = ((static_cast<U16>(mRawData[0]) << 8) | static_cast<U16>(mRawData[1])) ^ 0xffff;
	
	memcpy(&mLeftStick, &mRawData[LeftStick_X], sizeof(VectorT<S8>));
	memcpy(&mRightStick, &mRawData[RightStick_X], sizeof(VectorT<S8>));
}

// get raw I2c data
void PSPNx::get(U8 data[DATA_BUFFER_BYTE_SIZE]) const
{
	memcpy(data, mRawData, DATA_BUFFER_BYTE_SIZE);
}

// getLeftStick
VectorT<S8> PSPNx::getLeftStick(void) const
{
	return mLeftStick;
}

// getRightStick
VectorT<S8> PSPNx::getRightStick(void) const
{
	return mRightStick;
}
	
// pressed
bool PSPNx::pressed(eButtons mask) const
{
     return (!(mPreviousState & mask)) && (mCurrentState & mask);
}

// held
bool PSPNx::held(eButtons mask) const
{
	return (mPreviousState & mask) && (mCurrentState & mask);
}

// released
bool PSPNx::released(eButtons mask) const
{
	return ((mPreviousState & mask) && !(mCurrentState & mask));
}

