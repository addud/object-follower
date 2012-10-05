#ifndef _ECROBOT_BLUETOOTH_H_
#define _ECROBOT_BLUETOOTH_H_

/**
 * Note that the below macros for maximum size of Rx/Tx buffers are valid for
 * ecrobot_send/read_bt. 
 * In case of ecrobot_send/read_bt_packet, further 2 bytes (which the API preserved internally) 
 * should be subtracted from the below macro values. 
 */
#define BT_MAX_TX_BUF_SIZE  (256)  /* maximum size of Bluetooth Tx buffer in byte */
#define BT_MAX_RX_BUF_SIZE  (128)  /* maximum size of Bluetooth Rx buffer in byte */

extern void ecrobot_init_bt_master(const U8* bd_addr, const CHAR* pin);
extern void ecrobot_init_bt_slave(const CHAR* pin);
extern void ecrobot_init_bt_connection(void);

extern void ecrobot_term_bt_connection(void);

extern SINT ecrobot_get_bt_status(void);
extern   U8 ecrobot_get_bt_device_address(U8* bd_addr);
extern   U8 ecrobot_get_bt_device_name(CHAR* bd_name);
extern  S16 ecrobot_get_bt_signal_strength(void);
extern   U8 ecrobot_set_bt_device_name(const CHAR* bd_name);
extern   U8 ecrobot_set_bt_factory_settings(void);

/* NOT RECOMMENDED TO USE (KEEP THEM FOR BACKWARD COMPATIBILITY) */
extern  U32 ecrobot_send_bt_packet(U8* buf, U32 bufLen);
extern  U32 ecrobot_read_bt_packet(U8* buf, U32 bufLen);

/* RECOMMENDED TO USE */
extern  U32 ecrobot_send_bt(const void* buf, U32 off, U32 len);
extern  U32 ecrobot_read_bt(void* buf, U32 off, U32 len);

#endif
