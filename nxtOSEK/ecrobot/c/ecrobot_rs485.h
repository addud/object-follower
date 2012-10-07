#ifndef _ECROBOT_RS485_H_
#define _ECROBOT_RS485_H_

#include "ecrobot_types.h"

#define MAX_RS485_TX_DATA_LEN   (64)
#define MAX_RS485_RX_DATA_LEN   (64)
#define DEFAULT_BAUD_RATE_RS485 (921600) // [bps]

/* NXT RS485 API */
extern void ecrobot_init_rs485(U32 baud_rate);
extern void ecrobot_term_rs485(void);
extern  U32 ecrobot_send_rs485(U8* buf, U32 off, U32 len);
extern  U32 ecrobot_read_rs485(U8* buf, U32 off, U32 len);

#endif
