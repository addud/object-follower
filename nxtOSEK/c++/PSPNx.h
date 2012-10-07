//
// PSPNx.h
//
// Mindsensor PSPNx wrapper class
//
// 09.28.2008 Jon C. Martin

#ifndef _PSPNX_H
#define _PSPNX_H

//
// these are necessary for data types associated with events and tasks, and the
// i2c function prototypes
//

extern "C" {
#include "ecrobot_interface.h"
#include "kernel.h"
#include "nxt_avr.h"
#include "i2c.h"
};

//
// this has definitions for the C++ classes
//

#include "LejosOSEKCC.h"
#include "Vector.h"

enum
{
	PSPNx_SELECT = 1,
	PSPNx_LJ = 2,
	PSPNx_RJ = 4,
	PSPNx_START = 8,
	PSPNx_UP = 16,
	PSPNx_RIGHT = 32,
	PSPNx_DOWN = 64,
	PSPNx_LEFT = 128,
	PSPNx_L2 = 256,
	PSPNx_R2 = 512, 
	PSPNx_L1 = 1024,
	PSPNx_R1 = 2048,
	PSPNx_TRIANGLE = 4096,
	PSPNx_CIRCLE = 8192,
	PSPNx_CROSS = 16384,
	PSPNx_SQUARE = 32768,
};
	
class PSPNx
{
public:
	PSPNx(U8 port, U8 address);
	~PSPNx();
	
	//enable or disable the sensor outside of the constructor/destructor
	void activate();
	void deactivate();
	bool isActive() const { return mActive; }
	
	//set the pad mode - mutually exclusive
	void setAnalog();
	void setDigital();

	//set other modes - ok to combine these
	void setEnergize(bool enable);
	void setADPA(bool enable);
	
	//call regularly
	void update();
	
	//poll methods for the stick
	bool pressed(U16 mask) const;
	bool held(U16 mask) const;
	bool released(U16 mask) const;
	
	VectorT<S8> getLeftStick() const;
	VectorT<S8> getRightStick() const;
	
	//raw gamepad info
	const U8* getRawData() const;
	
	static const U8 DATA_BUFFER_BYTE_SIZE = 6;
private:
	enum
	{
		Button_1,
		Button_2,
		LeftStick_X,
		LeftStick_Y,
		RightStick_X,
		RightStick_Y,
	};

	U8 mPort;
	U8 mAddress;
	U8 mRawData[DATA_BUFFER_BYTE_SIZE];
	U16 mCurrentState;
	U16 mPreviousState;
	U8 mActive;
	
	VectorT<S8> mLeftStick;
	VectorT<S8> mRightStick;
};

#endif

