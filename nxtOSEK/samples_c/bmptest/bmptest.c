/* bmptest.c */ 
#include <string.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareTask(Task1);

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

/*
 * a bmp file can be accessed by using following macros:
 * E.g RCXintro_1.bmp
 * EXTERNAL_BMP_DATA(file name without extension); <- This is external declarations
 * BMP_DATA_START(file name without extension)     <- start address of a bmp file
 * BMP_DATA_END(file name without extension)       <- end address of a bmp file
 * BMP_DATA_SIZE(file name without extension)      <- size of a bmp file 
 */

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
	const char *bmp;
	int width;
	int height;
	int x;
	int y;
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

TASK(Task1)
{
	static U8 lcd[NXT_LCD_DEPTH*NXT_LCD_WIDTH];
	int i;

	while(1)
  	{
		if (ecrobot_is_RUN_button_pressed())
		{
			for (i = 0; i < sizeof(bmp_table)/sizeof(BMP_DATA); i++)
			{
				memset(lcd, 0x00, sizeof(lcd));
				ecrobot_bmp2lcd(bmp_table[i].bmp, lcd, bmp_table[i].width, bmp_table[i].height);
				display_clear(0);
				display_bitmap_copy(lcd, 100, 8, bmp_table[i].x, bmp_table[i].y);
				display_update();
				systick_wait_ms(120);
			}
		}
  	}

	TerminateTask();
}
