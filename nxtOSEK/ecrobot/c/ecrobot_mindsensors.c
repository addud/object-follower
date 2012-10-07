/*****************************************************************************
 * FILE: ecrobot_mindsensors.c
 *
 * Author: Thanh Pham
 *
 *****************************************************************************/
#include "ecrobot_interface.h"

/**
 * init a NXT port for I2C device(NXTMMX)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_MMX_init(U8 port_id)
{
	ecrobot_init_i2c(port_id, LOWSPEED_9V);
}

/**
 * terminate a NXT port for I2C device(NXTMMX)
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 */
void ecrobot_term_MMX(U8 port_id)
{
	ecrobot_term_i2c(port_id);
}

/*
 * set Motor speed
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03 
 * @param motor_number: MMX_Motor_1/MMX_Motor_2/MMX_Motor_Both
 * @param speed: PWM duty ration (-100 to 100)
 * @param mode: float(0)/brake(1)
 */
void ecrobot_set_MMX_speed(U8 port_id, U8 i2caddr, U8 motor_number, S8 speed, U8 mode)
{
	U8 inData = 'S';
	unsigned char cmdA = 0x81; /* speed brake control */
	unsigned char data[4] = {speed, 0, 0, cmdA};
	if(mode == 1) // brake
	{
		cmdA = 0x91;
	}
	if(motor_number == MMX_Motor_Both)
	{
		cmdA &= 0x7f;
	}
	data[3] = cmdA;
	
	if((motor_number & 0x01) != 0)
	{
		ecrobot_send_i2c(port_id, i2caddr, 0x46, data, 4);
		while (i2c_busy(port_id) != 0);
	}
	if((motor_number & 0x02) != 0)
	{
		ecrobot_send_i2c(port_id, i2caddr, 0x4E, data, 4);
		while (i2c_busy(port_id) != 0);
	}	
	if(motor_number == MMX_Motor_Both)
	{
		ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
	}
	while (i2c_busy(port_id) != 0);
}

/*
 * set Motor speed
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03 
 * @param motor_number: MMX_Motor_1/MMX_Motor_2/MMX_Motor_Both
 * @param speed: PWM duty ration (-100 to 100)
 * @param mode: float(0)/brake(1)
 */
void ecrobot_set_MMX_stop(U8 port_id, U8 i2caddr, U8 motor_number, U8 mode)
{
    U8 inData;
	if(mode == 0) // float
	{
		if((motor_number & 0x01) != 0) {
			inData = 'a';
			ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
			while (i2c_busy(port_id) != 0);
		}
		if((motor_number & 0x02) != 0) {
			inData = 'b';
			ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
			while (i2c_busy(port_id) != 0);
		}
		if(motor_number == MMX_Motor_Both){
			inData = 'c';
			ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
		}
	}
	else //brake or brake_hold
	{
		if((motor_number & 0x01) != 0) {
			inData = 'A';
			ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
			while (i2c_busy(port_id) != 0);
		}
		if((motor_number & 0x02) != 0) {
			inData = 'B';
			ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
			while (i2c_busy(port_id) != 0);
		}
		if(motor_number == MMX_Motor_Both) {
			inData = 'C';
			ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
		}
	}
	while (i2c_busy(port_id) != 0);
}
/*
 * set Motor run time
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03
 * @param motor_number: MMX_Motor_1/MMX_Motor_2/MMX_Motor_Both
 * @param speed: PWM duty ration (-100 to 100)
 * @param duration: 1-255 seconds
 * @param mode: float(0)/brake(1)
 */
