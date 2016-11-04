/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

/* NOTE: COMMENT THE FOLLOWING LINE OUT TO ENABLE A FULLY FEATURED / FULL BUILD OF THE LIBRARY */
//#define ITTYBITTY_SLIM

#if defined(ITTYBITTY_SLIM) && !defined(EXCLUDE_ITTYBITTY_BYTES)
	#define EXCLUDE_ITTYBITTY_BYTES
#endif

#ifndef EXCLUDE_ITTYBITTY_GPIO


#include "IttyBitty_GPIO.h"

using namespace IttyBitty;


#ifdef ARDUINO

PVBYTE ARDUINO_PORT_TO_MODE[NUM_PORTS];
PVBYTE ARDUINO_PORT_TO_OUTPUT[NUM_PORTS];
PVBYTE ARDUINO_PORT_TO_INPUT[NUM_PORTS];

BYTE ARDUINO_PIN_TO_PORT[NUM_DIGITAL_PINS];
BYTE ARDUINO_PIN_TO_MASK[NUM_DIGITAL_PINS];


namespace IttyBitty
{
	// ARDUINO PIN GLOBAL FUNCTIONS

	PinMode GetPinMode(PIN_NUMBER p)
	{
		return GET_ARDUINO_PIN_MODE(p);
	}

	VOID SetPinMode(PIN_NUMBER p, PinMode mode)
	{
		SET_ARDUINO_PIN_MODE(p, mode);
	}

	VOID SetPinMode(PIN_NUMBER p, PinModeBasic basicMode)
	{
		SET_ARDUINO_PIN_MODE(p, basicMode);
	}

	VOID SetPinMode(PIN_NUMBER p, RCBYTE arduinoMode)
	{
		SET_ARDUINO_PIN_MODE(p, arduinoMode);
	}

	CBIT CheckPinSet(PIN_NUMBER p)
	{
		return CHECK_ARDUINO_PIN_SET(p);
	}
	
	CBIT (*ReadPin)(PIN_NUMBER) = &CheckPinSet;
	CBIT (*CheckPin)(PIN_NUMBER) = &CheckPinSet;

	CBIT CheckPinUnset(PIN_NUMBER p)
	{
		return CHECK_ARDUINO_PIN_UNSET(p);
	}
	
	VOID WritePin(PIN_NUMBER p, RCBIT state)
	{
		WRITE_ARDUINO_PIN(p, state);
	}

	VOID SetPin(PIN_NUMBER p)
	{
		SET_ARDUINO_PIN(p);
	}

	VOID ClearPin(PIN_NUMBER p)
	{
		CLEAR_ARDUINO_PIN(p);
	}

	VOID TogglePin(PIN_NUMBER p)
	{
		TOGGLE_ARDUINO_PIN(p);
	}
		
	VOID ResetPin(PIN_NUMBER p)
	{
		RESET_ARDUINO_PIN(p);
	}
};

#endif	// #ifdef ARDUINO


#ifndef EXCLUDE_ITTYBITTY_BYTES

	#define _INITIALIZE_PORT_STRUCTS(port_letter)	\
		RBITPACK P##port_letter##_DDR	= *(PACK_BYTE_REF((RVBYTE)DDR##port_letter));	\
		RBITPACK P##port_letter##_PORT	= *(PACK_BYTE_REF((RVBYTE)PORT##port_letter));	\
		RBITPACK P##port_letter##_PIN	= *(PACK_BYTE_REF((RVBYTE)PIN##port_letter));	\
		REG8 DDR##port_letter##_REG(&DDR##port_letter);									\
		REG8 PORT##port_letter##_REG(&PORT##port_letter);								\
		REG8 PIN##port_letter##_REG(&PIN##port_letter);									\
		PORT Port##port_letter(DDR##port_letter##_REG, PORT##port_letter##_REG, PIN##port_letter##_REG);

#else	// #ifdef EXCLUDE_ITTYBITTY_BYTES

	#define _INITIALIZE_PORT_STRUCTS(port_letter)	\
		RBITPACK P##port_letter##_DDR	= *(PACK_BYTE_REF((RVBYTE)DDR##port_letter));	\
		RBITPACK P##port_letter##_PORT	= *(PACK_BYTE_REF((RVBYTE)PORT##port_letter));	\
		RBITPACK P##port_letter##_PIN	= *(PACK_BYTE_REF((RVBYTE)PIN##port_letter));	\

#endif	// #ifndef EXCLUDE_ITTYBITTY_BYTES


#ifdef PORTA
	_INITIALIZE_PORT_STRUCTS(A)
#endif

#ifdef PORTB
	_INITIALIZE_PORT_STRUCTS(B)
#endif

#ifdef PORTC
	_INITIALIZE_PORT_STRUCTS(C)
#endif

#ifdef PORTD
	_INITIALIZE_PORT_STRUCTS(D)
#endif

#ifdef PORTE
	_INITIALIZE_PORT_STRUCTS(E)
#endif

#ifdef PORTF
	_INITIALIZE_PORT_STRUCTS(F)
#endif

#ifdef PORTG
	_INITIALIZE_PORT_STRUCTS(G)
#endif

#ifdef PORTH
	_INITIALIZE_PORT_STRUCTS(H)
#endif

#ifdef PORTJ
	_INITIALIZE_PORT_STRUCTS(J)
#endif

#ifdef PORTK
	_INITIALIZE_PORT_STRUCTS(K)
#endif

#ifdef PORTL
	_INITIALIZE_PORT_STRUCTS(L)
#endif


#ifndef EXCLUDE_ITTYBITTY_BYTES

	#define _GPIO_INITIALIZE_PORT(port_letter) RPORT GPIO::P##port_letter = Port##port_letter;

	#ifdef PORTA
		_GPIO_INITIALIZE_PORT(A)
	#endif

	#ifdef PORTB
		_GPIO_INITIALIZE_PORT(B)
	#endif

	#ifdef PORTC
		_GPIO_INITIALIZE_PORT(C)
	#endif

	#ifdef PORTD
		_GPIO_INITIALIZE_PORT(D)
	#endif

	#ifdef PORTE
		_GPIO_INITIALIZE_PORT(E)
	#endif

	#ifdef PORTF
		_GPIO_INITIALIZE_PORT(F)
	#endif

	#ifdef PORTG
		_GPIO_INITIALIZE_PORT(G)
	#endif

	#ifdef PORTH
		_GPIO_INITIALIZE_PORT(H)
	#endif

	#ifdef PORTJ
		_GPIO_INITIALIZE_PORT(J)
	#endif

	#ifdef PORTK
		_GPIO_INITIALIZE_PORT(K)
	#endif

	#ifdef PORTL
		_GPIO_INITIALIZE_PORT(L)
	#endif

#endif	// #ifndef EXCLUDE_ITTYBITTY_BYTES

#endif	// #ifndef EXCLUDE_ITTYBITTY_GPIO
