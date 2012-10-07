//
// Motor.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "Motor.h"
using namespace ecrobot;

//=============================================================================
// Constructor
Motor::Motor(ePortM port, bool brake)
:
mPort(port),
mBrake(brake),
mPWM(0)
{
	AssertDeviceConstructor("Motor Assert");
}

//=============================================================================
// Destructor
Motor::~Motor(void)
{
	nxt_motor_set_speed(mPort, 0, 1); // set brake to stop the motor immidiately
}

//=============================================================================
// set motor PWM ratio: PWM_MAX to PWM_MIN
void Motor::setPWM(S8 pwm)
{
	mPWM = (pwm>PWM_MAX)? PWM_MAX:((pwm<PWM_MIN)? PWM_MIN:pwm);

	if (mBrake == true)
	{
		nxt_motor_set_speed(mPort, mPWM, 1);
	}
	else
	{
		nxt_motor_set_speed(mPort, mPWM, 0);
	}	
}

//=============================================================================
// set brake (true:brake/false:float)
void Motor::setBrake(bool brake)
{
	mBrake = brake;
	setPWM(mPWM);
}

