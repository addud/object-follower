/**
 *  motion.c 
 * 
 * Motion control for LATTEBOX NXTe/LSC based biped robot.
 * All motion parameters are based on nxtelib.nxc.
 * 
 * Special thanks to Yu Yang <sog@lattebox.com>
 */ 

#include "ecrobot_interface.h"
#include "sleep.h"
#include "motion.h"

/*=============================================================================
 * Robot motion paramters table
 * 
 *  {{ ch01,  ch02,  ch03,  ch04,  ch05,  ch06,  ch07,  ch08,  ch09,  ch10}, wait}
 */

/* motion parameters for RC servo neutral position */
const motion_t PRM_NEUTRAL[] = {
   {{{ 1000,  1000,  1000,  1000,  1000,  1000,  1000,  1000,  1000,  1000}},   0}
};

/* motion parameters for standing up */
const motion_t PRM_STAND_UP[] = {
   {{{ 1000,  1000,   800,  1200,   800,  1200,   800,  1200,  1000,  1000}}, 500}
};

/* motion parameters for going forward */
const motion_t PRM_FORWARD[] = {
   {{{  950,   950, BLANK, BLANK, BLANK, BLANK,   850, BLANK, BLANK,  1050}}, 200},
   {{{BLANK, BLANK,   300, BLANK,   400, BLANK,   900, BLANK,  1050,  1100}}, 100},
   {{{BLANK, BLANK,   200,  1100, BLANK, BLANK, BLANK,  1350,   850,   900}}, 200},
   {{{BLANK, BLANK,   800, BLANK,   800, BLANK,   850, BLANK, BLANK, BLANK}},   0},
   {{{BLANK, BLANK, BLANK,  1600, BLANK,  1500, BLANK, BLANK, BLANK, BLANK}}, 200},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,  1200, BLANK, BLANK}},   0},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,   700, BLANK,  1100,  1150}}, 100},
   {{{BLANK, BLANK, BLANK,  1200, BLANK,  1200, BLANK, BLANK,  1000,  1050}}, 200},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,   850, BLANK, BLANK, BLANK}}, 100}
};

/* motion parameters for turning right */
const motion_t PRM_RIGHT_TURN[] = {
   {{{ 1050,  1050, BLANK, BLANK, BLANK, BLANK,   850, BLANK, BLANK,  1050}}, 200},
   {{{BLANK, BLANK,   300, BLANK,   400, BLANK,   900, BLANK,  1050,  1100}}, 100},
   {{{BLANK, BLANK,   200,  1100, BLANK, BLANK, BLANK,  1350,   850,   900}}, 200},
   {{{BLANK, BLANK,   800, BLANK,   800, BLANK,   850, BLANK, BLANK, BLANK}},   0},
   {{{BLANK, BLANK, BLANK,  1600, BLANK,  1500, BLANK, BLANK, BLANK, BLANK}}, 200},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,  1200, BLANK, BLANK}},   0},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,   700, BLANK,  1100,  1150}}, 100},
   {{{BLANK, BLANK, BLANK,  1200, BLANK,  1200, BLANK, BLANK,  1000,  1050}}, 200},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,   850, BLANK, BLANK, BLANK}}, 100}
};

/* motion parameters for turning left */
const motion_t PRM_LEFT_TURN[] = {
   {{{  950,   950, BLANK, BLANK, BLANK, BLANK, BLANK,  1150,   950, BLANK}}, 200},
   {{{BLANK, BLANK, BLANK,  1700, BLANK,  1600, BLANK,  1100,   900,   950}}, 100},
   {{{BLANK, BLANK,   900,  1800, BLANK, BLANK,   650, BLANK,  1100,  1150}}, 200},
   {{{BLANK, BLANK, BLANK,  1200, BLANK,  1200, BLANK,  1150, BLANK, BLANK}},   0},
   {{{BLANK, BLANK,   400, BLANK,   500, BLANK, BLANK, BLANK, BLANK, BLANK}}, 200},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,   800, BLANK, BLANK, BLANK}},   0},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,  1300,   850,   900}}, 100},
   {{{BLANK, BLANK,   800, BLANK,   800, BLANK, BLANK, BLANK,   950,  1000}}, 200},
   {{{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,  1150, BLANK, BLANK}}, 100}
};

/* robot motion paramters table */
const motionTable_t motionTable[] = {
	{(motion_t *)PRM_NEUTRAL,    sizeof(PRM_NEUTRAL)/sizeof(motion_t)},
	{(motion_t *)PRM_STAND_UP,   sizeof(PRM_STAND_UP)/sizeof(motion_t)},
	{(motion_t *)PRM_FORWARD,    sizeof(PRM_FORWARD)/sizeof(motion_t)},
	{(motion_t *)PRM_RIGHT_TURN, sizeof(PRM_RIGHT_TURN)/sizeof(motion_t)},
	{(motion_t *)PRM_LEFT_TURN,  sizeof(PRM_LEFT_TURN)/sizeof(motion_t)}
};


/*=============================================================================
 * Functions
 */

/**
 * initialize all servos which are connected to NXTe/LSC
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * 
 */
void initServo(U8 port_id)
{
	int i;
	U8 servo_ch;
	
	init_NXTe(port_id);

	for (i = 0; i < N_NXTe_CH; i++)
	{
		sync_NXTeServo(port_id, NXTe_CH[i]);
		load_NXTeServo(port_id, NXTe_CH[i], ALL_SERVO_ENABLE);

		/* set motion control delay */
		for (servo_ch = MIN_SERVO_CH; servo_ch <= MAX_SERVO_CH; servo_ch++)
		{
			set_NXTeDelay(port_id, NXTe_CH[i], servo_ch, SERVO_DELAY);
		}
	} 
}

/**
 * set servo angles and wait in msec
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param motion: motion paramter
 * @return: 1(success)/0(failure) 
 */
int setServo(U8 port_id, motion_t *motion)
{
	int i;
	S16 angle;
	U8 servo_ch;
	
	for (i = 0; i < N_NXTe_CH; i++)
	{
		/* check all servos to be controlled is not moving */
		if (read_NXTeMotion(port_id, NXTe_CH[i]) != 0) return 0;
	}

	for (i = 0; i < N_NXTe_CH; i++)
	{
		/* send data to each NXTe channel(LSC) */
		for (servo_ch = MIN_SERVO_CH; servo_ch <= MAX_SERVO_CH; servo_ch++)
		{
			angle = motion->angle[i][servo_ch-1];
			if (angle != BLANK)
			{
				/* send angle data to each servo */
				set_NXTeAngle(port_id, NXTe_CH[i], servo_ch, angle);
			}
		}
	}
	
	if (motion->wait > 0)
	{	
		/* OSEK caller task is turned into waiting mode 
		 * during the specified period in msec
		 */
		sleep(motion->wait);
	}

	return 1;
}

/**
 * set motion data to servos according to pre-defined motion command
 * 
 * @param port_id: NXT_PORT_S1/NXT_PORT_S2/NXT_PORT_S3/NXT_PORT_S4
 * @param cmd: motion command
 */
void setMotion(U8 port_id, motionCmd_t cmd)
{
	int i;
	
	if (cmd >= sizeof(motionTable)) return;
	
	for (i = 0; i < motionTable[cmd].steps; i++)
	{
		if (setServo(port_id, motionTable[cmd].pMotion + i) == 0)
		{
			/* if robot is moving, try the same step again */
			if (--i < 0) i = 0;
		}
	}
}