void ecrobot_set_MMX_time(U8 port_id, U8 i2caddr, U8 motor_number, S8 speed, U8 duration, U8 mode)
{
	U8 inData = 'S';
	unsigned char cmdA = 0xD1; /* speed brake control */
	unsigned char data[4] = {speed, duration, 0, cmdA};
	if(mode == 0) //float
		cmdA &= 0xEF;
	if(motor_number == MMX_Motor_Both)
		cmdA &= 0x7F;
	data[3] = cmdA;
	if((motor_number & 0x01) != 0) {
		ecrobot_send_i2c(port_id, i2caddr, 0x46, data, 4);
		while (i2c_busy(port_id) != 0)
			systick_wait_ms(50);
	}
	if((motor_number & 0x02) != 0) {
		ecrobot_send_i2c(port_id, i2caddr, 0x4E, data, 4);
		while (i2c_busy(port_id) != 0)
			systick_wait_ms(50);
	}
	if(motor_number == MMX_Motor_Both)
		ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
	while (i2c_busy(port_id) != 0)
		systick_wait_ms(50);
}
/*
 * get Servo Motor revolution in degree
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03
 * @param motor_number: MMX_Motor_1/MMX_Motor_2
 * @return: motor revolution in degree 
 */
S32 ecrobot_get_MMX_count(U8 port_id, U8 i2caddr, U8 motor_number)
{
	U8 data[4] = {0, 0, 0, 0};
	S32 count = 0;
	if((motor_number & 0x01) != 0)
		ecrobot_read_i2c(port_id, i2caddr, 0x62, data, 4);
	if((motor_number & 0x02) != 0) 
		ecrobot_read_i2c(port_id, i2caddr, 0x66, data, 4);
	count = count | (U32)data[0] | ((U32)data[1]) << 8 | ((U32)data[2]) << 16 | ((U32)data[3]) << 24;
	return count;
}

/*
 * set Servo Motor Run revolution in degree
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03
 * @param motor_number: MMX_Motor_1/MMX_Motor_2/MMX_Motor_Both
 * @param count: 1-4294967295 degree
 * @param relativve: Move Absolute(0)/Move Relative(Add new tacho pos to old pos) (1)
 * @param mode: Float(0)/Brake(1)/Brake_Holde(3)
 */
void ecrobot_set_MMX_Run_Rev(U8 port_id, U8 i2caddr, U8 motor_number, S8 speed,U32 count, U8 relative, U8 mode)
{
	U8 inData = 'S';
    unsigned char byte1, byte2, byte3, byte4;
	unsigned char cmdA;
	cmdA = 0x89; // control set tacho, speed, float

	if(relative == 1)
		cmdA |= 0x04;
	if(mode == 1) //brake
		cmdA |= 0x10;
	else if (mode == 2) //brake and hold
		cmdA |= 0x30;
    if(motor_number == MMX_Motor_Both)
		cmdA &= 0x7F;
    
	byte1 = 0xff&count;
    byte2 = 0xff&((0x0000ff00&count)>>8);
    byte3 = 0xff&((0x00ff0000&count)>>16);
    byte4 = 0xff&((0xff000000&count)>>24);
	unsigned char data[8] = {byte1, byte2, byte3, byte4, speed, 0, 0, cmdA};
	
	if((motor_number & 0x01) != 0) {
		ecrobot_send_i2c(port_id, i2caddr, 0x42, data, 8);
		while (i2c_busy(port_id) != 0)
			systick_wait_ms(50);
	}
	if((motor_number & 0x02) != 0) {
		ecrobot_send_i2c(port_id, i2caddr, 0x4A, data, 8);
		while (i2c_busy(port_id) != 0)
			systick_wait_ms(50);
	}
	if	(motor_number == MMX_Motor_Both)
		ecrobot_send_i2c(port_id, i2caddr, 0x41, &inData , 1);
	while (i2c_busy(port_id) != 0)
		systick_wait_ms(50);
	
}


/*
 * MMXMotor is timed done
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03
 * @param motor_number: MMX_Motor_1/MMX_Motor_2/MMX_Motor_Both
 * @return: 0 not done/1 is done
 */
U8 MMX_IsTimeDone(U8 port_id, U8 i2caddr, U8 motor_number)
{
	U8 data[2] = {0, 0};

	ecrobot_read_i2c(port_id,i2caddr, 0x72, data, 2);
	if(motor_number == MMX_Motor_1) 
	{
		if((data[0] & 0x40) == 0) return true;
	} 
	else if(motor_number == MMX_Motor_2) 
	{
		if((data[1] & 0x40) == 0) return true;
	} 
	else if(motor_number == MMX_Motor_Both)
	{
		if(((data[0] & 0x40) == 0) && ((data[1] & 0x40) == 0)) return true;
	}
	return false;
}

