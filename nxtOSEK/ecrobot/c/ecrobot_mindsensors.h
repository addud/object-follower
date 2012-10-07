#ifndef _ECROBOT_MINDSENSORS_H_
#define _ECROBOT_MINDSENSORS_H_

#include "ecrobot_types.h"


/* NXTMMX define */
#define MMX_Motor_1                0x01
#define MMX_Motor_2                0x02
#define MMX_Motor_Both             0x03


/* Mindsensor MMX API */
extern void ecrobot_MMX_init(U8 port_id);
extern void ecrobot_term_MMX(U8 port_id);
extern void ecrobot_set_MMX_speed(U8 port_id, U8 i2caddr, U8 motor_number, S8 speed, U8 mode);
extern void ecrobot_set_MMX_stop(U8 port_id, U8 i2caddr, U8 motor_number, U8 mode);
extern void ecrobot_set_MMX_time(U8 port_id, U8 i2caddr, U8 motor_number, S8 speed, U8 duration, U8 mode);
extern S32 ecrobot_get_MMX_count(U8 port_id, U8 i2caddr, U8 motor_number);
extern void ecrobot_set_MMX_Run_Rev(U8 port_id, U8 i2caddr, U8 motor_number, S8 speed, U32 count, 
									U8 relative, U8 mode);
extern U8 MMX_IsTimeDone(U8 port_id, U8 i2caddr, U8 motor_number);
extern U8 MMX_IsTachoDone(U8 port_id, U8 i2caddr, U8 motor_number);
extern U8 MMX_MotorStatus(U8 port_id, U8 i2caddr, U8 motor_number);
extern void MMX_SetPerformanceParameters(U8 port_id, U8 i2caddr, U16 KP_tacho, U16 KI_tacho,
    U16 KD_tacho,U16 KP_speed,U16 KI_speed,U16 KD_speed,U8 pass_count,U8 tol);

#endif
