//
// Bluetooth.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "Bluetooth.h"
using namespace ecrobot;


//=============================================================================
// Constructor
Bluetooth::Bluetooth(void)
:
mIsConnected(false),
mCancelConnection(false)
{
	AssertDeviceConstructor("Bt Assert");
}

//=============================================================================
// Destructor (close existing Bluetooth connection).
Bluetooth::~Bluetooth(void)
{
	this->close(); // close Bluetooth communication
}

//=============================================================================
// connect as slave device
bool Bluetooth::waitForConnection(const CHAR* passkey, U32 duration)
{
	U32 start = systick_get_ms();
	while(!mCancelConnection
		  && !mIsConnected 
		  && (duration == 0 || (systick_get_ms() - start) <= duration))
	{
		ecrobot_init_bt_slave(passkey);

		if (ecrobot_get_bt_status() == BT_STREAM)
		{
			mIsConnected = true;
			return mIsConnected;
		}
	}
	return mIsConnected;
}

//=============================================================================
// Cancel of waiting for a connection.
//
void Bluetooth::cancelWaitForConnection(void)
{
	mCancelConnection = true;
}

//=============================================================================
// connect as master device
bool Bluetooth::waitForConnection(const CHAR* passkey, const U8 address[7], U32 duration)
{
	U32 start = systick_get_ms();
	while(!mCancelConnection
		  && !mIsConnected 
		  && (duration == 0 || (systick_get_ms() - start) <= duration))
	{
		ecrobot_init_bt_master(address, passkey);

		if (ecrobot_get_bt_status() == BT_STREAM)
		{
			mIsConnected = true;
			return mIsConnected;
		}
	}
	return mIsConnected;
}

//=============================================================================
// Get the Bluetooth Device Address of the device
bool Bluetooth::getDeviceAddress(U8 address[7]) const
{
	return static_cast<bool>(ecrobot_get_bt_device_address(address));
}

//=============================================================================
// Get the friendly name of the device.
bool Bluetooth::getFriendlyName(CHAR* name) const
{
	return static_cast<bool>(ecrobot_get_bt_device_name(name));
}

//=============================================================================
// Set the friendly name of the device.
bool Bluetooth::setFriendlyName(const CHAR* name)
{
	return static_cast<bool>(ecrobot_set_bt_device_name(name));
}

//=============================================================================
// get connection status
bool Bluetooth::isConnected(void) const
{
	return mIsConnected;
}

//=============================================================================
// get RSSI
S16 Bluetooth::getRSSI(void)
{
	return ecrobot_get_bt_signal_strength();
}

//=============================================================================
// send packet data
U32 Bluetooth::send(U8* data, U32 length)
{
	return ecrobot_send_bt_packet(data, length);
}

//=============================================================================
// send data
U32 Bluetooth::send(const void* data, U32 offset, U32 length)
{
	return ecrobot_send_bt(data, offset, length);
}

//=============================================================================
// receive packet data
U32 Bluetooth::receive(U8* data, U32 length) const
{
	return ecrobot_read_bt_packet(data, length);
}

//=============================================================================
// receive data
U32 Bluetooth::receive(void* data, U32 offset, U32 length) const
{
	return ecrobot_read_bt(data, offset, length);
}

//=============================================================================
// Reset all settings in the persistent settings in the BlueCore chip.
void Bluetooth::setFactorySettings(void)
{
	ecrobot_set_bt_factory_settings();
	this->close();
}

//=============================================================================
// close the connection
void Bluetooth::close(void)
{
	ecrobot_term_bt_connection();
	mIsConnected = false;
}

