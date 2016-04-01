/*******************************************************************************
* Name:		IttyBitty Library
* Created:	3/20/2016
* Author:	Tom Biuso <tjbtech@yahoo.com>
*
* Copyright � 2016 Thomas J. Biuso III ALL RIGHTS RESERVED.
*******************************************************************************/

#ifndef _ITTYBITTY_
#define _ITTYBITTY_ "FTW"


/* LIBRARY BASE: BASIC UTILITY HELPERS & BIT MANIPULATION MACROS 
*
* [IttyBitty_aliases.h]: TYPEDEFS FOR WIN32 API-STYLE TYPE REFERENCES
* [IttyBitty_type_traits.h]: METAFUNCTIONS FOR TEMPLATED TYPING GOODNESS
* [IttyBitty_util.h]: MISCELLANEOUS HELPER MACROS, ETC.
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register management for ATmegas */

//#include "IttyBitty_aliases.h"		// Included by [IttyBitty_type_traits.h]
//#include "IttyBitty_type_traits.h"	// Included by [IttyBitty_util.h]
//#include "IttyBitty_util.h"			// Included by [IttyBitty_bits.h]
#include "IttyBitty_bits.h"


/* NOTE: DEFINE [ITTYBITTY_SLIM] TO INCLUDE ONLY THE BARE MINIMUM, SUCH AS BIT-TWIDDLING MACROS */

#ifdef ITTYBITTY_SLIM
	#define ITTYBITTY_BASE_ONLY
	#define EXCLUDE_ITTYBITTY_BYTES
#endif


/* NOTE: DEFINE [ITTY_BITTY_BASE_ONLY] TO EXCLUDE (MORE RESOURCE-DEMANDING) FULL-FEATURED FUNCTIONALITY */

#ifdef ITTYBITTY_BASE_ONLY
	#define EXCLUDE_ITTYBITTY_REGISTERS
#endif


/* [IttyBitty_bytes.h]: DATA STRUCTURES FOR BIT-PACKING BYTES, WORDS, DWORDS, ... */

#ifndef EXCLUDE_ITTYBITTY_BYTES
	#include "IttyBitty_bytes.h"
#else
	#define EXCLUDE_ITTYBITTY_REGISTERS
	#define EXCLUDE_ITTYBITTY_GPIO
	#define EXCLUDE_ITTYBITTY_INTERRUPTS
#endif


/* [IttyBitty_registers.h]: REGISTER ABSTRACTIONS FOR CONVENIENCE AND CLARITY */

#ifndef EXCLUDE_ITTYBITTY_REGISTERS
	#include "IttyBitty_registers.h"
#else
	#define EXCLUDE_ITTYBITTY_GPIO
	#define EXCLUDE_ITTYBITTY_INTERRUPTS
#endif


/* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS */

#ifndef EXCLUDE_ITTYBITTY_GPIO
	#include "IttyBitty_gpio.h"
#else
	#define EXCLUDE_ITTYBITTY_LED
#endif


/* [IttyBitty_interrupts.h]:  */

#ifndef EXCLUDE_ITTYBITTY_INTERRUPTS
	#include "IttyBitty_interrupts.h"
#else
	#define EXCLUDE_ITTYBITTY_LED
#endif


/* [IttyBitty_led.h]: DATA TYPE FOR DEAD-EASY ON-BOARD & EXTERNAL LED BLINKING */

#ifndef EXCLUDE_ITTYBITTY_LED
	#include "IttyBitty_led.h"
#endif


#endif
