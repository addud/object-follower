#ifndef _ECROBOT_INTERFACE_H_
#define _ECROBOT_INTERFACE_H_

/* LEJOS NXJ I/O drivers */
#include "mytypes.h"
#include "interrupts.h"
#include "aic.h"
#include "AT91SAM7.h"
#include "uart.h"
#include "systick.h"
#include "nxt_avr.h"
#include "twi.h"
#include "platform_hooks.h"
#include "nxt_avr.h"
#include "nxt_lcd.h"
#include "nxt_motors.h"
#include "sensors.h"
#include "display.h"
#include "i2c.h"
#include "bt.h"
#include "sound.h"
#include "udp.h"
#include "hs.h"

#include "ecrobot_types.h"
#include "ecrobot_bluetooth.h"
#include "ecrobot_usb.h"
#include "ecrobot_rs485.h"
#include "ecrobot_mindsensors.h"


typedef enum {
	NXT_PORT_A,
	NXT_PORT_B,
	NXT_PORT_C
}MOTOR_PORT_T;

typedef enum {
	NXT_PORT_S1,
	NXT_PORT_S2,
	NXT_PORT_S3,
	NXT_PORT_S4
}SENSOR_PORT_T;

typedef enum {
	EXECUTED_FROM_FLASH,
	EXECUTED_FROM_SRAM,
	DEVICE_NO_INIT,
	DEVICE_INITIALIZED,
	BT_NO_INIT,
	BT_INITIALIZED,
	BT_CONNECTED,
	BT_STREAM,
}SYSTEM_T;

#define EXTERNAL_WAV_DATA(name) \
  extern const CHAR name##_wav_start[]; \
  extern const CHAR name##_wav_end[]; \
  extern const CHAR name##_wav_size[]

#define WAV_DATA_START(name) name##_wav_start
#define WAV_DATA_END(name)   name##_wav_end
#define WAV_DATA_SIZE(name)  name##_wav_size

#define EXTERNAL_BMP_DATA(name) \
  extern const CHAR name##_bmp_start[]; \
  extern const CHAR name##_bmp_end[]; \
  extern const CHAR name##_bmp_size[]

#define BMP_DATA_START(name) name##_bmp_start
#define BMP_DATA_END(name)   name##_bmp_end
#define BMP_DATA_SIZE(name)  name##_bmp_size

#define LOWSPEED_9V 1
#define LOWSPEED    2

/* NXT buttons */
#define BTN_ORANGE_RECT  (0x01)
#define BTN_LEFT         (0x02)
#define BTN_RIGHT        (0x04)
#define BTN_GRAY_RECT    (0x08)

/* NXT Color Sensor sensor mode macros */
#define NXT_COLORSENSOR              (0) // activates as a color sensor 
#define NXT_LIGHTSENSOR_RED          (1) // activates as a light sensor with red lamp
#define NXT_LIGHTSENSOR_GREEN        (2) // activates as a light sensor with green lamp
#define NXT_LIGHTSENSOR_BLUE         (3) // activates as a light sensor with blue lamp
#define NXT_LIGHTSENSOR_WHITE        (4) // activates as a light sensor with white lamp
#define NXT_LIGHTSENSOR_NONE         (5) // activates as a light sensor with no lamp
#define NXT_COLORSENSOR_DEACTIVATE   (6) // deactivates the sensor
#define NUM_OF_NXT_COLORSENSOR_MODES (7)

/* NXT Color Sensor color number macros */
#define NXT_COLOR_BLACK              (0)
#define NXT_COLOR_BLUE               (1)
#define NXT_COLOR_GREEN              (2)
#define NXT_COLOR_YELLOW             (3)
#define NXT_COLOR_ORANGE             (4)
#define NXT_COLOR_RED                (5)
#define NXT_COLOR_WHITE              (6)
#define NXT_COLOR_UNKNOWN            (99)

/* HiTechnic Color Sensor calibration modes */
#define CAL_WHITE  0x43
#define CAL_BLACK  0x42