/*
 * MMXMotor is tacho done
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03
 * @param motor_number: MMX_Motor_1/MMX_Motor_2/MMX_Motor_Both
 * @return: 0 not done/1 is done
 */
U8 MMX_IsTachoDone(U8 port_id, U8 i2caddr, U8 motor_number)
{
	U8 data[2] = {0, 0};

	ecrobot_read_i2c(port_id,i2caddr, 0x72, data, 2);
	if(motor_number == MMX_Motor_1) 
	{
		if((data[0] & 0x08) == 0) return true;
	} 
	else if(motor_number == MMX_Motor_2) 
	{
		if((data[1] & 0x08) == 0) return true;
	} 
	else if(motor_number == MMX_Motor_Both)
	{
		if(((data[0] & 0x08) == 0) && ((data[1] & 0x08) == 0)) return true;
	}
	return false;
}

/*
 * Read Motor Status
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03
 * @param motor_number: MMX_Motor_1/MMX_Motor_2
 * @return : Motor Status
 * 	Bit 0: 1 Motor is programmed to move at a fixed speed
 *  Bit 1: Motor is Ramping (up or down).
 *  Bit 2: Motor is powered. 
 *  Bit 3: Positional Control is ON. The motor is either moving
 *         towards desired encoder position or holding its position.
 *  Bit 4: Motor is in Brake mode. 
 *  Bit 5: Motor is overloaded. 
 *  Bit 6: Motor is in timed mode. This bit is 1 while the motor
           is programmed to move for given duration.
 *  Bit 7: Motor is stalled. 
 */
U8 MMX_MotorStatus(U8 port_id, U8 i2caddr, U8 motor_number)
{
	U8 motor_status = 0x00; // modified by takashic 2010/05/24

	while (i2c_busy(port_id) != 0);
	if(motor_number == MMX_Motor_1) 
	{
		ecrobot_read_i2c(port_id,i2caddr, 0x72, &motor_status, 1);
		return motor_status;
	} 
	else if(motor_number == MMX_Motor_2) 
	{
		ecrobot_read_i2c(port_id,i2caddr, 0x73, &motor_status, 1);
		return motor_status;
	} 

	while (i2c_busy(port_id) != 0);
	return motor_status; // added by takashic 2010/05/24
}
/*
 * Set Performance Parameters
 *
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param i2caddr:  i2c bus address on the wire >> 1, so if default = 0x06 >> 1 = 0x03
 * @param U16 KP_tacho, U16 KI_tacho, U16 KD_tacho,U16 KP_speed,U16 KI_speed,U16 KD_speed,U8 pass_count,U8 tol
 */
void MMX_SetPerformanceParameters(U8 port_id, U8 i2caddr, U16 KP_tacho, U16 KI_tacho,
    U16 KD_tacho,U16 KP_speed,U16 KI_speed,U16 KD_speed,U8 pass_count,U8 tol)
{
	unsigned char data[14];
	data[0] =    (KP_tacho & 0xFF);
	data[1] =  (((KP_tacho &0xFF00)>>8) & 0xFF);
	data[2] =    (KI_tacho & 0xFF);
	data[3] =  (((KI_tacho &0xFF00)>>8) & 0xFF);
	data[4] =    (KD_tacho & 0xFF);
	data[5] =  (((KD_tacho &0xFF00)>>8) & 0xFF);
	data[6] =    (KP_speed & 0xFF);
	data[7] =  (((KP_speed &0xFF00)>>8) & 0xFF);
	data[8] =   (KI_speed & 0xFF);
	data[9] = (((KI_speed &0xFF00)>>8) & 0xFF);
	data[10] =   (KD_speed & 0xFF);
	data[11] = (((KD_speed &0xFF00)>>8) & 0xFF);
	data[12] = pass_count;
	data[13] = tol;
	
	while (i2c_busy(port_id) != 0);
	ecrobot_send_i2c(port_id, i2caddr, 0x7A, data, 16);
	while (i2c_busy(port_id) != 0);
  
}
