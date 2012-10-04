//
// Nxt.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef NXT_H_
#define NXT_H_

extern "C"
{
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * NXT intelligent block class.
 */
class Nxt
{
public:
	/**
	 * NXT Button enum.
	 * Note that this enum is kept for backward compatibility. Recommend to use
	 * eNxtButton enum.
	 */
	enum eButton
	{
		RUN_ON = 0x01,                    /**< RUN (right triangle) button is ON   */
		ENTR_ON = 0x02,                   /**< ENTR(orange rectangle) button is ON */
		RUN_ENTR_ON = (RUN_ON | ENTR_ON), /**< RUN and ENTR buttons are ON         */
		BUTTONS_OFF = 0x00,               /**< RUN and ENTR buttons are OFF        */
	};
	
	/**
	 * NXT Button enum.
	 * Note that left triangle and gray colored rectangle buttons on the NXT are reserved for stopping and shutdown application program.
	 * To use these buttons for an application, define NO_RUN_ENTER_STOP_EXIT compile switch macro while compiling the application.   
	 */
	enum eNxtButton
	{
		ORANGE_RECT = 0x01,               /**< Orange colored rectangle button */
		LEFT = 0x02,                      /**< Left triangle button            */
		RIGHT = 0x04,                     /**< Right triangle button           */
		GRAY_RECT = 0x08,                 /**< Gray colored rectangle button   */
	};

	/**
	 * Constructor.
	 * @param -
	 * @return -
	 */
	Nxt(void);

	/**
	 * Get NXT buttons status.
	 * Note that this API is kept for backward compatibility. Recommend to use
	 * getNxtButtons API instead of getButtons API.
	 * @param -
	 * @return Status of RUN/ENTR buttons
	 */
	eButton getButtons(void) const;
	
	/**
	 * Get NXT buttons status.
	 * @param -
	 * @return Status of all buttons on the NXT (true:pressed/false:not pressed)
	 */
	eNxtButton getNxtButtons(void) const;

	/**
	 * Get battery voltage in mV.
	 * @param -
	 * @return Battery voltage in mV
	 */
	S16 getBattMv(void) const;
	
	/**
	 * Shutdown (Power off) the NXT
	 * @param -
	 * @return -
	 */ 
	void shutdown(void);
	
	/**
	 * Restart the running application 
	 * @param -
	 * @return -
	 */ 
	void restart(void);
	
	/**
	 * Execute NXT BIOS.
	 * Note that this API works only when NXT BIOS is used. Otherwise, it does nothing.<BR>
	 * Note that NXT BIOS 1.0.4 or later is required.
	 * @param -
	 * @return -
	 */
	 void execNXTBIOS(void);
};
}

#endif
