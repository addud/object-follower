//
// BmpFileDraw.h
//

#ifndef BMPFILEDRAW_H_
#define BMPFILEDRAW_H_

#include "Lcd.h"
using namespace ecrobot;

class BmpFileDraw
{
private:
	Lcd& mrLcd;
	U8 mBuf[Lcd::MAX_LCD_WIDTH * Lcd::MAX_LCD_DEPTH];

public:
	/**
	 * Constructor.
	 * @param lcd Reference of an Lcd object
	 * @return -
	 */
	BmpFileDraw(Lcd& lcd);

	/**
	 * Destructor.
	 * @param -
	 * @return -
	 */
	~BmpFileDraw(void);

	/**
	 * Draw a monochrome bmp file data to LCD data buffer.
	 * @param bmp Monochrome bmp file
	 * @param width Width of bmp file data in pixel
	 * @param height Height of bmp file data in pixel
	 * @param xPosInWidth X axis position of bit map data in the width unit (= 1 pixel)
	 * @param yPosInDepth Y axis position of bit map data in the depth unit (= 8 pixels)
	 * @return The result of draw (true:succeeded/false:failed)
	 */
	bool draw(const CHAR* bmp, U32 width, U32 height, U32 xPosInWidth, U32 yPosInDepth);
};

#endif
