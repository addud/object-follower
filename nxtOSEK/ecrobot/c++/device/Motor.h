//
// Motor.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Port.h"

extern "C"
{
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * NXT Motor class.
 */
class Motor
{
public:
	/**
	 * Maximum PWM value.
	 */
	static const S8 PWM_MAX = 100;
	
	/**
	 * Minimum PWM value.
	 */
	static const S8 PWM_MIN = -100;

	/**
	 * Constructor (set brake by default).
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.
	 * @param port Motor connected port
	 * @param brake true:brake/false:float
	 * @return -
	 */
	explicit Motor(ePortM port, bool brake = true);

	/**
	 * Destructor (stop the motor).
	 * @param -
	 * @return -
	 */
	~Motor(void);

	/**
	 * Stop motor and set motor encoder count to 0.
	 * @param -
	 * @return -
	 */
	inline void reset(void)
	{
		nxt_motor_set_speed(mPort, 0, 1); // need to set brake to stop the motor immidiately
		nxt_motor_set_count(mPort, 0);
	}

	/**
	 * Get motor encoder count.
	 * @param -
	 * @return Motor encoder count in degree.
	 */
	inline S32 getCount(void) const { return nxt_motor_get_count(mPort); }

	/**
	 * Set motor encoder count.
	 * @param count Motor encoder count in degree.
	 * @return -
	 */
	inline void setCount(S32 count) { nxt_motor_set_count(mPort, count); }

	/**
	 * Set motor PWM value.
	 * @param pwm PWM_MAX to PWM_MIN
	 * @return -
	 */
	void setPWM(S8 pwm);

	/**
	 * Set brake.
	 * @param brake true:brake/false:float
	 * @return -
	 */
	void setBrake(bool brake);

protected:
	/**
	 * Get motor connected port.
	 * @param -
	 * @return Motor connected port
	 */
	inline ePortM getPort(void) const { return mPort; }

	/**
	 * Get brake status.
	 * @param -
	 * @return true:brake/false:float
	 */
	inline bool getBrake(void) const { return mBrake; }

	/**
	 * Get current PWM value.
	 * @param -
	 * @return PWM set value
	 */
	inline S8 getPWM(void) const { return mPWM; }

private:
   ePortM mPort;
	bool mBrake;
	S8 mPWM;
};
}

#endif
