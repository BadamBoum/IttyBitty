/***********************************************************************************************
* [IttyBitty_LCD_chars.h]: VALUE-ADDED SYMBOLS & ICONS FOR HD44780-COMPATIBLE LCD DISPLAYS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_LCD_CHARS_H
#define _ITTYBITTY_LCD_CHARS_H


#include "IttyBitty_util.h"


#pragma region DEFINES

// LCD SYMBOL CHARACTERS

// ARROWS
#define LCD_SYMBOL_SCROLL_RIGHT			0x10
#define LCD_SYMBOL_SCROLL_LEFT			0x11
#define LCD_SYMBOL_DOUBLE_ARROW_UP		0x15
#define LCD_SYMBOL_DOUBLE_ARROW_DOWN	0x16
#define LCD_SYMBOL_SPLIT_CIRCLE			0x17
#define LCD_SYMBOL_ARROW_RETURN			0x18
#define LCD_SYMBOL_ARROW_UP				0x19
#define LCD_SYMBOL_ARROW_DOWN			0x1A
#define LCD_SYMBOL_ARROW_RIGHT			0x1A
#define LCD_SYMBOL_ARROW_LEFT			0x1B
#define LCD_SYMBOL_SCROLL_UP			0x1E
#define LCD_SYMBOL_SCROLL_DOWN			0x1F

// MISCELLANEOUS
#define LCD_SYMBOL_BLANK				0x20
#define LCD_SYMBOL_TRIANGLE				0x0E
#define LCD_SYMBOL_HOUSE				0x7F
#define LCD_SYMBOL_NOTE					0x91
#define LCD_SYMBOL_BELL					0x98
#define LCD_SYMBOL_HEART				0x9D
#define LCD_SYMBOL_COPYRIGHT			0xA9
#define LCD_SYMBOL_RESERVED				0xAE

#pragma endregion


namespace IttyBitty
{
#pragma region CUSTOM LCD CHARACTER FLASH CONSTANT DECLARATIONS

	// Miscellaneous symbols
	EXTERN PROGMEM CBYTE LCD_CHAR_SLIDER_END_LEFT[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SLIDER_END_RIGHT[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_CHECKMARK[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_BOX_EMPTY[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_BOX_CHECKMARK[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_WARNING[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_NOT_ALLOWED[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_LIGHTNING[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_NOTES[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_CLOCK_A[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_CLOCK_B[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_HOURGLASS_1[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_HOURGLASS_2[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_HOURGLASS_3[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_HOURGLASS_4[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_ANGLE[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_ANGLE_2[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_CLOCKWISE[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_COUNTER_CCW[8];


	// Shape (outline) icons
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_CIRCLE[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_ROUND[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_OVAL[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_CUSHION[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_SQUARE[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_DIAMOND[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_BAGUETTE[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_EMERALD[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_TRILLIANT[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_TRIANGLE[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_SHAPE_SPECIAL[8];


	// Small arrow icons
	EXTERN PROGMEM CBYTE LCD_CHAR_ARROW_UP_SMALL[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_ARROW_DOWN_SMALL[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_ARROW_LEFT_SMALL[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_ARROW_RIGHT_SMALL[8];

	// Medium arrow icons
	EXTERN PROGMEM CBYTE LCD_CHAR_ARROW_UP[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_ARROW_DOWN[8];

	// Large arrow icons
	EXTERN PROGMEM CBYTE LCD_CHAR_ARROW_LEFT_LARGE[8];
	EXTERN PROGMEM CBYTE LCD_CHAR_ARROW_RIGHT_LARGE[8];

#pragma endregion
};

#endif
