//
// GamePad.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include <string.h>

#include "GamePad.h"
using namespace ecrobot;


//=============================================================================
// Constructor
GamePad::GamePad(const Bluetooth& bt)
:
mrBt(bt)
{
	memset(mRawData, 0, sizeof(U8)*DATA_BUFFER_BYTE_SIZE);
}

//=============================================================================
// get GamePad command
VectorT<S8> GamePad::get(void)
{
	if (mrBt.isConnected())
	{
		mrBt.receive(mRawData, DATA_BUFFER_BYTE_SIZE);
		return VectorT<S8>(mRawData[0], mRawData[1]);
	}
	else
	{
		return VectorT<S8>(0,0);
	}
}

//=============================================================================
// Check the connection status of GamePad controller.
bool GamePad::isConnected(void)
{
	return mrBt.isConnected();
}


