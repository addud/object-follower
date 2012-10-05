/*****************************************************************************
 * FILE: ecrobot_HiTechnic.c
 *
 * COPYRIGHT 2008 Takashi Chikamasa <takashic@cybernet.co.jp>
 *
 * <About leJOS NXJ>
 *  leJOS NXJ is a full firmware replacement of LEGO Mindstorms NXT and 
 *  designed for Java programming environment for the NXT 
 *  ( For more detailed information, please see: http://lejos.sourceforge.net/ )
 *  In the leJOS NXJ distribution, C source files for NXT platform layer is also
 *  included besides with the Java VM. The platform C source code is well
 *  structured, comprehensive, and achieved higher performance than the LEGO's
 *  one. Therefore, leJOS NXJ (platform) is also the best GCC based C/C++  
 *  development platform for NXT.
 *
 *  The contents of this file are subject to the Mozilla Public License
 *  Version 1.0 (the "License"); you may not use this file except in
 *  compliance with the License. You may obtain a copy of the License at
 *  http://www.mozilla.org/MPL/
 *
 *  Software distributed under the License is distributed on an "AS IS"
 *  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *  License for the specific language governing rights and limitations
 *  under the License.
 *
 *  The Original Code is TinyVM code, first released March 6, 2000,
 *  later released as leJOS on September 23, 2000.
 *
 *  The Initial Developer of the Original Code is Jose H. Solorzano.
 *
 *  Contributor(s): see leJOS NXJ ACKNOWLEDGEMENTS .
 *
 *
 * <About TOPPERS OSEK>
 *  TOPPERS OSEK is an open source OSEK kernel and developed by TOPPERS project.
 *  TOPPERS(Toyohashi OPen Platform for Embedded Real-time Systems) has been managed 
 *  by a Non Profit Organization founded in Sep. 2003 and has been led by Professor
 *  Hiroaki Takada of Nagoya University in Japan. 
 *
 *  TOPPERS OSEK program is covered by the TOPPERS License as published
 *  by the TOPPERS PROJECT (http://www.toppers.jp/en/index.html).
 *
 *****************************************************************************/
#include "ecrobot_interface.h"


/*==============================================================================
 * NXT HiTechnic Gyro Sensor API
 *=============================================================================*/

/**
 * get HiTechnic Gyro Sensor raw A/D data
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @return: A/D raw data(0 to 1023)
 */
U16 ecrobot_get_gyro_sensor(U8 port_id)
{
	return (U16)sensor_adc(port_id);
}

/*==============================================================================
 * NXT HiTechnic Acceleration Sensor API
 *=============================================================================*/

/**
 * init a NXT port for I2C device(Acceleration Sensor)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_init_accel_sensor(U8 port_id)
{
	ecrobot_init_i2c(port_id, LOWSPEED);
}

/**
 * get HiTechnic Acceleration Sensor data ([x,y,z] axes acceleration)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param buf: buffer to return the x/y/z axes accel data
 */
void ecrobot_get_accel_sensor(U8 port_id, S16 buf[3])
{
	 SINT i;
	  /* support for multiple accel sensors in a NXT */
	 static U8 data[4][6] = {{0}};

	for (i=0; i<3; i++)
	{
		buf[i] = (S16)data[port_id][i];
		if (buf[i] > 127)
		{
			buf[i] -= 256;
		}
		buf[i] = (S16)((buf[i] << 2) | (data[port_id][i+3] & 0x03));
	}
	// Data representation from the sensor, per Hi-Technic's documentation:
	//
	// data[0]: X axis upper 8 bits
	// data[1]: Y axis upper 8 bits
	// data[2]: Z axis upper 8 bits
	// data[3]: X axis lower 2 bits
	// data[4]: Y axis lower 2 bits
	// data[5]: Z axis lower 2 bits
	if (i2c_busy(port_id) == 0)
	{
	   /* i2c_start_transaction just triggers an I2C transaction,
		* actual data transaction between ARM7 and an Acceleration
		* Sensor is done by an ISR after this, so there is one execution cycle
		* delay for consistent data acquistion
		*/
		i2c_start_transaction(port_id,1,0x42,1,&data[port_id][0],6,0);
	}
}

/**
 * terminate a NXT port for I2C device(Acceleration Sensor)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_term_accel_sensor(U8 port_id)
{
	i2c_disable(port_id);
}

/*==============================================================================
 * NXT HiTechnic IR Seeker API
 *
 * Note that IR Seeker API is developed by 
 * Nathan Bahr Sr. Electrical Engineer, Milwaukee School of Engineering (bahrn@msoe.edu)
 *=============================================================================*/

