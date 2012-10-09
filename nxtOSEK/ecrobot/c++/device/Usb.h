//
// Usb.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef USB_H_
#define USB_H_


extern "C"
{
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * USB communication class.
 */
class Usb
{
public:
	/**
	 * Maximum length of data in byte for send/receive.
	 */
	static const U32 MAX_USB_DATA_LENGTH = 64;

	/**
	 * Constructor.
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.
	 * When the object is destructed while the system is shut down, USB is shut down automatically.
	 * @param -
	 * @return -
	 */
	Usb(void);

	/**
	 * Destructor (shut down USB).
	 * @param -
	 * @return -
	 */
	~Usb(void);

	/**
	 * USB communication handler which must be invoked every 1msec while application is running.
	 * @param -
	 * @return -
	 */
	void commHandler(void);

	/**
	 * Check connection status.
	 * @param -
	 * @return true:connected/false:not connected
	 */
	bool isConnected(void) const;

	/**
	 * Send data to the host device.
	 * @param data Data to be sent
	 * @param offset Offset of data to be sent
	 * @param length Length of data to be sent
	 * @return Length of sent data
	 */
	U32 send(U8* data, U32 offset, U32 length);

	/**
	 * Receive data from the host device.
	 * @param data Data to be received
	 * @param offset Offset of data to be received
	 * @param length Length of data to be received
	 * @return Length of received data
	 */
	U32 receive(U8* data, U32 offset, U32 length) const;

	/**
	 * Close the existing connection.
	 * @param -
	 * @return true:closed/false failed to close
	 */
	bool close(void);
};
}

#endif
