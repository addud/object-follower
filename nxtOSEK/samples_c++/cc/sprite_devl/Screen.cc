#include "Screen.h"

#ifdef _MSC_VER
#include <assert.h>
#else
extern "C"
{
	#include "systick.h"
}
#endif

Screen::Screen()
{
	memset(mLcd, 0x00, NXT_LCD_DEPTH*NXT_LCD_WIDTH);
	for(int i = 0; i < NUM_SPRITES; ++i)
	{
		mSpriteList[i] = NULL;
	}
}

void Screen::update()
{
	memset(mLcd, 0x00, NXT_LCD_DEPTH*NXT_LCD_WIDTH);
	for(int i = 0; i < NUM_SPRITES; ++i)
	{
		if(mSpriteList[i])
		{
			if(mSpriteList[i]->frameIsRenderable())
			{
				renderBitmap(	mLcd, 
								mSpriteList[i]->getCurrentFramePtr(), 
								mSpriteList[i]->getWidth(), 
								mSpriteList[i]->getHeight(), 
								mSpriteList[i]->getPosition().mX, 
								mSpriteList[i]->getPosition().mY, 
								mSpriteList[i]->getInvert(), 
								mSpriteList[i]->getHFlip(), 
								mSpriteList[i]->getVFlip());
			}
			
			mSpriteList[i]->update();
		}
	}
#ifndef _MSC_VER
	// Display update of NXT LCD takes 16msec according LEGO HW development kit. 
	// Thus faster refresh rate(update) than 16msec does not work. 
	// Actually it makes the system busy by frequest ISR requests and 
	// it may cause a system crash. Then it needs to insert 20msec (> 16msec) wait.
	systick_wait_ms(20);
#endif
	display_bitmap_copy(mLcd, NXT_LCD_WIDTH, NXT_LCD_DEPTH, 0, 0);
	display_update();
}

Sprite* Screen::newSprite(Sprite *sprite)
{
	for(int i = 0; i < NUM_SPRITES; ++i)
	{
		if(mSpriteList[i] == NULL)
		{
			mSpriteList[i] = sprite;
			return sprite;
		}
	}

	return sprite;
}

void Screen::deleteSprite(Sprite *sprite)
{
	for(int i = 0; i < NUM_SPRITES; ++i)
	{
		if(mSpriteList[i] == sprite)
		{
			mSpriteList[i] = NULL;
			return;
		}
	}
}
#ifdef _MSC_VER
void Screen::renderBitmap(U8 *lcd, const CHAR *sprite, S32 width, S32 height, S32 xPos, S32 yPos, bool invert, bool hflip, bool vflip)
{
    int spriteByteWidth = width/8;
    int currentSpriteByte = 0;
    int spriteRow = 0;

    for (int y = 0; y < height; ++y)
    {
        if(vflip == true)
        {
            spriteRow = height - 1 - y;
        }
        else
        {
            spriteRow = y;
        }

        if (spriteRow + yPos < 0 || spriteRow + yPos > 63)
        {
            currentSpriteByte += spriteByteWidth;
            continue;
        }

        int spriteCol = 0;
        for (int x = 0; x < spriteByteWidth; x++)
        {
            if (hflip == true)
            {
                spriteCol = spriteByteWidth - 1 - x;
            }
            else
            {
                spriteCol = x;
            }

            unsigned char workByte = sprite[currentSpriteByte++];

            if(invert)
	        {
                workByte ^= 0xff;
	        }

            int spritePixelOffset = (spriteCol * 8) + xPos;
            
            int lcdPixelOffset = ((spriteRow + yPos) * 100) + spritePixelOffset;
            int pixelShift = 0;
            for (int px = 0; px < 8; ++px)
            {
                if (hflip == true)
                {
                    pixelShift = px;
                }
                else
                {
                    pixelShift = 7 - px;
                }

                if (spritePixelOffset + px < 0 || spritePixelOffset + px > 99)
                {
                    continue;
                }

                if (workByte > 0)
                {
                    int lcdBytePos = (lcdPixelOffset + px) / 8;
                    int lcdBitPos = (lcdPixelOffset + px) % 8;

                    if ((workByte & (1 << pixelShift)) == (1 << pixelShift))
                    {
                        lcd[lcdBytePos] |= (char)(1 << lcdBitPos);
                    }
                }
            }
        }
    }
}
#else
void Screen::renderBitmap(U8 *lcd, const CHAR *file, S32 width, S32 height, S32 xPos, S32 yPos, bool invert, bool hflip, bool vflip)
{	
	SINT bmp_line = width / 8;
	if (width % 8)
	{
		bmp_line++;
	}

	//iterate through each row of the bitmap
	for (SINT bmp_row = 0; bmp_row < height; bmp_row++)
	{
		//if the position of any row puts it off screen, the don' render it
		if(bmp_row + yPos < 0 || bmp_row + yPos > 63)
		{
			continue;
		}

		//setup the pixel position on the lcd to render
		SINT lcd_row = (bmp_row + yPos) / 8;
		SINT lcd_bit_pos = 7 - ((bmp_row + yPos) % 8);

		//iterate through each column
		for(SINT bmp_col = 0; bmp_col < bmp_line ; bmp_col++)
		{
			//vflip if nevessary
			U8 row = bmp_row;

			if(vflip)
			{
				row = (height - bmp_row);
			}

			//hflp if necessary
			SINT renderColumn = bmp_col;

			if(hflip)
			{
				renderColumn = bmp_line - bmp_col;
			}

			//get the byte to render
			U8 bmp_data = file[(row * bmp_line) + bmp_col];

			//invert the bits if necessary
			if(invert)
			{
				bmp_data ^= 0xff;
			}

			//get the position on the lcd to render
			SINT lcd_pos = (lcd_row * NXT_LCD_WIDTH) + ((renderColumn * 8) + xPos);

			//now iterate through each bit in the render byte
			for (SINT bmp_bit_pos = 0; bmp_bit_pos < 8; bmp_bit_pos++)
			{

				//hflip the renderbytes bits if necessary
				U8 bitToDraw = (7 - bmp_bit_pos);

				if(hflip)
				{
					bitToDraw = bmp_bit_pos;
				}

				//if ever a bit is off screen, don't render it
				if((renderColumn * 8) + xPos + bitToDraw < 0 || 
					(renderColumn * 8) + xPos + bitToDraw  > 99)
				{
					continue;
				}

				//finally, render the pixel
				if (bmp_data & (0x01 << bitToDraw))
				{
					SINT lcd_index = lcd_pos + bmp_bit_pos;
					// checks the size of render data to be stored into LCD
					if (lcd_index < NXT_LCD_DEPTH*NXT_LCD_WIDTH)
					{
						lcd[lcd_index] |= (0x80 >> lcd_bit_pos);
					}
				}
				/*else
				{
					//if the bitmap pixel is clear and we're not rendering transparently,
					//clear this pixel location on the lcd
					if(!transparent)
					{
						lcd[lcd_pos + bmp_bit_pos] &= (~0x80 >> lcd_bit_pos);
					}
				}*/
			}
		}
	}
}
#endif

