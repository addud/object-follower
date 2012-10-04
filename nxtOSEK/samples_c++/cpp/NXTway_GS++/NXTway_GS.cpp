//
// NXTway_GS.cpp
//

#include "NXTway_GS.h"


//=============================================================================
// Constructor
NXTway_GS::NXTway_GS(const Nxt& nxt, const GyroSensor& gyro, Motor& motorL, Motor& motorR)
:
mrNxt(nxt),
mrGyro(gyro),
mrMotorL(motorL),
mrMotorR(motorR),
mPwmL(0),
mPwmR(0)
{
	this->reset();
}

//=============================================================================
// Reset NXTway-GS
void NXTway_GS::reset(S16 offset)
{
	this->stop();
	balance_init();
	this->setGyroOffset(offset);
}

//=============================================================================
// Set gyro sensor offset value
void NXTway_GS::setGyroOffset(S16 offset)
{
	mGyroOffset = offset;
}

//=============================================================================
// Calibrate gyro sensor offset value dynamically
S16 NXTway_GS::calGyroOffset(void)
{
	U32 calGyroOffset = 0;
	SINT numOfAvg = 0;
	while (numOfAvg < 100) // it takes approximately 4*100 = 400msec
	{
		calGyroOffset += mrGyro.get();
		numOfAvg++;
		U32 tic = systick_get_ms();
		while (systick_get_ms() < 4 + tic); // wait for 4msec
	}
	return static_cast<S16>(calGyroOffset/numOfAvg);
}

//=============================================================================
// Get motor PWM values to be set
VectorT<S8> NXTway_GS::getPWM(void) const
{
	return VectorT<S8>(mPwmL, mPwmR);
}

//=============================================================================
// Get calculated motor PWM values
VectorT<S8> NXTway_GS::calcPWM(VectorT<S16> cmd) const
{
	VectorT<S8> pwm;
	balance_control(
		static_cast<F32>(cmd.mX),
		static_cast<F32>(cmd.mY),
		static_cast<F32>(mrGyro.get()),
		static_cast<F32>(mGyroOffset),
		static_cast<F32>(mrMotorL.getCount()),
		static_cast<F32>(mrMotorR.getCount()),
		static_cast<F32>(mrNxt.getBattMv()),
		&pwm.mX,
		&pwm.mY);
	return pwm;
}

//=============================================================================
// Drive NXTway-GS by driver
void NXTway_GS::drive(Driver* driver)
{
	this->drive(driver->getCommand());
}

//=============================================================================
// Drive NXTway-GS by driver command
void NXTway_GS::drive(VectorT<S16> cmd)
{
	VectorT<S8> pwm = calcPWM(cmd);
	mPwmL = pwm.mX;
	mPwmR = pwm.mY;
	mrMotorL.setPWM(mPwmL);
	mrMotorR.setPWM(mPwmR);
}

//=============================================================================
// Stop the wheel motors and reset the motor encoders to zero
void NXTway_GS::stop(void)
{
	mPwmL = mPwmR = 0;
	mrMotorL.reset();
	mrMotorR.reset();
}