/**
 * init a NXT port for I2C device(IR Seeker)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_init_ir_seeker(U8 port_id)
{
	ecrobot_init_i2c(port_id, LOWSPEED);
}

/**
 * get HiTechnic IR Seeker data (Direction and Five Intensity Vectors)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param buf: buffer to return the direction and five intesity vector data
 */
void ecrobot_get_ir_seeker(U8 port_id, S8 buf[6])
{
	 SINT i;
	  /* support for multiple IR Seeker in a NXT */
	 static U8 data[4][6] = {{0}};

	for (i=0; i<6; i++)
	{
		buf[i] = (S8)data[port_id][i];
	}
	// Data representation from the sensor, per Hi-Technic's documentation:
	//
	// data[0]: Direction  8 bits
	// data[1]: Intensity1 8 bits
	// data[2]: Intensity2 8 bits
	// data[3]: Intensity3 8 bits
	// data[4]: Intensity4 8 bits
	// data[5]: Intensity5 8 bits
	if (i2c_busy(port_id) == 0)
	{
	   /* i2c_start_transaction just triggers an I2C transaction,
		* actual data transaction between ARM7 and an Infrared
		* Sensor is done by an ISR after this, so there is one execution cycle
		* delay for consistent data acquistion
		*/
		i2c_start_transaction(port_id,1,0x42,1,&data[port_id][0],6,0);
	}
}

/**
 * terminate a NXT port for I2C device(IR Seeker)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_term_ir_seeker(U8 port_id)
{
	i2c_disable(port_id);
}

/*==============================================================================
 * NXT HiTechnic Color Sensor API
 *=============================================================================*/

/**
 * init a NXT port for I2C device(Color Sensor)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_init_color_sensor(U8 port_id)
{
	ecrobot_init_i2c(port_id, LOWSPEED);
}

/**
 * calibrate the Color Sensor
 *
 * Puts the sensor into white balance calibration mode. For best results
 * the sensor should be pointed at a diffuse white surface at a distance
 * of approximately 15mm before calling this method. After a fraction of
 * a second the sensor lights will flash and the calibration is done. When
 * calibrated, the sensor keeps this information in non-volatile memory.
 *
 * Puts the sensor into black/ambient level calibration mode. For best
 * results the sensor should be pointed in a direction with no obstacles
 * for 50cm or so. This reading the sensor will use as a base level for
 * other readings. After a fraction of a second the sensor lights will
 * flash and the calibration is done. When calibrated, the sensor keeps
 * this information in non-volatile memory.
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param mode: calibration mode (CAL_WHITE/CAL_BLACK)
 * @return: 1(succeeded)/0(failed)
 */
U8 ecrobot_cal_color_sensor(U8 port_id, U8 mode)
{
	U8 cmd = mode;

	if (ecrobot_wait_i2c_ready(port_id, 50) == 0) return 0;
	i2c_start_transaction(port_id,1,0x41,1,&cmd,1,1);
	if (ecrobot_wait_i2c_ready(port_id, 50) == 0) return 0;
	
	return 1;
}

/**
 * get HiTechnic Color Sensor data ([r,g,b] raw color data)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param buf: buffer to return the r/g/b raw color data
 */
void ecrobot_get_color_sensor(U8 port_id, S16 buf[3])
{
	/* support for multiple color sensors in a NXT */
	static U8 data[4][14] = {{0}};

	// Data representation from the sensor, per Hi-Technic's documentation:
	//
	// data[0]: color number
	// data[1]: red saturation
	// data[2]: green saturation
	// data[3]: blue saturation
	// data[4]: raw red upper 2 bits
	// data[5]: raw red lower 8 bits
	// data[6]: raw green upper 2 bits
	// data[7]: raw green lower 8 bits
	// data[8]: raw blue upper 2 bits
	// data[9]: raw blue lower 8 bits
	// data[10]: color index (2 bits per r/g/b)
	// data[11]: normalized red
	// data[12]: normalized green
	// data[13]: normalized blue
	buf[0] = (S16)(((data[port_id][4] << 8) & 0x300) | data[port_id][5]);
	buf[1] = (S16)(((data[port_id][6] << 8) & 0x300) | data[port_id][7]);
	buf[2] = (S16)(((data[port_id][8] << 8) & 0x300) | data[port_id][9]);

	if (i2c_busy(port_id) == 0)
	{
	   /* i2c_start_transaction just triggers an I2C transaction,
		* actual data transaction between ARM7 and a Color
		* Sensor is done by an ISR after this, so there is one execution cycle
		* delay for consistent data acquistion
		*/
		i2c_start_transaction(port_id,1,0x42,1,data[port_id],14,0);
	}
}

