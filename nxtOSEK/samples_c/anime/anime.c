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
EXTERNAL_BMP_DATA(anime00000);
EXTERNAL_BMP_DATA(anime00004);
EXTERNAL_BMP_DATA(anime00008);
EXTERNAL_BMP_DATA(anime00012);
EXTERNAL_BMP_DATA(anime00016);
EXTERNAL_BMP_DATA(anime00020);
EXTERNAL_BMP_DATA(anime00024);
EXTERNAL_BMP_DATA(anime00028);
EXTERNAL_BMP_DATA(anime00032);
EXTERNAL_BMP_DATA(anime00036);
EXTERNAL_BMP_DATA(anime00040);
EXTERNAL_BMP_DATA(anime00044);
EXTERNAL_BMP_DATA(anime00048);
EXTERNAL_BMP_DATA(anime00052);
EXTERNAL_BMP_DATA(anime00056);
EXTERNAL_BMP_DATA(anime00060);
EXTERNAL_BMP_DATA(anime00064);
EXTERNAL_BMP_DATA(anime00068);
EXTERNAL_BMP_DATA(anime00072);
EXTERNAL_BMP_DATA(anime00076);
EXTERNAL_BMP_DATA(anime00080);
EXTERNAL_BMP_DATA(anime00084);
EXTERNAL_BMP_DATA(anime00088);
EXTERNAL_BMP_DATA(anime00092);
EXTERNAL_BMP_DATA(anime00096);
EXTERNAL_BMP_DATA(anime00100);
EXTERNAL_BMP_DATA(anime00104);
EXTERNAL_BMP_DATA(anime00108);
EXTERNAL_BMP_DATA(anime00112);
EXTERNAL_BMP_DATA(anime00116);
EXTERNAL_BMP_DATA(anime00120);
EXTERNAL_BMP_DATA(anime00124);
EXTERNAL_BMP_DATA(anime00128);
EXTERNAL_BMP_DATA(anime00132);
EXTERNAL_BMP_DATA(anime00136);
EXTERNAL_BMP_DATA(anime00140);
EXTERNAL_BMP_DATA(anime00144);
EXTERNAL_BMP_DATA(anime00148);
EXTERNAL_BMP_DATA(anime00152);
EXTERNAL_BMP_DATA(anime00156);
EXTERNAL_BMP_DATA(anime00160);
EXTERNAL_BMP_DATA(anime00164);
EXTERNAL_BMP_DATA(anime00168);
EXTERNAL_BMP_DATA(anime00172);
EXTERNAL_BMP_DATA(anime00176);
EXTERNAL_BMP_DATA(anime00180);
EXTERNAL_BMP_DATA(anime00184);
EXTERNAL_BMP_DATA(anime00188);
EXTERNAL_BMP_DATA(anime00192);
EXTERNAL_BMP_DATA(anime00196);
EXTERNAL_BMP_DATA(anime00200);
EXTERNAL_BMP_DATA(anime00204);
EXTERNAL_BMP_DATA(anime00208);
EXTERNAL_BMP_DATA(anime00212);
EXTERNAL_BMP_DATA(anime00216);
EXTERNAL_BMP_DATA(anime00220);
EXTERNAL_BMP_DATA(anime00224);
EXTERNAL_BMP_DATA(anime00228);
EXTERNAL_BMP_DATA(anime00232);
EXTERNAL_BMP_DATA(anime00236);
EXTERNAL_BMP_DATA(anime00240);
EXTERNAL_BMP_DATA(anime00244);
EXTERNAL_BMP_DATA(anime00248);
EXTERNAL_BMP_DATA(anime00252);
EXTERNAL_BMP_DATA(anime00256);
EXTERNAL_BMP_DATA(anime00260);
EXTERNAL_BMP_DATA(anime00264);
EXTERNAL_BMP_DATA(anime00268);
EXTERNAL_BMP_DATA(anime00272);
EXTERNAL_BMP_DATA(anime00276);
EXTERNAL_BMP_DATA(anime00280);
EXTERNAL_BMP_DATA(anime00284);
EXTERNAL_BMP_DATA(anime00288);
EXTERNAL_BMP_DATA(anime00292);
EXTERNAL_BMP_DATA(anime00296);
EXTERNAL_BMP_DATA(anime00300);
EXTERNAL_BMP_DATA(anime00304);
EXTERNAL_BMP_DATA(anime00308);
EXTERNAL_BMP_DATA(anime00312);
EXTERNAL_BMP_DATA(anime00316);
EXTERNAL_BMP_DATA(anime00320);
EXTERNAL_BMP_DATA(anime00324);
EXTERNAL_BMP_DATA(anime00328);
EXTERNAL_BMP_DATA(anime00332);
EXTERNAL_BMP_DATA(anime00336);
EXTERNAL_BMP_DATA(anime00340);
EXTERNAL_BMP_DATA(anime00344);
EXTERNAL_BMP_DATA(anime00348);
EXTERNAL_BMP_DATA(anime00352);
EXTERNAL_BMP_DATA(anime00356);
EXTERNAL_BMP_DATA(anime00360);
EXTERNAL_BMP_DATA(anime00364);
EXTERNAL_BMP_DATA(anime00368);
EXTERNAL_BMP_DATA(anime00372);
EXTERNAL_BMP_DATA(anime00376);
EXTERNAL_BMP_DATA(anime00380);
EXTERNAL_BMP_DATA(anime00384);
EXTERNAL_BMP_DATA(anime00388);
EXTERNAL_BMP_DATA(anime00392);
EXTERNAL_BMP_DATA(anime00396);
EXTERNAL_BMP_DATA(anime00400);
EXTERNAL_BMP_DATA(anime00404);
EXTERNAL_BMP_DATA(anime00408);
EXTERNAL_BMP_DATA(anime00412);
EXTERNAL_BMP_DATA(anime00416);
EXTERNAL_BMP_DATA(anime00420);
EXTERNAL_BMP_DATA(anime00424);
EXTERNAL_BMP_DATA(anime00428);
EXTERNAL_BMP_DATA(anime00432);
EXTERNAL_BMP_DATA(anime00436);
EXTERNAL_BMP_DATA(anime00440);
EXTERNAL_BMP_DATA(anime00444);
EXTERNAL_BMP_DATA(anime00448);
EXTERNAL_BMP_DATA(anime00452);
EXTERNAL_BMP_DATA(anime00456);
EXTERNAL_BMP_DATA(anime00460);
EXTERNAL_BMP_DATA(anime00464);

