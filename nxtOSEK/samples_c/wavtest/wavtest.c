/* wavtest.c */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareTask(Task1); 

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

/*
 * a wav file can be accessed by using following macros:
 * E.g lego_mindstorms_nxt.wav
 * EXTERNAL_WAV_DATA(file name without extension); <- This is external declarations
 * WAV_DATA_START(file name without extension)     <- start address of a wav file
 * WAV_DATA_END(file name without extension)       <- end address of a wav file
 * WAV_DATA_SIZE(file name without extension)      <- size of a wav file 
 */
EXTERNAL_WAV_DATA(lego_mindstorms_nxt);

TASK(Task1)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string("WAV TEST");
	display_goto_xy(0, 2);
	display_string("PRESS ENTR");
	display_update();

	while(1)
  	{
  		if (ecrobot_is_ENTER_button_pressed())
  		{
  			ecrobot_sound_wav(WAV_DATA_START(lego_mindstorms_nxt), 
  				(U32)WAV_DATA_SIZE(lego_mindstorms_nxt), -1, 70);
  		}
	}
  
	TerminateTask();
}
