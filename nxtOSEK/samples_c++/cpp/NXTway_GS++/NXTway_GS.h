//
// NXTway_GS.h
//

#ifndef NXTWAY_GS_H_
#define NXTWAY_GS_H_

#include "Vector.h"
#include "Nxt.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Clock.h"
using namespace ecrobot;

#include "Driver.h"

extern "C"
{
	#include "balancer.h"
};

class NXTway_GS
{
/**
 * A wrapper class of NXTway-GS balancer C API
 */
public:
	/**
	 * Constructor.
	 * @param nxt NXT device object
	 * @param gyro Gyro Sensor device object
	 * @param motorL Motor device object for left wheel
	 * @param motorR Motor device object for right wheel
	 */
	NXTway_GS(const Nxt& nxt, const GyroSensor& gyro, Motor& motorL, Motor& motorR);

	/**
	 * Calibrate the Gyro Sensor offset value dynamically. It takes approximately 400msec.
	 * While calibrating the robot, robot should be held statically to measure the Gyro Sensor value at zero angular velocity.
	 * @return Calibrated Gyro Sensor offset value
	 */
	S16 calGyroOffset(void);

	/**
	 * Get Gyro Sensor offset value in use.
	 * @return Gyro Sensor offset value in use.
	 */
	S16 getGyroOffset(void) { return mGyroOffset; }

	/**
	 * Set Gyro Sensor offset value. Gyro Sensor offset value means the sensor value at angular velocity is equal to zero.
	 * @param offset Gyro Sensor offset value
	 */
	void setGyroOffset(S16 offset);

	/**
	 * Get Motor PWM values to be set for motors.
	 * @return motor pwm values (mX:motor pwm for left wheel/mY:motor pwm for right wheel)
	 */
	VectorT<S8> getPWM(void) const;

	/**
	 * Get Motor PWM values calculated by NXTway-GS balancer. Inside of this API, NXTway-GS balancer is invoked to calculate the PWM values,
	 * but the PWM values are not set to the motors. Thus the calculated PWM values should be set to the motors manually.
	 * Note that this API might be useful to enhance the NXTway-GS control in conjunction with the NXTway-GS balancer.
	 * @param cmd cmd.mX:Foward command/cmd.mY:Turn command
	 * @return motor pwm values (mX:motor pwm for left wheel/mY:motor pwm for right wheel)
	 */
	VectorT<S8> calcPWM(VectorT<S16> cmd) const;

	/**
	 * Reset NXTway-GS. (turn off the motors, reset motor encoders to zero and initialize NXTway-GS balancer)
	 * @param offset Gyro Sensor offset value (optional)
	 */
	void reset(S16 offset=GyroSensor::DEFAULT_OFFSET);

	/**
	 * Drive NXTway-GS by driver.
	 * @param driver robot driver object derived from Driver class
	 */
	void drive(Driver* driver);

	/**
	 * Drive NXTway-GS by command.
	 * @param cmd Robot control command (cmd.mX:forward, cmd.mY:turn)
	 */
	void drive(VectorT<S16> cmd);

	/**
	 * Stop NXTway-GS. (turn off the motors and reset the motor encoders to zero)
	 */
	void stop(void);

private:
	const Nxt& mrNxt;
	const GyroSensor& mrGyro;
	Motor& mrMotorL;
	Motor& mrMotorR;
	U16 mGyroOffset;
	S8 mPwmL, mPwmR;
};

#endif

