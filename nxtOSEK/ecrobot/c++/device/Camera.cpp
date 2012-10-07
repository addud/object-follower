//
// Camera.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "Camera.h"
using namespace ecrobot;

#include <string.h>

//=============================================================================
// Constructor
Camera::Camera(ePortS port)
:
mI2c(I2c(port)) // activate I2C
{
	memset(mBuffer, 0, DATA_BUFFER_BYTE_SIZE); // zero clear data buffer
}

//=============================================================================
// Enable/disable tracking objects
void Camera::enableTracking(boolean enable)
{
	if (enable)
	{
		this->sendCommand(ENABLE_TRACKING);
	}
	else
	{
		this->sendCommand(DISABLE_TRACKING);
	}
}

//=============================================================================
// Get the rectangle containing a tracked object
void Camera::getRectangle(SINT id, Rectangle_T* rect)
{
	rect->upperLeftX  = static_cast<SINT>(mBuffer[1 + 5 * id + 1]);
	rect->upperLeftY  = static_cast<SINT>(mBuffer[1 + 5 * id + 2]);
	rect->lowerRightX = static_cast<SINT>(mBuffer[1 + 5 * id + 3]);
	rect->lowerRightY = static_cast<SINT>(mBuffer[1 + 5 * id + 4]);

	SINT w = rect->lowerRightX - rect->upperLeftX;
	rect->width = (w < 0) ? -w : w; // get absolute value

	SINT h = rect->upperLeftY - rect->lowerRightY;
	rect->height = (h < 0) ? -h : h;  // get absolute value
}

//=============================================================================
// Call regularly to poll the status of the camera device
bool Camera::update(void)
{
	memset(mBuffer, 0, DATA_BUFFER_BYTE_SIZE); // zero clear data buffer
	return mI2c.receive(0x42, mBuffer, DATA_BUFFER_BYTE_SIZE);
}