/* HiTechnic Prototype Sensor digital port configurations */
#define HTPS_DIGTAL_PORTS (0x3f)
#define HTPS_D0           (0x01)
#define HTPS_D1           (0x02)
#define HTPS_D2           (0x04)
#define HTPS_D3           (0x08)
#define HTPS_D4           (0x10)
#define HTPS_D5           (0x20)

/*HiTechnic Tetrix controllers*/

#define TETRIX_MODE_PWM 0x00
#define TETRIX_MODE_PWM_REV 0x08
#define TETRIX_MOTOR_FLOAT -128
#define TETRIX_MOTOR_BRAKE 0
#define TETRIX_ADDRESS_1 0x01         //Daisey chain position 1
#define TETRIX_ADDRESS_2 0x02         //Daisey chain position 2
#define TETRIX_ADDRESS_3 0x03         //Daisey chain position 3
#define TETRIX_ADDRESS_4 0x04         //Daisey chain position 4
#define TETRIX_SERVO_OFF 0xFF               //turn off servos/float
#define TETRIS_SERVO_ON_NO_TIMEOUT   0xAA              //Disable 10 second TIMER
#define TETRIX_SERVO_ON 0x00   //restart 10 second timer
#define TETRIX_SERVO_NO_STEP_TIME 0x00       //all servo run at their maximum rate

/* NXT servo motor API */
extern  S32 ecrobot_get_motor_rev(U8 port_id);
extern void ecrobot_set_motor_speed(U8 port_id, S8 speed);
extern void ecrobot_set_motor_mode_speed(U8 port_id, S32 mode, S8 speed);

/* NXT light sensor API */
extern  U16 ecrobot_get_light_sensor(U8 port_id);
extern void ecrobot_set_light_sensor_active(U8 port_id);
extern void ecrobot_set_light_sensor_inactive(U8 port_id);

/* NXT touch sensor API */
extern   U8 ecrobot_get_touch_sensor(U8 port_id);

/* NXT sound sensor API */
extern  U16 ecrobot_get_sound_sensor(U8 port_id);

/* NXT I2C API */
extern void ecrobot_init_i2c(U8 port_id, U8 type);
extern   U8 ecrobot_wait_i2c_ready(U8 port_id, U32 wait);
extern SINT ecrobot_send_i2c(U8 port_id, U32 address, SINT i2c_reg, U8 *buf, U32 len);
extern SINT ecrobot_read_i2c(U8 port_id, U32 address, SINT i2c_reg, U8 *buf, U32 len);
extern void ecrobot_term_i2c(U8 port_id);

/* NXT ultrasonic sensor API */
extern void ecrobot_init_sonar_sensor(U8 port_id);
extern  S32 ecrobot_get_sonar_sensor(U8 port_id);
extern void ecrobot_term_sonar_sensor(U8 port_id);

/* NXT color sensor API */
extern void ecrobot_init_nxtcolorsensor(U8 port_id, U8 mode);
extern void ecrobot_process_bg_nxtcolorsensor(void);
extern void ecrobot_set_nxtcolorsensor(U8 port_id, U8 mode);
extern   U8 ecrobot_get_nxtcolorsensor_mode(U8 port_id);
extern  U16 ecrobot_get_nxtcolorsensor_id(U8 port_id);
extern void ecrobot_get_nxtcolorsensor_rgb(U8 port_id, S16 rgb[3]);
extern  U16 ecrobot_get_nxtcolorsensor_light(U8 port_id);
extern void ecrobot_term_nxtcolorsensor(U8 port_id);

/* HiTechnic gyro sensor API */
extern  U16 ecrobot_get_gyro_sensor(U8 port_id);

/* HiTechnic acceleration sensor API */
extern void ecrobot_init_accel_sensor(U8 port_id);
extern void ecrobot_get_accel_sensor(U8 port_id, S16 buf[3]);
extern void ecrobot_term_accel_sensor(U8 port_id);

/* HiTechnic IR Seeker API */
extern void ecrobot_init_ir_seeker(U8 port_id);
extern void ecrobot_get_ir_seeker(U8 port_id, S8 buf[6]);
extern void ecrobot_term_ir_seeker(U8 port_id);

