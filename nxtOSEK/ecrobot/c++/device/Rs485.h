//
// Rs485.h
//
// Copyright 2010 by Takashi Chikamasa, Simone Casale Brunet, Jon C. Martin and Robert W. Kramer
//

#ifndef RS485_H_
#define RS485_H_


extern "C"
{
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * RS485 communication class. NXT sensor port 4 should be used for RS485 communication.<BR>
 * Default configrations:<BR>
 * 921600 [bps]<BR>
 * Asynchronous mode<BR>
 * 8 bits character length<BR>
 * 1 stop bit<BR>
 * No parity check
 */
class Rs485
{
public:
	/**
	 * Maximum length of data in byte for send/receive.
	 */
	static const U32 MAX_RS485_DATA_LENGTH = 64;

	/**
	 * LEGO default baud rate [bps].
	 */
	static const U32 LEGO_DEFAULT_BAUD_RATE = 921600;

	/**
	 * Constructor.
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.
	 * When the object is destructed while the system is shut down, RS485 is disabled automatically.
	 * @param baudRate RS485 baud rate [bps]
	 * @return -
	 */
	Rs485(U32 baudRate = LEGO_DEFAULT_BAUD_RATE);

	/**
	 * Destructor (disable RS485).
	 * @param -
	 * @return -
	 */
	~Rs485(void);

	/**
	 * Send data.
	 * @param data Data to be sent
	 * @param offset Offset of data to be sent
	 * @param length Length of data to be sent
	 * @return Length of sent data
	 */
	U32 send(U8* data, U32 offset, U32 length);

	/**
	 * Receive data.
	 * @param data Data to be received
	 * @param offset Offset of data to be received
	 * @param length Length of data to be received
	 * @return Length of received data
	 */
	U32 receive(U8* data, U32 offset, U32 length) const;
};
}

#endif
