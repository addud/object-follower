/* sample.cpp for TOPPERS/ATK(OSEK) */ 

#include <string.h>

// ECRobot++ API
#include "Nxt.h"
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

#include "BmpFileDraw.h"

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* 
 * Intro of NXT firmware(RCXintro_1.bmp - RCXintro_16.bmp) 
 * are included in NXT firmware source code.
 * <http://mindstorms.lego.com/Overview/NXTreme.aspx> 
 */
EXTERNAL_BMP_DATA(RCXintro_1);
EXTERNAL_BMP_DATA(RCXintro_2);
EXTERNAL_BMP_DATA(RCXintro_3);
EXTERNAL_BMP_DATA(RCXintro_4);
EXTERNAL_BMP_DATA(RCXintro_5);
EXTERNAL_BMP_DATA(RCXintro_6);
EXTERNAL_BMP_DATA(RCXintro_7);
EXTERNAL_BMP_DATA(RCXintro_8);
EXTERNAL_BMP_DATA(RCXintro_9);
EXTERNAL_BMP_DATA(RCXintro_10);
EXTERNAL_BMP_DATA(RCXintro_11);
EXTERNAL_BMP_DATA(RCXintro_12);
EXTERNAL_BMP_DATA(RCXintro_13);
EXTERNAL_BMP_DATA(RCXintro_14);
EXTERNAL_BMP_DATA(RCXintro_15);
EXTERNAL_BMP_DATA(RCXintro_16);

typedef struct
{
	const CHAR *bmp;
	U32 width;
	U32 height;
	U32 x;
	U32 y;
} BMP_DATA;

const BMP_DATA bmp_table[] = {
	{ BMP_DATA_START(RCXintro_1),  64, 64, 16, 0 },
	{ BMP_DATA_START(RCXintro_2),  64, 64, 16, 0 },	
	{ BMP_DATA_START(RCXintro_3),  64, 64, 16, 0 },
	{ BMP_DATA_START(RCXintro_4),  64, 64, 16, 0 },
	{ BMP_DATA_START(RCXintro_5),  52, 64, 23, 0 },
	{ BMP_DATA_START(RCXintro_6),  44, 48, 28, 0 },
	{ BMP_DATA_START(RCXintro_7),  34, 40, 35, 0 },
	{ BMP_DATA_START(RCXintro_8),  22, 24, 44, 0 },
	{ BMP_DATA_START(RCXintro_9),  14, 24, 52, 0 },
	{ BMP_DATA_START(RCXintro_10), 10, 16, 56, 0 },
	{ BMP_DATA_START(RCXintro_11),  8, 16, 58, 0 },
	{ BMP_DATA_START(RCXintro_12), 94, 16,  3, 0 },
	{ BMP_DATA_START(RCXintro_13), 94, 16,  3, 0 },
	{ BMP_DATA_START(RCXintro_14), 94, 16,  3, 0 },
	{ BMP_DATA_START(RCXintro_15), 94, 16,  3, 0 },
	{ BMP_DATA_START(RCXintro_16), 94, 16,  3, 0 }
};

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Clock clock;
	Nxt nxt;
	Lcd lcd;

	BmpFileDraw* bmpFile = new BmpFileDraw(lcd);
	for (SINT i = 0; i < (SINT)(sizeof(bmp_table)/sizeof(BMP_DATA)); i++)
	{
		lcd.clear();
		bmpFile->draw(bmp_table[i].bmp, bmp_table[i].width, bmp_table[i].height, bmp_table[i].x, bmp_table[i].y);
		lcd.putf("d", i+1,0);
		lcd.disp();
		clock.wait(200);
	}
	delete bmpFile;
		
	while(true);
}
}
