//
// Bluetooth.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_


extern "C"
{
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * Bluetooth communication class.
 *
 * Note:<BR>
 * User specified friendly device name using setFriendlyName seems to be appeared in the Windows<BR>
 * Bluetooth device dialog only when NXT BIOS is used as the firmware (why?).
 */
class Bluetooth
{
public:
	/**
	 * Maximum length of data in byte to send (= 256 bytes).
	 */
	static const U32 MAX_BT_TX_DATA_LENGTH = BT_MAX_TX_BUF_SIZE; // defined in ecrobot_bluetooth.h
	
	/**
	 * Maximum length of data in byte to receive (= 128 bytes).
	 */
	static const U32 MAX_BT_RX_DATA_LENGTH = BT_MAX_RX_BUF_SIZE;  // defined in ecrobot_bluetooth.h

	/**
	 * Constructor.
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.
	 * When the object is destructed while the system is shut down, Bluetooth is closed automatically.
	 * @param -
	 * @return -
	 */
	Bluetooth(void);

	/**
	 * Destructor.
	 * Close the existing connection.
	 * @param -
	 * @return -
	 */
	~Bluetooth(void);

	/**
	 * Wait for a connection as a slave device.
	 * @param passkey Bluetooth passkey (up to 16 characters. I.e. "1234")
	 * @param duration Wait duration in msec (duration = 0 means wait forever)
	 * @return true:connected/false:not connected
	 */
	bool waitForConnection(const CHAR* passkey, U32 duration);

	/**
	 * Wait for a connection as a master device.
	 * @param passkey Bluetooth passkey (up to 16 characters. I.e. "1234")
	 * @param address Bluetooth Device Address to be connected (7bytes hex array data)
	 * @param duration Wait duration in msec (duration = 0 means wait forever)
	 * @return true:connected/false:not connected
	 */
	bool waitForConnection(const CHAR* passkey, const U8 address[7], U32 duration);

	/**
	 * Cancel of waiting for a connection.
	 * This member function must be invoked from the 1msec interrupt hook function (i.e. user_1ms_isr_type2 for nxtOSEK)\n
	 * to cancel of waiting for a connection. Otherwise, it does not work.
	 * @param -
	 * @return -
	 */
	void cancelWaitForConnection(void);

	/**
	 * Get the Bluetooth Device Address of the device.
	 * @param address Bluetooth Device Address (7bytes hex array data)
	 * @return true:succeeded/false:failed
	 */
	bool getDeviceAddress(U8 address[7]) const;

	/**
	 * Get the friendly name of the device.
	 * @param name Friendly name (max. 16 characters)
	 * @return true:succeeded/false:failed
	 */
	bool getFriendlyName(CHAR* name) const;

	/**
	 * Set the friendly name of the device.
	 * While a connection is established, device name can't be changed.
	 * @param name Friendly name (max. 16 characters)
	 * @return true:succeeded/false:failed
	 */
	bool setFriendlyName(const CHAR* name);

	/**
	 * Get connection status.
	 * @param -
	 * @return true:connected/false:not connected
	 */
	bool isConnected(void) const;
	
	/**
	 * Get RSSI (Received Signal Strength Indicator).
	 * @param -
	 * @return RSSI -1 to 255. Higher value means the link quality is better. -1 means Bluetooth is not connected.
	 */
	S16 getRSSI(void);

	/**
	 * Send data to the connected device.
	 * @param data Data buffer to send
	 * @param length Length of data in bytes to be sent.
	 * Note that maximum length of data in bytes is MAX_BT_TX_DATA_LENGTH - 2 bytes
	 * @return Length of sent data in bytes.
	 */
	U32 send(U8* data, U32 length);

	/**
	 * <strong>(RECOMMENDED TO USE)</strong>  Send data to the connected device.
	 * Note that this API sends data as it is. It means that no addtional data (number of data) is added, so it is good to be used for user designed protocol.
	 * @param data Data buffer to send
	 * @param offset Data buffer offset in bytes
	 * @param length Length of data in bytes to be sent.
	 * Note that maximum length of data in bytes is MAX_BT_TX_DATA_LENGTH
	 * @return Length of sent data in bytes
	 */
	U32 send(const void* data, U32 offset, U32 length);

	/**
	 * Receive data from the connected device.
	 * @param data Data to be received
	 * @param length Length of data in bytes to be received
	 * Note that maximum length of data in bytes is MAX_BT_RX_DATA_LENGTH - 2 bytes
	 * @return Length of received data in bytes.
	 */
	U32 receive(U8* data, U32 length) const;

	/**
	 * <strong>(RECOMMENDED TO USE)</strong>  Receive data from the connected device. 
	 * Note that this API receives data as it is. It means that no addtional data (number of data) is added, so it is good to be used for user designed protocol.
	 * @param data Data buffer to receive
	 * @param offset Data buffer offset in bytes
	 * @param length Length of data in bytes to be received.
	 * Note that maximum length of data in bytes is MAX_BT_RX_DATA_LENGTH
	 * @return Length of received data in bytes
	 */
	U32 receive(void* data, U32 offset, U32 length) const;
	
	/**
	 * Reset all settings in the persistent settings in the BlueCore chip.
	 * The BlueCore chip should be restarted (remove the battery) after calling this function.<BR>
	 * Otherwise old values can be floating around the BlueCore chip causing<BR>
	 * unexpected behavior.
	 * @param -
	 * @return -
	 */
	 void setFactorySettings(void);

private:
	bool mIsConnected;
	bool mCancelConnection;
	void close(void);
};
}

#endif