/* HiTechnic color sensor API */
extern void ecrobot_init_color_sensor(U8 port_id);
extern   U8 ecrobot_cal_color_sensor(U8 port_id, U8 mode);
extern void ecrobot_get_color_sensor(U8 port_id, S16 buf[3]);
extern void ecrobot_term_color_sensor(U8 port_id);

/* HiTechnic compass sensor API */
extern void ecrobot_init_compass_sensor(U8 port_id);
extern   U8 ecrobot_cal_compass_sensor(U8 port_id);
extern  S16 ecrobot_get_compass_sensor(U8 port_id);
extern void ecrobot_term_compass_sensor(U8 port_id);

/* HiTechnic prototype sensor API */
extern void ecrobot_init_prototype_sensor(U8 port_id, U8 rate, U8 dir);
extern void ecrobot_get_prototype_analog_sensor(U8 port_id, S16 buf[5]);
extern   U8 ecrobot_get_prototype_digital_sensor(U8 port_id);
extern void ecrobot_get_prototype_sensor(U8 port_id, S16 a_buf[5], U8 d_buf[6]);
extern void ecrobot_send_prototype_digital_sensor(U8 port_id, U8 data);
extern void ecrobot_term_prototype_sensor(U8 port_id);

/* HiTechnic Tetrix controllers */
extern void ecrobot_init_tetrix(U8 port_id);
extern void ecrobot_tetrix_motors(U8 port_id, U32 i2c_address, U8 mode_motor1, U8 mode_motor2, S8 pwm_motor1, S8 pwm_motor2);
extern void ecrobot_tetrix_servos(U8 port_id, U32 i2c_address, U8 step_time, U8 pwm, U8 servo1, U8 servo2, U8 servo3, U8 servo4, U8 servo5, U8 servo6);
extern U32 ecrobot_tetrix_battery(U8 port_id, U32 i2c_address);
extern void ecrobot_term_tetrix(U8 port_id);

/* RCX sensors API */
extern void ecrobot_set_RCX_power_source(U8 port_id);
extern void ecrobot_term_RCX_power_source(U8 port_id);
extern  S16 ecrobot_get_RCX_sensor(U8 port_id);
extern   U8 ecrobot_get_RCX_touch_sensor(U8 port_id);

/* NXT internal status API */
extern  U16 ecrobot_get_battery_voltage(void);
extern  U32 ecrobot_get_systick_ms(void);
extern   U8 ecrobot_is_ENTER_button_pressed(void);
extern   U8 ecrobot_is_RUN_button_pressed(void);
extern   U8 ecrobot_get_button_state(void);
extern void ecrobot_restart_NXT(void);
extern void ecrobot_shutdown_NXT(void);
extern void ecrobot_exec_NXT_BIOS(void); /* It works only if NXT BIOS is used. Otherwise, do nothing. */

/* LCD display command for system */
extern SINT ecrobot_bmp2lcd(const CHAR *file, U8 *lcd, S32 width, S32 height);
extern void ecrobot_show_int(S32 var);
extern void ecrobot_debug1(UINT var1, UINT var2, UINT var3);
extern void ecrobot_debug2(UINT var1, UINT var2, UINT var3);
extern void ecrobot_status_monitor(const CHAR *target_name);
extern void ecrobot_adc_data_monitor(const CHAR *target_name);
extern void ecrobot_bt_data_logger(S8 data1, S8 data2);
extern void ecrobot_bt_adc_data_logger(S8 data1, S8 data2, S16 adc1, S16 adc2, S16 adc3, S16 adc4);
extern void ecrobot_sint_var_monitor(SINT vars[16]);

/* NXT sound API */
extern SINT ecrobot_sound_tone(U32 freq, U32 ms, U32 vol);
extern SINT ecrobot_sound_wav(const CHAR *file, U32 length, S32 freq, U32 vol);

/* system hook functions */
extern void ecrobot_device_initialize(void);
extern void ecrobot_device_terminate(void);

extern void user_1ms_isr_type2(void); /* This function must be used for only TOPPERS/ATK */
extern void check_NXT_buttons(void);  /* This function must be used for only TOPPERS/JSP */
extern SINT get_OS_flag(void);        /* This function must be used for only TOPPERS/JSP */

#endif
