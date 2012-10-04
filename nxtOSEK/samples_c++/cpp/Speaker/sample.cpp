/* sample.cpp for TOPPERS/ATK(OSEK) */ 


// ECRobot++ API
#include "Speaker.h"
#include "Nxt.h"
#include "Clock.h"
#include "Lcd.h"
using namespace ecrobot;
 
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


// I am not sure these are proper notes
const U32 TONE_TABLE[6][12] =
{
	// C     C#    D     D#    E     F     F#    G     G#    A     A#   B
	{  33,   35,   37,   39,   41,   44,   46,   49,   52,   55,   58,   62},
	{  65,   69,   73,   78,   82,   87,   92,   98,  104,  110,  117,  123},
	{ 131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,  247},
	{ 262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494},
	{ 523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988},
	{1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976}
};

#ifdef PLAY_WAV
// playing WAV file consumes tons of memory, so it needs to use NXT BIOS
EXTERNAL_WAV_DATA(lego_mindstorms_nxt); // lego_mindstorms_nxt.wav (just speaks "LEGO MINDSTORMS NXT")
#endif

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Speaker speaker;
	Nxt nxt;
	Clock clock;
	Lcd lcd;

	lcd.clear();
	lcd.putf("s", "Speaker");
	lcd.disp();

	while(1)
	{
#ifdef PLAY_WAV
		if (nxt.getButtons() == Nxt::RUN_ON)
		{
			speaker.playWav(WAV_DATA_START(lego_mindstorms_nxt), 
				(U32)WAV_DATA_SIZE(lego_mindstorms_nxt), 70);
			clock.wait(100);
		}
#endif
		if (nxt.getButtons() == Nxt::ENTR_ON)
		{
			for (SINT scale = 0; scale < 6; scale++)
			{
				for (SINT note = 0; note < 12; note++)
				{
		 			speaker.playTone(TONE_TABLE[scale][note], 200, 20);
					clock.wait(200);
				}
			}
		}
	}
}

}
