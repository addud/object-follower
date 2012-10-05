//
// PSPNx.h
//
// Mindsensor PSPNx wrapper class
//
// 09.28.2008 Jon C. Martin
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef _PSPNX_H
#define _PSPNX_H

#include "I2c.h"
#include "Vector.h"
using namespace ecrobot;

namespace ecrobot
{
/**
 * Mindsensor PSPNx (http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=61) class.
 *
 * [ How to use with TOPPERS/ATK1(OSEK) ]<BR>
 * I2C (derived/compositted) class and Clock class internally use RTOS features.
 * Thus, user needs to implement a C function and RTOS provided events.<BR><BR>
 * + Invoke SleeperMonitor function in user_1msec_isr_type2 hook.<BR>
 * &nbsp;&nbsp;void user_1ms_isr_type2(void)<BR>
 * &nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;SleeperMonitor(); // needed for I2C devices and Clock class<BR>
 * &nbsp;&nbsp;}<BR>
 * <BR>
 * + Define EventSleepI2C and EventSleep Events in user oil file.<BR>
 * &nbsp;&nbsp;EVENT EventSleepI2C<BR>
 * &nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;MASK = AUTO;<BR>
 * &nbsp;&nbsp;};<BR><BR>
 * &nbsp;&nbsp;EVENT EventSleep<BR>
 * &nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;MASK = AUTO;<BR>
 * &nbsp;&nbsp;};<BR><BR>
 * &nbsp;&nbsp;TASK TaskMain<BR>
 * &nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;AUTOSTART = TRUE<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;{<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;APPMODE = appmode1;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;};<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;PRIORITY = 1;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;ACTIVATION = 1;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;SCHEDULE = FULL;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;STACKSIZE = 512;<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;EVENT = EventSleepI2C; <- Here it is<BR>
 * &nbsp;&nbsp;&nbsp;&nbsp;EVENT = EventSleep; <- Here it is<BR>
 * &nbsp;&nbsp;};<BR>
 * <BR>
 * [ How to use with TOPPERS/JSP(ITRON) ]<BR>
 * In case of using this class with TOPPERS/JSP(ITRON), RTOS specific definitions for the class are not needed.
 */
class PSPNx
{
public:
	/**
 	 * PSPNx buttons status mask.
	 */
	enum eButtons
	{
		  SELECT =     1, /**< SELECT button   */
		      LJ =     2, /**< LJ button       */
		      RJ =     4, /**< RJ button       */
		   START =     8, /**< START button    */
		      UP =    16, /**< UP button       */
		   RIGHT =    32, /**< RIGHT button    */
		    DOWN =    64, /**< DOWN button     */
		    LEFT =   128, /**< LEFT button     */
		      L2 =   256, /**< L2 button       */
		      R2 =   512, /**< R2 button       */
		      L1 =  1024, /**< L1 button       */
		      R1 =  2048, /**< R1 button       */
		TRIANGLE =  4096, /**< TRIANGLE button */
		  CIRCLE =  8192, /**< CIRCLE button   */
		   CROSS = 16384, /**< CROSS button    */
		  SQUARE = 32768, /**< SQUARE button   */
	};

	/**
	 * PSPNx default address.
	 */
	static const U8 PSPNx_DEFAULT_ADDRESS = 0x02;

	/**
	 * Size of raw I2C data.
	 */
	static const U8 DATA_BUFFER_BYTE_SIZE = 6;

	/**
	 * Constructor (activate I2C).
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port PSPNx connected port
	 * @param address PSPNx address(currently not used)
	 * @return -
	 */
	explicit PSPNx(ePortS port, U8 address=PSPNx_DEFAULT_ADDRESS);

	//set the pad mode - mutually exclusive
	/**
	 * Set the analog pad mode (analog/digital is mutually exclusive).
	 * @param -
	 * @return -
	 */
	void setAnalog(void);
	/**
	 * Set the digital pad mode (analog/digital is mutually exclusive).
	 * @param -
	 * @return -
	 */
	void setDigital(void);

	//set other modes - ok to combine these
	/**
	 * Set the energize mode.<BR>
	 * @param enable true:enable/false:disable energize mode
	 * @return -
	 */
	void setEnergize(bool enable);
	/**
	 * Set the ADPA mode.<BR>
	 * @param enable true:enable/false:disable ADPA mode
	 * @return -
	 */
	void setADPA(bool enable);

	//call regularly
	/**
	 * Call regularly to poll the status of the PSPNx.<BR>
	 * @param -
	 * @return -
	 */
	void update(void);

	//poll methods for the stick.
	/**
	 * Check the buttons pressed<BR>
	 * @param mask PSPNx buttons status mask
	 * @return true:pressed/false:not pressed
	 */
	bool pressed(eButtons mask) const;
	/**
	 * Check the buttons held.<BR>
	 * @param mask PSPNx buttons status mask
	 * @return true:held/false:not held
	 */
	bool held(eButtons mask) const;
	/**
	 * Check the buttons released.<BR>
	 * @param mask PSPNx buttons status mask
	 * @return true:released/false:not released
	 */
	bool released(eButtons mask) const;

	/**
	 * Get the left stick inputs.
	 * @param -
	 * @return Left stick inputs<BR>
	 * VectorT.mX: Left stick input in X axis<BR>
	 * VectorT.mY: Left stick input in Y axis
	 */
	VectorT<S8> getLeftStick(void) const;
	/**
	 * Get the reft stick inputs.
	 * @param -
	 * @return Right stick inputs<BR>
	 * VectorT.mX: Right stick input in X axis<BR>
	 * VectorT.mY: Right stick input in Y axis
	 */
	VectorT<S8> getRightStick(void) const;

	//raw gamepad info
	/**
	 * Get raw I2C data from PSPNx.
	 * @param data
	 */
	void get(U8 data[DATA_BUFFER_BYTE_SIZE]) const;

private:
	enum
	{
		Button_1,
		Button_2,
		LeftStick_X,
		LeftStick_Y,
		RightStick_X,
		RightStick_Y,
	};

	I2c mI2c; // composite

	U8 mAddress;
	U8 mRawData[DATA_BUFFER_BYTE_SIZE];
	U16 mCurrentState;
	U16 mPreviousState;
	
	VectorT<S8> mLeftStick;
	VectorT<S8> mRightStick;
};

}

#endif

