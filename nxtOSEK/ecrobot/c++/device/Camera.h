//
// Camera.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef CAMERA_H_
#define CAMERA_H_

#include "I2c.h"

namespace ecrobot
{
/**
 * Mindsensor Camera device (http://www.mindsensors.com/) class.
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
class Camera
{
public:
	/** Type of rectangle for object being tracked. */
	typedef struct {
		SINT upperLeftX;	/**< Upper left X position of rectangle  */
		SINT upperLeftY;	/**< Upper left Y position of rectangle  */
		SINT lowerRightX;	/**< Lower right X position of rectangle */
		SINT lowerRightY;	/**< Lower right Y position of rectangle */
		SINT width;			/**< Width of rectangle (in X)           */
		SINT height;		/**< Height of rectangle (in Y)          */
	} Rectangle_T;

	// Camera commands according to NXTCam-v2-User-Guide.pdf provided from Mindsensors
	/** Command to sort tracked objects by size */
	static const U8 SORT_OBJ_BY_SIZE = 0x41;
	/** Command to select object tracing mode */
	static const U8 OBJECT_TRACKING = 0x42;
	/** 
	 * Command to write to camera registers.<BR>
	 * According to Mindsensors:<BR>
	 * Use extreme CAUTION when using this command since this can stop your camera
	 * working properly. In case this happens, please power off your NXTCam
	 * and power it on again.
	 */
	static const U8 WRITE_CAM_REG = 0x43;
	/** Command to disable tracking */
	static const U8 DISABLE_TRACKING = 0x44;
	/** Command to enable tracking */
	static const U8 ENABLE_TRACKING = 0x45;
	/** Command to get the color map from camera engine */
	static const U8 GET_COLOR_MAP = 0x47;
	/** Command to read data from the camera engine */
	static const U8 READ_CAM_REG = 0x48;
	/** Command to turn illumination On (Future) */
	static const U8 ILLUMINATION_ON = 0x49;
	/** Command to select line tracking mode */
	static const U8 LINE_TRACKING = 0x4C;
	/** Command to set ADPA mode On */
	static const U8 SET_ADPA_ON = 0x4E;
	/** Command to set ADPA mode Off (default) */
	static const U8 SET_ADPA_OFF = 0x4F;
	/** Command to ping camera engine */
	static const U8 PING_CAMERA_ENGINE = 0x50;
	/** Command to reset camera engine */
	static const U8 RESET_CAMERA_ENGINE = 0x52;
	/** Command to send the color map to camera engine */
	static const U8 SET_COLOR_MAP = 0x53;
	/** Command to turn illumination Off */
	static const U8 ILLUMINATION_OFF = 0x54;
	/** Command to sort tracked objects by color */
	static const U8 SORT_OBJ_BY_COLOR = 0x55;
	/** Command to get camera engine firmware version */
	static const U8 GET_VERSION = 0x56;
	/** Command to not sort tracked objects */
	static const U8 NO_SORTING_OBJ = 0x58;

	/**
	 * Tracking types.
	 */
	enum eTrackingType
	{
		OBJECT = OBJECT_TRACKING,	/**< Select object tracing mode */
		LINE   = LINE_TRACKING		/**< Select Line tracking mode */
	};

	/**
 	 * Tracked objects sorting types.
	 */
	enum eSortType
	{
		SIZE		= SORT_OBJ_BY_SIZE,		/**< Sort tracked objects by size  */
		COLOR		= SORT_OBJ_BY_COLOR, 	/**< Sort tracked objects by color */
		NO_SORTING	= NO_SORTING_OBJ		/**< Do not sort tracked objects   */
	};

	/**
	 * Constructor (activate I2C).
	 * Note:<BR>
	 * This class must be constructed as a global object. Otherwise, a device assertion will be displayed<BR>
	 * in the LCD when the object is constructed as a non global object.<BR>
	 * When the object is destructed while the system is shut down, the device is de-activated automatically.
	 * @param port Camera device connected port
	 * @return -
	 */
	explicit Camera(ePortS port);

	/**
	 * Enable/disable tracking objects.
	 * @param enable: true(enable)/false(disable)
	 * @return -
	 */
	void enableTracking(boolean enable);

	/**
	 * Choose either object or line tracking mode.
	 * @param mode OBJECT/LINE
	 * @return -
	 */
	inline void setTrackingType(eTrackingType mode) { this->sendCommand(static_cast<U8>(mode)); }

	/**
	 * Camera sorts objects it detects according to criteria, either color, size,
	 * or no sorting at all.
	 * @param sortType SIZE/COLOR/NO_SORTING
	 * @return -
	 */
	inline void sortBy(eSortType sortType) { this->sendCommand(static_cast<U8>(sortType)); }

	/**
	 * Get the number of objects being tracked.
	 * @param -
	 * @return Number of objects (0 - 8)
	 */
	inline SINT getNumberOfObjects(void) const { return static_cast<SINT>(mBuffer[0]); }

	/**
	 * Get the color number for a tracked object.
	 * @param id The object number (starting at zero)
	 * @return the color of the object (starting at zero)
	 */
	inline SINT getObjectColor(SINT id) const { return static_cast<SINT>(mBuffer[1 + id * 5]); }

	/**
	 * Get the rectangle containing a tracked object.
	 * @param id The object number (staring at zero)
	 * @param rect Rectangle data
	 */
	void getRectangle(SINT id, Rectangle_T* rect);

	/**
	 * Call regularly to poll the status of the camera device.
	 * @param -
	 * @return The result of update: true(succeded)/false(failed)
	 */
	bool update(void);

	/**
	 * Send a camera command.
	 * @param command single byte camera command
	 * @return The result of update: true(succeded)/false(failed)
	 */
	inline bool sendCommand(U8 command) { return mI2c.send(0x41, &command, 1); }

	/**
	 * Receive raw data from the camera.
	 * @param address I2C address
	 * @param data Data to be received
	 * @param length Length of data to be received
	 * @return The result of receive data: true(succeded)/false(failed)
	 */
	inline bool receive(U32 address, U8* data, U32 length) { return mI2c.receive(address, data, length); }

private:
	static const U8 DATA_BUFFER_BYTE_SIZE = 41;
	I2c mI2c; // composite
	U8  mBuffer[DATA_BUFFER_BYTE_SIZE]; // buffer to receive all data
};
}
#endif
