/* motion.h */

#ifndef _MOTION_H_
#define _MOTION_H_

#include "ecrobot_interface.h"
#include "nxte.h"

#define N_NXTe_CH   1 /* number of NXTe channels in use */
#define SERVO_DELAY 4 /* servo control delay */

#define BLANK -1 /* no angle data */

typedef enum {
	NEUTRAL,
	STAND_UP,
	FORWARD,
	RIGHT_TURN,
	LEFT_TURN
} motionCmd_t;

typedef struct {
	S16 angle[N_NXTe_CH][MAX_SERVO_CH]; /* angles for servo ch01 to ch10 (-1: set no angle) */
	U16 wait; /* wait time in msec after setting all angles */
} motion_t;

typedef struct {
	motion_t *pMotion; /* address of motion parameter */
	int steps; /* motion steps */
} motionTable_t;

extern void initServo(U8 port_id);
extern  int setServo(U8 port_id, motion_t *motion);
extern void setMotion(U8 port_id, motionCmd_t cmd);

#endif
