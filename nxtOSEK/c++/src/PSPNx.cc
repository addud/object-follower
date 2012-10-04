//
// PSPNx.cc
//
// Mindsensor PSPNx wrapper class
//
// 09.28.2008 Jon C. Martin

#include "PSPNx.h"
#include <string.h>

// PSPNx
PSPNx::PSPNx(U8 port, U8 address)
:	mPort(port)
,	mAddress(address)
,	mCurrentState(0)
,	mPreviousState(0)
,	mActive(true)
{
	memset(mRawData, 0, sizeof(U8)*DATA_BUFFER_BYTE_SIZE);
	ecrobot_init_i2c(mPort, LOWSPEED);
}

// ~PSPNx
PSPNx::~PSPNx()
{
	deactivate();
}

// activate
void PSPNx::activate()
{
	if(!mActive)
	{
		mActive = true;
		ecrobot_init_i2c(mPort, LOWSPEED);
	}
}

// deactivate
void PSPNx::deactivate()
{
	if(mActive)
	{
		mActive = false;
		ecrobot_term_i2c(mPort);	
	}
}

// setAnalog
void PSPNx::setAnalog()
{
	U8 inData = 's';
	ecrobot_send_i2c(mPort, 0x01, 0x41, &inData, 1);
}

// setDigital
void PSPNx::setDigital()
{
	U8 inData = 'A';
	ecrobot_send_i2c(mPort, 0x01, 0x41, &inData, 1);
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

	ecrobot_send_i2c(mPort, 0x01, 0x41, &inData, 1);
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

	ecrobot_send_i2c(mPort, 0x01, 0x41, &inData, 1);
}

// update
void PSPNx::update()
{
	//if we can't get a read off of the port, bail unit the next update
	if(ecrobot_read_i2c(mPort, 0x01, 0x42, mRawData, DATA_BUFFER_BYTE_SIZE) == 0)
	{
		return;	
	}
	
	mPreviousState = mCurrentState;
	mCurrentState = (*(U16*)mRawData) ^ 0xffff;
	
	memcpy(&mLeftStick, &mRawData[LeftStick_X], sizeof(VectorT<S8>));
	memcpy(&mRightStick, &mRawData[RightStick_X], sizeof(VectorT<S8>));
}

// getRawData
const U8* PSPNx::getRawData() const
{
	return 	mRawData;
}

// getLeftStick
VectorT<S8> PSPNx::getLeftStick() const
{
	return mLeftStick;
}

// getRightStick
VectorT<S8> PSPNx::getRightStick() const
{
	return mRightStick;
}
	
// pressed
bool PSPNx::pressed(U16 mask) const
{
     return (!(mPreviousState & mask)) && (mCurrentState & mask);
}

// held
bool PSPNx::held(U16 mask) const
{
	return (mPreviousState & mask) && (mCurrentState & mask);
}

// released
bool PSPNx::released(U16 mask) const
{
	return ((mPreviousState & mask) && !(mCurrentState & mask));
}

