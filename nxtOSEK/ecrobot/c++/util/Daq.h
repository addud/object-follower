//
// Daq.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef DAQ_H_
#define DAQ_H_

#include "Bluetooth.h"

extern "C"
{
	#include "ecrobot_interface.h"
};

namespace ecrobot
{
/**
 * Data acquistion class for NXT GamePad data logging
 */
class Daq
{
public:
	/**
	 * Constructor.
	 * @param bt Reference of a Bluetooth object.
	 * @return -
	 */
	Daq(Bluetooth& bt);

	/**
	 * Send data to NXT GamePad (almost equivalent to ecrobot_bt_data_logger).
	 * @param dataS08 Data to be saved to "Data1" and "Data2" column in a csv file.
	 * @param dataS32 Data to be saved to "I2C" column in a csv file.<BR>
	 * <BR>
	 * Byte frame:&nbsp;&nbsp; CSV column name:&nbsp;&nbsp; Data<BR>
	 * byte00-03:&nbsp;&nbsp; Time:&nbsp;&nbsp; System clock in msec<BR>
	 * byte04:&nbsp;&nbsp; Data1:&nbsp;&nbsp; dataS08[0]<BR>
	 * byte05:&nbsp;&nbsp; Data2:&nbsp;&nbsp; dataS08[1]<BR>
	 * byte06-07:&nbsp;&nbsp; Battery:&nbsp;&nbsp; Battery voltage in mV<BR>
	 * byte08-11:&nbsp;&nbsp; Motor Rev A:&nbsp;&nbsp; Motor count at Port A<BR>
	 * byte12-15:&nbsp;&nbsp; Motor Rev B:&nbsp;&nbsp; Motor count at Port B<BR>
	 * byte16-19:&nbsp;&nbsp; Motor Rev C:&nbsp;&nbsp; Motor count at Port C<BR>
	 * byte20-21:&nbsp;&nbsp; ADC S1:&nbsp;&nbsp; A/D raw value at Port S1<BR>
	 * byte22-23:&nbsp;&nbsp; ADC S2:&nbsp;&nbsp; A/D raw value at Port S2<BR>
	 * byte24-25:&nbsp;&nbsp; ADC S3:&nbsp;&nbsp; A/D raw value at Port S3<BR>
	 * byte26-27:&nbsp;&nbsp; ADC S4:&nbsp;&nbsp; A/D raw value at Port S4<BR>
	 * byte28-31:&nbsp;&nbsp; I2C:&nbsp;&nbsp; dataS32<BR>
	 * @return -
	 */
	void send(S8 dataS08[2], S32 dataS32);

	/**
	 * Send data to NXT GamePad.
	 * @param dataS08 Data to be saved to "Data1" and "Data2" column in a csv file.
	 * @param dataU16 Data to be saved to "Battery" column in a csv file.
	 * @param dataS16 Data to be saved to "ADC S1/ADC S2/ADC S3/ADC S4" column in a csv file.
	 * @param dataS32 Data to be saved to "Motor Rev A/Motor Rev B/Motor Rev C/I2C" column in a csv file.<BR>
	 * <BR>
	 * Byte frame:&nbsp;&nbsp; CSV column name:&nbsp;&nbsp; Data<BR>
	 * byte00-03:&nbsp;&nbsp; Time:&nbsp;&nbsp; System clock in msec<BR>
	 * byte04:&nbsp;&nbsp; Data1:&nbsp;&nbsp; dataS08[0]<BR>
	 * byte05:&nbsp;&nbsp; Data2:&nbsp;&nbsp; dataS08[1]<BR>
	 * byte06-07:&nbsp;&nbsp; Battery:&nbsp;&nbsp; dataU16<BR>
	 * byte08-11:&nbsp;&nbsp; Motor Rev A:&nbsp;&nbsp; dataS32[0]<BR>
	 * byte12-15:&nbsp;&nbsp; Motor Rev B:&nbsp;&nbsp; dataS32[1]<BR>
	 * byte16-19:&nbsp;&nbsp; Motor Rev C:&nbsp;&nbsp; dataS32[2]<BR>
	 * byte20-21:&nbsp;&nbsp; ADC S1:&nbsp;&nbsp; dataS16[0]<BR>
	 * byte22-23:&nbsp;&nbsp; ADC S2:&nbsp;&nbsp; dataS16[1]<BR>
	 * byte24-25:&nbsp;&nbsp; ADC S3:&nbsp;&nbsp; dataS16[2]<BR>
	 * byte26-27:&nbsp;&nbsp; ADC S4:&nbsp;&nbsp; dataS16[3]<BR>
	 * byte28-31:&nbsp;&nbsp; I2C:&nbsp;&nbsp; dataS32[3]<BR>
	 * @return -
	 */
	void send(S8 dataS08[2], U16 dataU16, S16 dataS16[4], S32 dataS32[4]);

private:
	Bluetooth& mrBt;	
};
}

#endif
