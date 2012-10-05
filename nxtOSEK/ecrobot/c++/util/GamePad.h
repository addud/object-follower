//
// GamePad.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef GAMEPAD_H_
#define GAMEPAD_H_

#include "Bluetooth.h"
#include "Vector.h"

extern "C"
{
	#include "ecrobot_interface.h"
};

namespace ecrobot
{
/**
 * PC HID compliant GamePad controller class for NXT GamePad
 */
class GamePad
{
public:
	/**
	 * Constructor.
	 * @param bt Reference of a Bluetooth object.
	 * @return -
	 */
	GamePad(const Bluetooth& bt);

	/**
	 * Get GamePad command.
	 * @param -
	 * @return Vectorized command\n
	 * VectorT.mX: Left analog input in vertical direction. -100(up) to 100(down)\n
	 * VectorT.mY: Right analog input in horizontal direction. -100(left) to 100(right)
	 */
	VectorT<S8>get(void);

	/**
	 * Check the connection status of GamePad controller.
	 * @param -
	 * @return true:connected/false:not connected
	 */
	bool isConnected(void);

private:
	static const U8 DATA_BUFFER_BYTE_SIZE = 32;

	const Bluetooth& mrBt;
	U8 mRawData[DATA_BUFFER_BYTE_SIZE];
};
}

#endif