typedef struct
{
	const char *bmp;
	int width;
	int height;
	int x;
	int y;
} BMP_DATA;

const BMP_DATA bmp_table[] = {
	{ BMP_DATA_START(anime00000),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00004),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00008),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00012),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00016),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00020),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00024),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00028),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00032),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00036),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00040),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00044),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00048),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00052),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00056),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00060),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00064),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00068),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00072),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00076),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00080),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00084),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00088),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00092),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00096),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00100),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00104),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00108),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00112),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00116),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00120),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00124),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00128),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00132),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00136),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00140),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00144),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00148),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00152),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00156),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00160),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00164),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00168),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00172),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00176),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00180),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00184),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00188),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00192),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00196),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00200),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00204),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00208),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00212),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00216),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00220),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00224),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00228),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00232),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00236),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00240),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00244),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00248),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00252),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00256),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00260),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00264),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00268),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00272),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00276),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00280),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00284),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00288),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00292),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00296),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00300),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00304),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00308),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00312),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00316),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00320),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00324),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00328),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00332),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00336),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00340),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00344),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00348),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00352),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00356),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00360),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00364),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00368),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00372),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00376),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00380),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00384),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00388),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00392),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00396),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00400),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00404),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00408),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00412),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00416),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00420),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00424),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00428),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00432),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00436),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00440),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00444),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00448),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00452),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00456),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00460),  93, 63, 4, 0 },
	{ BMP_DATA_START(anime00464),  93, 63, 4, 0 }
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
				systick_wait_ms(200);
			}
		}
  	}

	TerminateTask();
}
