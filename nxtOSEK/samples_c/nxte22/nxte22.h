/* nxte22.h */ 

#ifndef _NXTE22_H_
#define _NXTE22_H_

#include "ecrobot_interface.h"

#define NXTe_I2C_ADDR 0x28 /* 0x50>>1 */
#define MAX_NXTe_CH  4     /* max. number of NXTe channels for LSC */

/* LATTEBOX LSC22 servo channel configuration */  
/* each bit (0 to 21 bits) represents enable/disable for each servo control */
#define ALL_22SERVO_ENABLE 0x03FFFFF
#define MIN_SERVO_CH  0
#define MAX_SERVO_CH 21

#define MAX_ANGLE 2000
#define MIN_ANGLE 0

extern const U8 NXTe_CH[MAX_NXTe_CH];

extern void init_NXTe22(U8 port_id);
extern void sync_NXTe22Servo(U8 port_id, U8 nxte_ch);
extern void load_NXTe22Servo(U8 port_id, U8 nxte_ch, U32 servo_ch_bit);
extern   U32 read_NXTe22Motion(U8 port_id, U8 nxte_ch);
extern void  set_NXTe22Delay(U8 port_id, U8 nxte_ch, U8 servo_ch, U8 delay);
extern void  set_NXTe22Angle(U8 port_id, U8 nxte_ch, U8 servo_ch, S16 angle);
extern   S16  get_NXTe22Angle(U8 port_id, U8 nxte_ch, U8 servo_ch);

#endif
