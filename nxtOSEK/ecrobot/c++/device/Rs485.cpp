//
// Rs485.cpp
//
// Copyright 2010 by Takashi Chikamasa, Simone Casale Brunet, Jon C. Martin and Robert W. Kramer
//

#include "Rs485.h"
using namespace ecrobot;


//=============================================================================
// Constructor
Rs485::Rs485(U32 baudRate)
{
	AssertDeviceConstructor("RS485 Assert");
	ecrobot_init_rs485(baudRate);
}

//=============================================================================
// Destructor
Rs485::~Rs485(void)
{
	ecrobot_term_rs485();
}

//=============================================================================
// send data
U32 Rs485::send(U8* data, U32 offset, U32 length)
{
	return ecrobot_send_rs485(data, offset, length);
}

//=============================================================================
// receive data
U32 Rs485::receive(U8* data, U32 offset, U32 length) const
{
	return ecrobot_read_rs485(data, offset, length);
}

