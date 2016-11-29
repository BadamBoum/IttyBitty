/***********************************************************************************************
* [IttyBitty_LCD_extensions_big.h]: ADDED SUPPORT FOR LARGE (TWO-ROW, MULTI-COLUMN)
*	CHARACTER PRINTING ON I2C-DRIVEN HD44780-COMPATIBLE LCD DISPLAYS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_LCD_EXTENSIONS_BIG_H
#define _ITTYBITTY_LCD_EXTENSIONS_BIG_H


#include "IttyBitty_aliases.h"


#pragma region DEFINES

#define BF_NOT_SUPPORTED 0
#define BF_WIDTH1_TABLE 0x01
#define BF_WIDTH2_TABLE 0x02
#define BF_WIDTH3_TABLE 0x03
#define BF_WIDTH4_TABLE 0x04
#define BF_WIDTH5_TABLE 0x05
#define BF_WIDTH3_SYMBOLS_TABLE 0x06

#pragma endregion


namespace IttyBitty
{
#pragma region LCD BIG FONT FLASH DATA TABLE DECLARATIONS

	EXTERN PROGMEM CBYTE LCD_BIG_FONT_SHAPES[64];
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_CHARACTERS[59];
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_WIDTH1[18];
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_WIDTH2[8];
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_WIDTH3[180];
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_WIDTH3_SYMBOLS[18];
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_WIDTH4[24];
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_WIDTH5[20];

#pragma endregion
};

#endif
