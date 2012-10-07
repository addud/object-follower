//
// Usb.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "Usb.h"
using namespace ecrobot;


//=============================================================================
// Constructor
Usb::Usb(void)
{
	AssertDeviceConstructor("Usb Assert");
	ecrobot_init_usb();
}

//=============================================================================
// Destructor
Usb::~Usb(void)
{
	ecrobot_term_usb();
}

//=============================================================================
// USB communication handler which must be executed every 1msec
void Usb::commHandler(void)
{
	(void)ecrobot_process1ms_usb();
}

//=============================================================================
// get USB connection status
bool Usb::isConnected(void) const
{
	return static_cast<bool>(ecrobot_is_usb_connected());
}

//=============================================================================
// send data
U32 Usb::send(U8* data, U32 offset, U32 length)
{
	return ecrobot_send_usb(data, offset, length);
}

//=============================================================================
// receive data
U32 Usb::receive(U8* data, U32 offset, U32 length) const
{
	return ecrobot_read_usb(data, offset, length);
}

//=============================================================================
// close connection
bool Usb::close(void)
{
	return ecrobot_disconnect_usb();
}

