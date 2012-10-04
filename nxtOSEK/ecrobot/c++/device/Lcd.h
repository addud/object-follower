//
// Lcd.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef LCD_H_
#define LCD_H_


extern "C"
{
	#include <cstdarg>
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * Simple LCD display class.
 *
 * [ Example ]<BR>
 * &nbsp;&nbsp;Lcd lcd;<BR>
 * <BR>
 * &nbsp;&nbsp;lcd.clear();<BR>
 * &nbsp;&nbsp;lcd.putf("s", "Hello");<BR>
 * &nbsp;&nbsp;lcd.putf("s", "World");<BR>
 * &nbsp;&nbsp;lcd.disp();<BR>
 * &nbsp;&nbsp;"HelloWorld"<BR>
 * <BR>
 * &nbsp;&nbsp;lcd.clear();<BR>
 * &nbsp;&nbsp;lcd.putf("s\ns", "Hello", "World");<BR>
 * &nbsp;&nbsp;lcd.disp();<BR>
 * &nbsp;&nbsp;"Hello"<BR>
 * &nbsp;&nbsp;"World"<BR>
 * <BR>
 * &nbsp;&nbsp;lcd.clear();<BR>
 * &nbsp;&nbsp;lcd.putf("d", -10,0);<BR>
 * &nbsp;&nbsp;lcd.disp();<BR>
 * &nbsp;&nbsp;"-10"<BR>
 * <BR>
 * &nbsp;&nbsp;lcd.clear();<BR>
 * &nbsp;&nbsp;lcd.putf("x", 255,0);<BR>
 * &nbsp;&nbsp;lcd.disp();<BR>
 * &nbsp;&nbsp;"FF"<BR>
 * <BR>
 * &nbsp;&nbsp;lcd.clear();<BR>
 * &nbsp;&nbsp;lcd.putf("sddsx", "Calc: ", 16,0, -1,2, "=0x", (16-1),0);<BR>
 * &nbsp;&nbsp;lcd.disp();<BR>
 * &nbsp;&nbsp;"Calc: 16-1=0xF"
 */
class Lcd
{
public:
	/**
	 * Max cursor position in X(horizontal) axis.
	 */
	static const U32 MAX_CURSOR_X = 15;

	/**
	 * Max cursor position in Y(vertical) axis.
	 */
	static const U32 MAX_CURSOR_Y = 7;
	
	/**
	 * Max LCD width (1 width = 1 pixel)
	 */
	static const U32 MAX_LCD_WIDTH = 100;
	
	/**
	 * Max LCD depth (1 depth = 8 pixels)
	 */
	static const U32 MAX_LCD_DEPTH = 64/8;

	/**
	 * Constructor.
	 * @param -
	 * @return -
	 */
	Lcd(void);

	/**
	 * Set cursor to (x,y) position. Top left is (0,0).
	 * @param x Cusor position in X(horizontal) axis.
	 * @param y Cusor position in Y(vertical) axis.
	 */
	void cursor(U32 x, U32 y);

	/**
	 * Clear LCD data buffer and reset cursor position to (0,0).
	 * @param lcdToo Clear LCD display too.
	 * @return -
	 */
	void clear(bool lcdToo=false);

	/**
	 * Clear LCD data buffer at the specified row.
	 * @param row LCD row position to be cleared
	 * @param lcdToo Clear LCD display too.
	 * @return true:succeeded/false:failed
	 */
	bool clearRow(U32 row, bool lcdToo=false);

	/**
	 * Put output to the LCD data buffer, according to format and other arguments passed to putf().
	 * @param format Output format string.<BR>
	 * "s":  String format.<BR>
	 * "d":  Decimal integer format. This format requires two arguments (arg1: value, arg2: spaces to be held).<BR>
	 * "x":  Hex integer format. This format requires two arguments (arg1: value, arg2: spaces to be held).<BR>
	 * "n":  Line feed format. Cursor position in X(horizontal) axis is set to 0.<BR>
	 * "\n": ASCII line feed format. Cursor position in X(horizontal) axis is set to 0.
	 * @return true:succeeded/false:failed(might be due to invalid format)
	 */
	bool putf(const CHAR* format, ...);

	/**
	 * Draw monochrome bit map data to the LCD data buffer.
	 * @param data Monochrome bit map data which is adapted to NXT LCD data alignment
	 * @param width Width of bit map data
	 * @param depth Depth of bit map data
	 * @param xPosInWidth X axis position of bit map data in the width unit (= 1 pixel)
	 * @param yPosInDepth Y axis position of bit map data in the depth unit (= 8 pixels)
	 */
	void draw(const U8* data, U32 width, U32 depth, U32 xPosInWidth, U32 yPosInDepth);

	/**
	 * Display data in the LCD data buffer to the LCD.
	 * Note that LCD display takes minimun 16msec due to hardware, so frequent executions
	 * of this member function makes the system busy.
	 * @param -
	 * @return -
	 */
	void disp(void);

private:
	U32 mPosY;
};
}


#endif
