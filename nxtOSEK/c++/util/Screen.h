#ifndef _SCREEN_H_
#define _SCREEN_H_

#ifndef _MSC_VER
extern "C" {
#include "ecrobot_interface.h"
#include "kernel.h"
#include "nxt_avr.h"
#include "nxtAssert.h"
#include "string.h"
};
#else
	#include "Defines.h"
	#include <string.h>
	#include "Stub.h"
	#include "types.h"
#endif

#include "Sprite.h"

#define NUM_SPRITES 10

class Screen
{
public:
	Screen();
	void update();

	Sprite* newSprite(Sprite *sprite);
	void deleteSprite(Sprite *sprite);
	static void renderBitmap(U8 *lcd, const CHAR *file, S32 width, S32 height, S32 xPos, S32 yPos, bool invert, bool hflip, bool vflip);
	static void renderBitmapPC(U8 *lcd, const CHAR *file, S32 width, S32 height, S32 xPos, S32 yPos, bool invert, bool hflip, bool vflip);

private:

	U8 mLcd[NXT_LCD_DEPTH*NXT_LCD_WIDTH];
	Sprite *mSpriteList[NUM_SPRITES];
};

#endif

