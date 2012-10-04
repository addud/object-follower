//
// Lcd.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "Lcd.h"
using namespace ecrobot;

//=============================================================================
// Constructor.
Lcd::Lcd(void)
:
mPosY(0)
{}

//=============================================================================
// Clear LCD
void Lcd::clear(bool lcdToo)
{
	mPosY = 0;
	display_goto_xy(0, mPosY);
	display_clear(static_cast<U32>(lcdToo));
}

//=============================================================================
// Clear LCD data buffer at the specified row position
bool Lcd::clearRow(U32 row, bool lcdToo)
{
	if (row > MAX_CURSOR_Y)
	{
		return false;
	}
	mPosY = row;
	display_goto_xy(0, mPosY);
	display_string("                ");
	if (lcdToo)
	{
		display_update();
	}
	return true;
}

//=============================================================================
// Set cursor to (x,y) position. Top left is (0,0).
void Lcd::cursor(U32 x, U32 y)
{
	x = (x>MAX_CURSOR_X)? MAX_CURSOR_X:x;
	y = (y>MAX_CURSOR_Y)? MAX_CURSOR_Y:y;
	mPosY = y;
	display_goto_xy(x, y);
}

//=============================================================================
// Put data into LCD buffer
bool Lcd::putf(const CHAR* format, ...)
{
	va_list argptr; // get args list
    va_start(argptr, format); // set the first argument

	while(*format != '\0')
	{
		switch(*format++)
		{
			case 's': // String
			{
				char* str = va_arg(argptr, char*);
				display_string(str);
				break;
			}
			case 'd': // Decimal integer value (value, places)
			{
				int dec = va_arg(argptr, int);
				int decPlaces = va_arg(argptr, int);
				display_int(dec, decPlaces);
				break;
			}
			case 'x': // Hex integer value (value, places)
			{
				unsigned int hex = static_cast<unsigned int>(va_arg(argptr, int));
				int hexPlaces = va_arg(argptr, int);
				display_hex(hex, hexPlaces);
				break;
			}
			case 'n':  // Line feed
			case '\n': // ASCII line feed
				mPosY++;
				mPosY = (mPosY>MAX_CURSOR_Y)? 0:mPosY;
				display_goto_xy(0, mPosY);
				break;

			case ' ': // Ignore the space
				break;

			default:
				// unexpected format
				va_end(argptr); // release argptr
				return false;
		}
	}

	va_end(argptr); // release args list
	return true;
}

//=============================================================================
// Draw monochrome bit map data to the LCD data buffer.
void Lcd::draw(const U8* data, U32 width, U32 depth, U32 xPosInWidth, U32 yPosInDepth)
{
	display_bitmap_copy(data, width, depth, xPosInWidth, yPosInDepth);
}

//=============================================================================
// Display data to LCD
void Lcd::disp(void)
{
	display_update();
}


