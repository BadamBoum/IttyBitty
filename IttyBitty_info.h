/**********************************************************************************
* [IttyBitty_info.h]: UTILITY FUNCTIONS RELATED TO BOARD SPECS & MEMORY USAGE
*
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#ifndef _ITTYBITTY_INFO_H
#define _ITTYBITTY_INFO_H


#include <avr/eeprom.h>

#ifndef _AVR_CPU_NAME_
#include "avr_cpunames.h"
#endif

#include "IttyBitty_util.h"


/* GENERAL CPU & ARDUINO INFO FUNCTIONS */

CONSTEXPR PCCHAR CPUType()
{
	return _AVR_CPU_NAME_;
}


/* MEMORY AREA/ALLOCATION VARIABLES & FUNCTIONS */

EXTERN PCHAR __data_start;
EXTERN PCHAR __data_end;
EXTERN PCHAR __bss_start;
EXTERN PCHAR __bss_end;
EXTERN PCHAR __heap_start;
EXTERN PCHAR __heap_end;

EXTERN PTR __brkval;

EXTERN PCHAR _etext;
EXTERN PCHAR _edata;

EXTERN PCHAR __malloc_heap_start;
EXTERN PCHAR __malloc_heap_end;
EXTERN SIZE __malloc_margin;


INLINE PVUINT StackPointer()
{
	return &static_cast<RVUINT>(SP);
}

INLINE CWORD StackSpaceTotal()
{
	WORD stackEnd = reinterpret_cast<WORD>(__heap_end);

	if (stackEnd > RAMEND)
		stackEnd = reinterpret_cast<WORD>(__bss_end);

	return static_cast<CWORD>(RAMEND + 1 - stackEnd - __malloc_margin);
}

INLINE CWORD StackSpaceUsed()
{
	return static_cast<CWORD>(RAMEND) + 1 - reinterpret_cast<CWORD>(StackPointer());
}

INLINE CWORD StackSpaceAvailable()
{
	return StackSpaceTotal() - reinterpret_cast<WORD>(StackPointer());
}

INLINE PCHAR HeapPointer()
{
	if (reinterpret_cast<WORD>(__brkval) == 0)
		return __heap_start;

	return reinterpret_cast<PCHAR>(__brkval);
}

INLINE CWORD HeapSpaceTotal()
{
	return reinterpret_cast<CWORD>(__heap_end) - reinterpret_cast<CWORD>(__heap_start);
}

INLINE CWORD HeapSpaceUsed()
{
	return reinterpret_cast<CWORD>(HeapPointer()) - reinterpret_cast<CWORD>(__heap_start);
}

INLINE CWORD HeapSpaceAvailable()
{
	return reinterpret_cast<CWORD>(__heap_end) - reinterpret_cast<CWORD>(HeapPointer());
}

CONSTEXPR CWORD SRAMTotalSize()
{
	return static_cast<CWORD>(RAMEND) + 1 - static_cast<CWORD>(RAMSTART);
}

INLINE CWORD SRAMUsed()
{
#ifdef XRAMSTART
	if (reinterpret_cast<WORD>(__heap_start) > RAMEND)
		return StackSpaceUsed();
#endif

	return StackSpaceUsed() + HeapSpaceUsed();
}

INLINE CWORD SRAMAvailable()
{
#ifdef XRAMSTART
	if (reinterpret_cast<WORD>(__heap_start) > RAMEND)
		return StackSpaceAvailable();
#endif

	return StackSpaceAvailable() + HeapSpaceAvailable();
}

CONSTEXPR WORD XRAMTotalSize()
{
	return static_cast<CWORD>(XRAMSIZE);
}


#ifdef XRAMSTART

INLINE WORD XRAMUsed()
{
	WORD stackEnd = reinterpret_cast<WORD>(__heap_end);

	if (stackEnd > RAMEND)
		stackEnd = reinterpret_cast<WORD>(__bss_end);

	return static_cast<CWORD>(static_cast<WORD>(RAMEND) + 1 - stackEnd - __malloc_margin);
}

INLINE CWORD XRAMAvailable()
{
	return XRAMTotalSize() - XRAMUsed();
}

INLINE CWORD TotalRAMUsed()
{
	return SRAMUsed() + XRAMUsed();
}

INLINE CWORD TotalRAMAvailable()
{
	return SRAMAvailable() + XRAMAvailable();
}

#else	// #ifndef XRAMSTART

INLINE CWORD TotalRAMUsed()
{
	return SRAMUsed();
}

INLINE CWORD TotalRAMAvailable()
{
	return SRAMAvailable();
}

#endif	// #ifdef XRAMSTART


CONSTEXPR CWORD TotalRAMSize()
{
	return SRAMTotalSize() + XRAMTotalSize();
}

#define ROM_USED_DETECTION_TOLERANCE_DWORDS 4

template<typename T = WORD, typename P = T>
CONST T ROMUsed(DWORD (&rom_read_dword)(P), CWORD romSize)
{
	T lastUsedAddr = 0x0;
	DWORD value = 0;
	BYTE consecutiveBlanks = 0;

	for (lastUsedAddr = 0x0; lastUsedAddr < romSize; lastUsedAddr++)
	{
		value = rom_read_dword(reinterpret_cast<P>(lastUsedAddr));

		if (value == 0xFFFFFFFF)
		{
			if (++consecutiveBlanks == ROM_USED_DETECTION_TOLERANCE_DWORDS)
				break;
		}
		else
		{
			consecutiveBlanks = 0;
		}
	}

	return static_cast<CONST T>(lastUsedAddr + 1);
}

CONSTEXPR CWORD FlashTotalSize()
{	
	return static_cast<CWORD>(FLASHEND) + 1;
}

INLINE DWORD __pgm_read_dword(WORD dwordPtr)
{
	return pgm_read_dword(dwordPtr);
}

INLINE CWORD FlashUsed()
{
	//return ROMUsed<>(__pgm_read_dword, FlashTotalSize());
	WORD textAndDataSize = reinterpret_cast<WORD>(&_etext) + reinterpret_cast<WORD>(&_edata);

	#ifdef SPMPAGESIZE
		STATIC CONST CWORD FLASH_PAGE_SIZE = SPM_PAGESIZE;
	#else
		STATIC CONST CWORD FLASH_PAGE_SIZE = SPM_PAGESIZE;
	#endif

	return static_cast<CWORD>(textAndDataSize) + FLASH_PAGE_SIZE;
}

INLINE CWORD FlashAvailable()
{
	return FlashTotalSize() - FlashUsed();
}

CONSTEXPR CWORD (*ProgMemTotalSize)() = &FlashTotalSize;
CONSTEXPR CWORD (*SketchSize)() = &FlashUsed;

CONSTEXPR CDWORD EEPROMTotalSize()
{
#if E2END == 0
	return 0;
#else
	return static_cast<CWORD>(E2END) + 1;
#endif
}

INLINE CDWORD EEPROMUsed()
{
#if E2END == 0
	return 0;
#else	
	return ROMUsed<DWORD, PCDWORD>(eeprom_read_dword, EEPROMTotalSize());
#endif
}

INLINE CDWORD EEPROMAvailable()
{
#if E2END == 0
	return 0;
#else	
	return EEPROMTotalSize() - EEPROMUsed();
#endif
}


#endif