/**
 * terminate a NXT port for I2C device(Color Sensor)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_term_color_sensor(U8 port_id)
{
	i2c_disable(port_id);
}

/*==============================================================================
 * NXT HiTechnic Compass Sensor API
 *=============================================================================*/

/**
 * init a NXT port for I2C device(Compass Sensor)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_init_compass_sensor(U8 port_id)
{
	ecrobot_init_i2c(port_id, LOWSPEED);
}

/**
 * calibrate a Compass Sensor
 * Note that this implementation is not smart as C++ version and
 * it has some waits in the function.
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @return: 1(succeeded)/0(failed)
 */
U8 ecrobot_cal_compass_sensor(U8 port_id)
{
	U8 cmd;

	if (ecrobot_wait_i2c_ready(port_id, 50) == 0) return 0;

	cmd = 0x43; /* start calibration command */
	i2c_start_transaction(port_id,1,0x41,1,&cmd,1,1);
	if (ecrobot_wait_i2c_ready(port_id, 50) == 0) return 0;

	cmd = 0x00; /* end calibration command */
	i2c_start_transaction(port_id,1,0x41,1,&cmd,1,1);
	if (ecrobot_wait_i2c_ready(port_id, 50) == 0) return 0;

	// now read back the byte, if it's 0 then calibration succeeded,
	// otherwise it'll be a 2 and it failed.
	i2c_start_transaction(port_id,1,0x41,1,&cmd,1,0);
	if (ecrobot_wait_i2c_ready(port_id, 50) == 0) return 0;

	return !cmd;
}

/**
 * get HiTechnic Compass Sensor data
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @return: heading data
 */
S16 ecrobot_get_compass_sensor(U8 port_id)
{
	/* support for multiple compass sensors in a NXT */
	static U8 data[4][5] = {{0}};

	// Data representation from the sensor, per Hi-Technic's documentation:
	//
	// data[0]: mode control
	// data[1]: two degree heading
	// data[2]: one degree heading
	// data[3]: heading low bytes
	// data[4]: heading high bytes
	S16 buf = ((S16)data[port_id][3] & 0xff) | (((S16)data[port_id][4] << 8) & 0xff00);

	if (i2c_busy(port_id) == 0)
	{
	   /* i2c_start_transaction just triggers an I2C transaction,
		* actual data transaction between ARM7 and an Acceleration
		* Sensor is done by an ISR after this, so there is one execution cycle
		* delay for consistent data acquistion
		*/
		i2c_start_transaction(port_id,1,0x41,1,&data[port_id][0],5,0);
	}

	return buf;
}

/**
 * terminate a NXT port for I2C device(Compass Sensor)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_term_compass_sensor(U8 port_id)
{
	i2c_disable(port_id);
}

/*==============================================================================
 * NXT HiTechnic Prototype Sensor API
 *=============================================================================*/

static U8 digitalDir;

static void set_sample_rate(U8 port_id, U8 rate)
{
	if (rate < 4)
	{
		rate = 4;
	}
	
	if (rate > 100)
	{
		rate = 100;
	}

	(void)ecrobot_wait_i2c_ready(port_id, 50); // wait for 50msec until I2C port gets ready
	i2c_start_transaction(port_id,1,0x4f,1,&rate,1,1);
}

static void set_digital_ports(U8 port_id, U8 dir)
{
	digitalDir = (dir & HTPS_DIGTAL_PORTS); // mask off the configured direction of digital I/O ports

	(void)ecrobot_wait_i2c_ready(port_id, 50);  // wait for 50msec until I2C port gets ready
	i2c_start_transaction(port_id,1,0x4e,1,&digitalDir,1,1);
}

/**
 * init a NXT port for I2C device(Prototype Sensor)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param rate: sampling rate (forcing into the range of 4 - 100 msec)
 * @param dir: direction of the six digital I/O ports
 *              a 1 bit in position i (0 <= i <= 5) indicates that port i is configured for output.
 *              a 0 bit indicates the port is configured for input.
 */
void ecrobot_init_prototype_sensor(U8 port_id, U8 rate, U8 dir)
{
	ecrobot_init_i2c(port_id, LOWSPEED);

	set_sample_rate(port_id, rate);

	set_digital_ports(port_id, dir);
}

