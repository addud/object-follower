//
// BmpFileDraw.cpp
//

#include <string.h>

#include "BmpFileDraw.h"


//=============================================================================
// Constructor
BmpFileDraw::BmpFileDraw(Lcd& lcd)
:
mrLcd(lcd)
{}

//=============================================================================
// Destructor
BmpFileDraw::~BmpFileDraw(void){}

//=============================================================================
// Draw a monochrome bmp file data to LCD data buffer.
bool BmpFileDraw::draw(const CHAR* bmp, U32 width, U32 height, U32 xPosInWidth, U32 yPosInDepth)
{
	memset(mBuf, 0x00, Lcd::MAX_LCD_WIDTH * Lcd::MAX_LCD_DEPTH); // flush buffer

	// Convert the bmp file format to the NXT LCD data alignment
	if (ecrobot_bmp2lcd(bmp, mBuf, width, height) == -1)
	{
		return false; // may be un-supported bmp file format
	}

	// Draw the converted bit map data to LCD data buffer
	mrLcd.draw(mBuf, Lcd::MAX_LCD_WIDTH, Lcd::MAX_LCD_DEPTH, xPosInWidth, yPosInDepth);

	return true;
}

