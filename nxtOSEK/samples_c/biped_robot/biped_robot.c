/**
 *  biped_robot.c 
 * 
 * This is a sample program for LATTEBOX NXTe/LSC based biped robot.
 * 
 * Special thanks to Yu Yang <sog@lattebox.com>
 */ 
#include "kernel.h"
#include "kernel_id.h"

#include "ecrobot_interface.h"
#include "sleep.h"
#include "motion.h"

/* OSEK declarations */
DeclareTask(Task_Init);
DeclareTask(Task_Commander);
DeclareTask(Task_Display);
DeclareTask(Task_MotionControl);
DeclareResource(ResourceCommand);
DeclareCounter(SysTimerCnt);

/* NXT Sensor port configration */
#define NXTe_PORT  NXT_PORT_S3

/* robot motion command */
static motionCmd_t motionCmd;

/*=============================================================================
 * nxtOSEK system hook functions
 */
void ecrobot_device_initialize()
{
	ecrobot_init_i2c(NXTe_PORT, LOWSPEED_9V);
	ecrobot_init_bt_slave("nxtOSEK");
}

void ecrobot_device_terminate()
{
	ecrobot_term_i2c(NXTe_PORT);
	ecrobot_term_bt_connection();
}

void user_1ms_isr_type2(void)
{
	StatusType ercd;

	ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
	if(ercd != E_OK)
	{
		ShutdownOS(ercd);
	}
  
    check_sleepers(); /* check on sleeping Tasks */
}

/*=============================================================================
 * User Tasks go here
 */

motionCmd_t getMotionCommand(S8 in1, S8 in2)
{
	motionCmd_t cmd = STAND_UP; /* default command */
	
	if (in1 == 0)
	{
		if (in2 > 0)
		{
			cmd = RIGHT_TURN;
		}
		else if (in2 < 0)
		{
			cmd = LEFT_TURN;
		}
	}
	else if (in1 > 0)
	{
		if (in2 == 0)
		{
			cmd = FORWARD;
		}
	}

	return cmd;
} 

/**
 * Initialize application
 */
TASK(Task_Init)
{
	initServo(NXTe_PORT);
	motionCmd = STAND_UP; /* default motion */
	
	TerminateTask();
}

/**
 * Receive Bluetooth message and publish a motion command.
 * This command decoder is assumed to be use for NXT GamePad.
 * NXT GamePad sends two user inputs 
 * - packet0: analog left stick input in vertical direction
 *   (upper max to lower max = -100 to 100)
 * - packet1: analog right stick input in horizontal direction
 *   (left max to right max = -100 to 100) 
 */
TASK(Task_Commander)
{
	U8 bt_receive_buf[32]; /* buffer size is fixed as 32 */ 

	/* read Bluetooth Rx data */
  	if (ecrobot_read_bt_packet(bt_receive_buf, 32))
  	{
		GetResource(ResourceCommand);
		motionCmd = getMotionCommand(-(*(S8 *)(&bt_receive_buf[0])), (*(S8 *)(&bt_receive_buf[1])));
		ReleaseResource(ResourceCommand);
  	}

	TerminateTask();
}

/**
 * Display NXT standard sensors/motors/internal status information.
 */
TASK(Task_Display)
{
  	ecrobot_status_monitor("BIPED ROBOT");

  	TerminateTask();
}

/**
 * Send angle data to NXTe according to motion command.
 * This Task should be invoked as a background Task.
 */
TASK(Task_MotionControl)
{
	motionCmd_t cmd;

	GetResource(ResourceCommand);
	cmd = motionCmd; /* latch motion command */
	ReleaseResource(ResourceCommand);

	/* set a robot motion */
	setMotion(NXTe_PORT, cmd);

	/* back ground task should end like this unless it's a one-shot task */
    TaskType t;
    GetTaskID(&t);
    ChainTask(t);
}