/**
 * get HiTechnic Prototype analog sensor data
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param buf: analog 5 channnel data buffer
 */
void ecrobot_get_prototype_analog_sensor(U8 port_id, S16 buf[5])
{
	SINT i;
	/* support for multiple prototype sensors in a NXT */
	static U8 data[4][10] = {{0}};

	// Data representation from the sensor, per Hi-Technic's documentation:
	//
	// data[0]: A0 upper 8 bits
	// data[1]: A0 lower 2 bits
	// data[2]: A1 upper 8 bits
	// data[3]: A1 lower 2 bits
	// data[4]: A2 upper 8 bits
	// data[5]: A2 lower 2 bits
	// data[6]: A3 upper 8 bits
	// data[7]: A3 lower 2 bits
	// data[8]: A4 upper 8 bits
	// data[9]: A4 lower 2 bits
	for (i=0;i<5;i++)
	{
		buf[i] = (S16)((data[port_id][2*i] << 2) | (data[port_id][2*i+1] & 0x03));
	}

	if (i2c_busy(port_id) == 0)
	{
	   /* i2c_start_transaction just triggers an I2C transaction,
		* actual data transaction between ARM7 and an Acceleration
		* Sensor is done by an ISR after this, so there is one execution cycle
		* delay for consistent data acquistion
		*/
		i2c_start_transaction(port_id,1,0x42,1,data[port_id],10,0);
	}
}

/**
 * get HiTechnic Prototype digital sensor data
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @return digital data (0 - 5 bits)
 */
U8 ecrobot_get_prototype_digital_sensor(U8 port_id)
{
	static U8 data[4] = {0};

	U8 buf = (data[port_id] & ~digitalDir) & HTPS_DIGTAL_PORTS;

	if (i2c_busy(port_id) == 0)
	{
	   /* i2c_start_transaction just triggers an I2C transaction,
		* actual data transaction between ARM7 and an Acceleration
		* Sensor is done by an ISR after this, so there is one execution cycle
		* delay for consistent data acquistion
		*/
		i2c_start_transaction(port_id,1,0x4c,1,&data[port_id],1,0);
	}

	return buf;
}

void ecrobot_get_prototype_sensor(U8 port_id, S16 a_buf[5], U8 d_buf[6])
{
	SINT i;
	/* support for multiple prototype sensors in a NXT */
	static U8 data[4][11] = {{0}};

	if (digitalDir != 0x00) return; // all digital port should be configured as inputs
	
	// Data representation from the sensor, per Hi-Technic's documentation:
	//
	// data[0]:  A0 upper 8 bits
	// data[1]:  A0 lower 2 bits
	// data[2]:  A1 upper 8 bits
	// data[3]:  A1 lower 2 bits
	// data[4]:  A2 upper 8 bits
	// data[5]:  A2 lower 2 bits
	// data[6]:  A3 upper 8 bits
	// data[7]:  A3 lower 2 bits
	// data[8]:  A4 upper 8 bits
	// data[9]:  A4 lower 2 bits
	// data[10]: D0 0-5 bits
	for (i=0;i<5;i++)
	{
		a_buf[i] = (S16)((data[port_id][2*i] << 2) | (data[port_id][2*i+1] & 0x03));
	}

	for (i=0;i<6;i++)
	{
		d_buf[i] = 0x00;
		if (data[port_id][10] & (0x01 << i))
		{
			d_buf[i] = 0x01;
		}
	}

	if (i2c_busy(port_id) == 0)
	{
	   /* i2c_start_transaction just triggers an I2C transaction,
		* actual data transaction between ARM7 and an Acceleration
		* Sensor is done by an ISR after this, so there is one execution cycle
		* delay for consistent data acquistion
		*/
		i2c_start_transaction(port_id,1,0x42,1,data[port_id],11,0);
	}
}

/**
 * send HiTechnic Prototype digital sensor data
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param data: digital data (0 - 5 bits)
 */
void ecrobot_send_prototype_digital_sensor(U8 port_id, U8 data)
{
	if (i2c_busy(port_id) == 0)
	{
		data &= digitalDir; // mask off input bits
		i2c_start_transaction(port_id,1,0x4d,1,&data,1,1);
	}
}

/**
 * terminate a NXT port for I2C device(Prototype Sensor)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_term_prototype_sensor(U8 port_id)
{
	i2c_disable(port_id);
}

/*==============================================================================
 * NXT Tetrix HiTechnic Controllers
 *=============================================================================*/

