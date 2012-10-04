//
// LegoLight.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "LegoLight.h"
using namespace ecrobot;


//=============================================================================
// Constructor
LegoLight::LegoLight(ePortM port)
:
mMotor(Motor(port, false))
{}

//=============================================================================
// turn on the light
void LegoLight::turnOn(void)
{
	mMotor.setPWM(Motor::PWM_MAX);
}

//=============================================================================
// turn on the light with brightness level
void LegoLight::turnOn(U8 brightness)
{
	brightness = (brightness>Motor::PWM_MAX)? Motor::PWM_MAX:brightness;
	mMotor.setPWM(brightness);
}

//=============================================================================
// turn off the light
void LegoLight::turnOff(void)
{
	mMotor.setPWM(0);
}

