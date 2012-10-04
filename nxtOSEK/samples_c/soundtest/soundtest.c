/* soundtest.c */
#include	"math.h"

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1); 

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
  StatusType ercd;

  ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
  if(ercd != E_OK)
  {
    ShutdownOS(ercd);
  }
}

/* ===============================================================
 * User Tasks go here
 */

/*
 Sound  1   2   3   4   5   6    7    8    9
 B      62 123 247 494 988 1976 3951 7902
 A#     58 117 233 466 932 1865 3729 7458
 A      55 110 220 440 880 1760 3520 7040 14080
 G#     52 104 208 415 831 1661 3322 6644 13288
 G      49  98 196 392 784 1568 3136 6272 12544
 F#     46  92 185 370 740 1480 2960 5920 11840
 F      44  87 175 349 698 1397 2794 5588 11176
 E      41  82 165 330 659 1319 2637 5274 10548
 D#     39  78 156 311 622 1245 2489 4978 9956
 D      37  73 147 294 587 1175 2349 4699 9398
 C#     35  69 139 277 554 1109 2217 4435 8870
 C      33  65 131 262 523 1047 2093 4186 8372
 Note: Frequency is audible from about 31 to 2100 Hertz.
*/
#define FREQ_MAX  2093 /* C,7 */
#define FREQ_MIN  31   /* B,0 */
#define ASCEND    1.059463094F /* 2^(1/12)  */
#define DESCEND   0.943874313F /* 2^(-1/12) */

double freq = FREQ_MIN;
double gain = ASCEND;

/* Task1 executed every 10ms */
TASK(Task1)
{
  U8 TouchSensorStatus;
  static U8 TouchSensorStatus_old = 0;
  U32 U32_freq;

//  TouchSensorStatus = ecrobot_get_touch_sensor(NXT_PORT_S4);
//  TouchSensorStatus = ecrobot_is_ENTER_button_pressed();
  TouchSensorStatus = ecrobot_is_RUN_button_pressed();
  if (TouchSensorStatus == 1 && TouchSensorStatus_old == 0)
  {
  	U32_freq = (U32)(freq + 0.5); /* rounding */
  	sound_freq(U32_freq, 400);

	display_clear(0);
	display_goto_xy(0, 0);
   	display_string("Freq: ");
   	display_unsigned(U32_freq, 0);
   	display_update();

  	if (freq >= FREQ_MAX) gain = DESCEND; 
  	else if (freq <= FREQ_MIN) 	gain = ASCEND;
	freq *= gain;
  }
  TouchSensorStatus_old = TouchSensorStatus;

  TerminateTask();
}