/**
 * init a NXT port for I2C Tetrix Controllers (in daisy chain)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */

void ecrobot_init_tetrix(U8 port_id)
{
ecrobot_init_i2c( port_id, LOWSPEED ) ;
} 


/**
 * Set Tetrix Motor mode and speed 
 *
 * @param port_is: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2c_address: TETRIX_ADDRESS_1/TETRIX_ADDRESS_2/TETRIX_ADDRESS_3/TETRIX_ADDRESS_4. Address (according to its position) of the dc motor controller in the daisy chain.
 * @param mode_motor1 : TETRIX_MODE_PWM(default)/TETRIX_MODE_PWM_REV (inverse direction of rotation of the motor). Other modes using Tetrix Encoder for speed or position regulation not yet supported (scheduled for end of 1st 2012 quater).
 * @param mode_motor2 : TETRIX_MODE_PWM(default)/TETRIX_MODE_PWM_REV (inverse direction of rotation of the motor).
 * @pwm_motor1: TETRIX_MOTOR_BRAKE (value 0)/TETRIX_MOTOR_FLOAT (value -128) or value from -100 to 100 for the speed. Negative value is reverse direction.
 * @pwm_motor2: TETRIX_MOTOR_BRAKE (value 0)/TETRIX_MOTOR_FLOAT (value -128) or value from -100 to 100 for the speed.
 */

void ecrobot_tetrix_motors(U8 port_id, U32 i2c_address, U8 mode_motor1, U8 mode_motor2, S8 pwm_motor1, S8 pwm_motor2)
{
	static U8 buf[4];  //do not work without static
	buf[0]=mode_motor1;
	buf[1]=pwm_motor1;
	buf[2]=pwm_motor2;
	buf[3]=mode_motor2;

	ecrobot_send_i2c(port_id, i2c_address, 0x44, buf, 4);

}

/**
 * Set Tetrix Servos positions and step time.
 *
 * @param port_is: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2c_address: TETRIX_ADDRESS_1/TETRIX_ADDRESS_2/TETRIX_ADDRESS_3/TETRIX_ADDRESS_4. Address (according to its position) of the servo controller in the daisy chain.
 * @param step_time : TETRIX_SERVO_NO_STEP_TIME (value 0, all servos run at full speed). Or a value from 1 to 15 to set the step time of the servo that is the further from its position, then others servos will slow down so that all reach their position at the same time.
 * @param  pwm : TETRIX_SERVO_OFF (turn off servos,float)/TETRIS_SERVO_ON_NO_TIMEOUT (ON and disable 10 second watchdog)/ TETRIX_SERVO_ON 0x00 (default, ON and restart 10 second watchdog timer)  
 * @param servo1 : position of servomotor 1 (value from 0-255). Be careful that servos may hit their mechanical limit at each end of this range, reulting in high current consumption.  
 * @param servo2 : ...
 */

void ecrobot_tetrix_servos(U8 port_id, U32 i2c_address, U8 step_time, U8 pwm, U8 servo1, U8 servo2, U8 servo3, U8 servo4, U8 servo5, U8 servo6)
{
	static U8 buf[8];  //do not work without static
	buf[0]=step_time;
	buf[1]=servo1;
	buf[2]=servo2;
	buf[3]=servo3;
	buf[4]=servo4;
	buf[5]=servo5;
	buf[6]=servo6;
	buf[7]=pwm;
	ecrobot_send_i2c(port_id, i2c_address, 0x41, buf, 8);

}


/**
 * Get battery voltage of the Tetrix battery pack
 *
 * @param port_is: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2c_address: TETRIX_ADDRESS_1/TETRIX_ADDRESS_2/TETRIX_ADDRESS_3/TETRIX_ADDRESS_4. Address (according to its position) of one DC motor controller in the daisy chain.
 * @return: Tetrix battery pack Voltage in millivolt
 */
U32 ecrobot_tetrix_battery(U8 port_id, U32 i2c_address)
{
	static U8 buf[2];
	U32 millivolt;

	ecrobot_read_i2c(port_id, i2c_address, 0x54, buf, 2);

	millivolt= buf[0] <<2 ;
	millivolt = millivolt | (buf[1] & 0x03);

	return millivolt*20 ; 
}


/**
 * terminate a NXT port for I2C Tetrix Controllers (in daisy chain)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_term_tetrix(U8 port_id)
{
ecrobot_term_i2c(port_id);
}

