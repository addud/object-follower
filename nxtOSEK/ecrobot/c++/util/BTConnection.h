//
// BTConnection.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef BTCONNECTION_H_
#define BTCONNECTION_H_

#include "Bluetooth.h"
#include "Lcd.h"
#include "Nxt.h"

extern "C"
{
	#include "ecrobot_interface.h"
};

namespace ecrobot
{
/**
 * Bluetooth connection helper class.
 */
class BTConnection
{
public:
	/**
	 * Constructor.
	 * @param bt Reference of a Bluetooth object.
	 * @param lcd Reference of a LCD object.
	 * @param nxt Reference of a NXT object.
	 * @return -
	 */
	BTConnection(Bluetooth&bt, Lcd& lcd, Nxt& nxt): mrBt(bt), mrLcd(lcd), mrNxt(nxt) {}

	/**
	 * Establish Bluetooth connection as a slave device and display the status in the LCD.
	 * Note that the connection process can be canceled by keep pushing ENTR button on the NXT for longer than 0.5sec.
	 * @param passkey Bluetooth passkey (up to 16 characters. I.e. "1234")
	 * @param devname Bluetooth user freindly device name (optional parameter. e.g. "NXT")
	 * @return 1(connected)/0(canceled)/-1(failed)
	 */
	SINT connect(const CHAR* passkey, const CHAR* devname = 0);

	/**
	 * Establish Bluetooth connection as a master device and display the status in the LCD.
	 * Note that the connection process can be canceled by keep pushing ENTR button on the NXT for longer than 0.5sec.
	 * @param passkey Bluetooth passkey (up to 16 characters. I.e. "1234")
	 * @param address Bluetooth Device Address to be connected (7bytes hex array data)
	 * @return 1(connected)/0(canceled)/-1(failed)
	 */
	SINT connect(const CHAR* passkey, const U8 address[7]);

private:
	Bluetooth &mrBt;
	Lcd& mrLcd;
	Nxt& mrNxt;
};
}

#endif /* BTCONNECTION_H_ */
