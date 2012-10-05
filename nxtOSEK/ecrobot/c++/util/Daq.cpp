//
// Daq.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "Daq.h"
using namespace ecrobot;


//=============================================================================
// Constructor
Daq::Daq(Bluetooth& bt)
:
mrBt(bt)
{}

//=============================================================================
// Send data to NXT GamePad
void Daq::send(S8 dataS08[2], S32 dataS32)
{
	U8 data[32];

	if (mrBt.isConnected())
	{
		*reinterpret_cast<U32*>(&data[0])  = systick_get_ms();
		*reinterpret_cast <S8*>(&data[4])  = dataS08[0];
		*reinterpret_cast <S8*>(&data[5])  = dataS08[1];
		*reinterpret_cast<U16*>(&data[6])  = ecrobot_get_battery_voltage();
		*reinterpret_cast<S32*>(&data[8])  = nxt_motor_get_count(0);
		*reinterpret_cast<S32*>(&data[12]) = nxt_motor_get_count(1);
		*reinterpret_cast<S32*>(&data[16]) = nxt_motor_get_count(2);
		*reinterpret_cast<S16*>(&data[20]) = sensor_adc(0);
		*reinterpret_cast<S16*>(&data[22]) = sensor_adc(1);
		*reinterpret_cast<S16*>(&data[24]) = sensor_adc(2);
		*reinterpret_cast<S16*>(&data[26]) = sensor_adc(3);
		*reinterpret_cast<S32*>(&data[28]) = dataS32;

		mrBt.send(data, 32);
	}
}

//=============================================================================
// Send data to NXT GamePad
void Daq::send(S8 dataS08[2], U16 dataU16, S16 dataS16[4], S32 dataS32[4])
{
	U8 data[32];

	if (mrBt.isConnected())
	{
		*reinterpret_cast<U32*>(&data[0])  = systick_get_ms();
		*reinterpret_cast <S8*>(&data[4])  = dataS08[0];
		*reinterpret_cast <S8*>(&data[5])  = dataS08[1];
		*reinterpret_cast<U16*>(&data[6])  = dataU16;
		*reinterpret_cast<S32*>(&data[8])  = dataS32[0];
		*reinterpret_cast<S32*>(&data[12]) = dataS32[1];
		*reinterpret_cast<S32*>(&data[16]) = dataS32[2];
		*reinterpret_cast<S16*>(&data[20]) = dataS16[0];
		*reinterpret_cast<S16*>(&data[22]) = dataS16[1];
		*reinterpret_cast<S16*>(&data[24]) = dataS16[2];
		*reinterpret_cast<S16*>(&data[26]) = dataS16[3];
		*reinterpret_cast<S32*>(&data[28]) = dataS32[3];

		mrBt.send(data, 32);
	}
}

