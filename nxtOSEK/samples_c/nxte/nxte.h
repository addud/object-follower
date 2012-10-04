/* nxte.h */ 

#ifndef _NXTE_H_
#define _NXTE_H_

#include "ecrobot_interface.h"

#define NXTe_I2C_ADDR 0x28 /* 0x50>>1 */
#define MAX_NXTe_CH  4     /* max. number of NXTe channels for LSC */

/* LATTEBOX LSC servo channel configuration */  
/* each bit (0 to 9 bits) represents enable/disable for each servo control */
#define ALL_SERVO_ENABLE 0x03FF
#define MIN_SERVO_CH  1
#define MAX_SERVO_CH 10

#define MAX_ANGLE 2000
#define MIN_ANGLE 0

extern const U8 NXTe_CH[MAX_NXTe_CH];

extern void init_NXTe(U8 port_id);
extern void sync_NXTeServo(U8 port_id, U8 nxte_ch);
extern void load_NXTeServo(U8 port_id, U8 nxte_ch, U16 servo_ch_bit);
extern   U16 read_NXTeMotion(U8 port_id, U8 nxte_ch);
extern void  set_NXTeDelay(U8 port_id, U8 nxte_ch, U8 servo_ch, U8 delay);
extern void  set_NXTeAngle(U8 port_id, U8 nxte_ch, U8 servo_ch, S16 angle);
extern   S16  get_NXTeAngle(U8 port_id, U8 nxte_ch, U8 servo_ch);

#endif
