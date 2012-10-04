/**
 *  nxte22.c 
 * 
 * This is a sample program for LATTEBOX NXTe(NXT Extension Kit Product)
 * and LSC22(22-Axis Servo Kit Product)
 * <http://www.lattebox.com/product_list_e.php?pts_type=1>
 * 
 * It enables a NXT to control RC servo motors via I2C.
 * Maximum number of RC servos to be controlled is:
 * Number of NXT Sensor ports(4) * Number of NXTe channels (4) * Number of LSC22 channels (22)
 * = 352 RC Servos might be controlled by using a NXT!
 * 
 * Special thanks to Yu Yang <sog@lattebox.com>
 */ 

#include "ecrobot_interface.h"
#include "nxte22.h"

const U8 I2C_SC18IS602_F0[2] = {0xF0, 0x0C}; /* Configure SPI Interface - Function ID F0h SPI Mode:3, 461kHz */

/* NXTe channel configuration parameters for LSC */
const U8 NXTe_CH[MAX_NXTe_CH] = {0x01, 0x02, 0x04, 0x08};
 
/**
 * init NXTe22. 
 * NOTE that the specified port has to be initialized for I2C (LOWSPEED_9V) before invoking this.
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4 
 */
void init_NXTe22(U8 port_id)
{
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, I2C_SC18IS602_F0[0], (U8 *)&I2C_SC18IS602_F0[1], 1);
}

/**
 * synchronize NXTe and LSC22 connected RC servos
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4 
 * @param nxte_ch: NXTe channel (0x01/0x02/0x04/0x08)
 */
void sync_NXTe22Servo(U8 port_id, U8 nxte_ch)
{
	U8 snd_buf, rcv_buf;
	
	snd_buf = 0x00;
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
	ecrobot_read_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &rcv_buf, 1);
	
	rcv_buf = 0;
	while(1)
	{
		snd_buf = 0xFF; /* send twice */
		ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
		ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
		snd_buf = 0x7F;
		ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);

		snd_buf = 0x00;
		ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
		ecrobot_read_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &rcv_buf, 1);
		
		if (rcv_buf == 99) break;
	}
}

/**
 * load RC servo channels connected to the NXTe
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4 
 * @param nxte_ch: NXTe channel (0x01/0x02/0x04/0x08)
 * @param servo_ch_bit: each bit (0 to 22 bits) represents enable/disable for each servo control
 */
void load_NXTe22Servo(U8 port_id, U8 nxte_ch, U32 servo_ch_bit)
{
	U8 h_byte,l_byte;
	
	servo_ch_bit &= ALL_22SERVO_ENABLE; /* check servo channel range */

	/* send 31 - 16 bits */	
	h_byte = 0xDF;
	l_byte = (U8)((servo_ch_bit >> 16) | 0x80); /* 0x80: servo freq is fixed as 20MHz */

	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &h_byte, 1);
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &l_byte, 1);
	
	/* send 15 - 0 bits */
	h_byte = (U8)(servo_ch_bit >> 8);
	l_byte = (U8)(servo_ch_bit & 0xFF);

	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &h_byte, 1);
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &l_byte, 1);
}

static void sleep(U8 port_id, U8 nxte_ch)
{
	U8 cmd = 0xFD;
	
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &cmd, 1);
}

/**
 * check servo is moving
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4 
 * @param nxte_ch: NXTe channel (0x01/0x02/0x04/0x08)
 * @return: each bit (0 to 21 bits) represents moving(1)/not moving(0) of each servo
 */
U32 read_NXTe22Motion(U8 port_id, U8 nxte_ch)
{
	U8 snd_buf;
	U8 h_byte, m_byte, l_byte;

	sleep(port_id, nxte_ch);	

	snd_buf = 0x5D;
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);

	snd_buf = 0x00;	
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
	ecrobot_read_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &h_byte, 1);

	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
	ecrobot_read_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &m_byte, 1);

	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
	ecrobot_read_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &l_byte, 1);

	return (((U32)(h_byte & 0x7F) << 16) | ((U32)(m_byte & 0xFF) << 8) | (U32)(l_byte & 0xFF)); 
}

/**
 * set delay to a servo
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4 
 * @param nxte_ch: NXTe channel (0x01/0x02/0x04/0x08)
 * @param servo_ch: Servo channel (0 to 21)
 * @param delay: control delay in msec(?)
 */
void set_NXTe22Delay(U8 port_id, U8 nxte_ch, U8 servo_ch, U8 delay)
{
	U8 h_byte,l_byte;
	
	h_byte = (0xE0 | servo_ch);
	l_byte = (U8)(delay & 0x0F);

	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &h_byte, 1);
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &l_byte, 1);
}

/**
 * set angle value of a servo
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4 
 * @param nxte_ch: NXTe channel (0x01/0x02/0x04/0x08)
 * @param servo_ch: Servo channel (0 to 21)
 * @param angle: servo angle count
 */
void set_NXTe22Angle(U8 port_id, U8 nxte_ch, U8 servo_ch, S16 angle)
{
	U8 h_byte,l_byte;
	
	/* limit check */
	if (angle >= MAX_ANGLE)
	{
		angle = MAX_ANGLE;
	}
	else if (angle <= MIN_ANGLE)
	{
		angle = MIN_ANGLE;
	}
	
	h_byte = (U8)(0xC0 | servo_ch);
	l_byte = (U8)(0xF8 | (angle >> 8));

	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &h_byte, 1);
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &l_byte, 1);
	
	h_byte = (U8)(angle & 0xFF);
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &h_byte, 1);
}

/**
 * get angle value of a servo
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4 
 * @param nxte_ch: NXTe channel (0x01/0x02/0x04/0x08)
 * @param servo_ch: Servo channel (0 to 21)
 * @param angle: servo angle count
 */
S16 get_NXTe22Angle(U8 port_id, U8 nxte_ch, U8 servo_ch)
{
	U8 snd_buf;
	U8 h_byte, l_byte;

	sleep(port_id, nxte_ch);	

	h_byte = (U8)(servo_ch | 0x40);
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &h_byte, 1);

	snd_buf = 0x00;
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
	ecrobot_read_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &h_byte, 1);
	
	ecrobot_send_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &snd_buf, 1);
	ecrobot_read_i2c(port_id, NXTe_I2C_ADDR, nxte_ch, &l_byte, 1);
	
	return (((S16)(h_byte & 0x07 ) << 8) + (S16)l_byte);
}
