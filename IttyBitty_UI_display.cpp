/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_MENUI
#endif

#ifndef NO_ITTYBITTY_MENUI

#include "IttyBitty_expressions.h"
#include "IttyBitty_UI_display.h"

using namespace IttyBitty;


#pragma region [UiRendererBase] IMPLEMENTATION

// [IUiRenderer] (NON-)IMPLEMENTATION

CBYTE UiRendererBase::Cols() const { return MAX_BYTE; }

CBYTE UiRendererBase::Rows() const { return MAX_BYTE; }

CBOOL UiRendererBase::IsLineWrapEnabled() const { return FALSE; }

VOID UiRendererBase::SetLineWrap(CBOOL) { }

VOID UiRendererBase::CursorOff() { }

VOID UiRendererBase::CursorBlinkOn() { }

VOID UiRendererBase::CursorBlinkOff() { }

CBOOL UiRendererBase::Available() { return TRUE; }

VOID UiRendererBase::Flush() { }

VOID UiRendererBase::Clear() { }

VOID UiRendererBase::ClearCol(CBYTE) { }

VOID UiRendererBase::ClearRow(CBYTE) { }

VOID UiRendererBase::ScrollLeft() { }

VOID UiRendererBase::ScrollRight() { }

VOID UiRendererBase::Home() { }

VOID UiRendererBase::CursorPrev() { }

VOID UiRendererBase::CursorNext() { }

VOID UiRendererBase::MoveCursor(CBYTE, CBYTE) { }

VOID UiRendererBase::LoadCustomChar(BYTE charIndex, PCBYTE charData) { }

VOID UiRendererBase::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr) { }

CBYTE UiRendererBase::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
	return (BYTE)this->write(value);
}

#ifndef NO_ITTYBITTY_EXTENSIONS

VOID UiRendererBase::DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS) { }

VOID UiRendererBase::DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS) { }

VOID UiRendererBase::DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL) { }

#endif

#pragma endregion


#pragma region [UiDisplayController] IMPLEMENTATION

UiDisplayController::UiDisplayController(CBYTE rendererCount, PPIUIRENDERER renderers)
	: _RendererCount(rendererCount), _Renderers(renderers) { }

UiDisplayController::UiDisplayController(RIUIRENDERER renderer) : _RendererCount(1)
{
	_Renderers = new PIUIRENDERER[1];
	_Renderers[0] = &renderer;
}

UiDisplayController::~UiDisplayController()
{
	if (_Renderers)
	{
		for (BYTE i = 0; i < _RendererCount; i++)
		{
			if (_Renderers[i])
			{
				delete _Renderers[i];
				_Renderers[i] = NULL;
			}
		}

		delete _Renderers;
		_Renderers = NULL;

		_RendererCount = 0;
	}
}


// OPERATORS

PCIUIRENDERER UiDisplayController::operator[](CBYTE i) const
{
	if (!_Renderers)
		return NULL;

	return _Renderers[i];
}

PIUIRENDERER UiDisplayController::operator[](CBYTE i)
{
	if (!_Renderers)
		return NULL;

	return _Renderers[i];
}


// ACCESSORS

CBYTE UiDisplayController::RendererCount() const
{
	return _RendererCount;
}

RCIUIRENDERER UiDisplayController::Renderer(CBYTE i) const
{
	return *this->operator[](i);
}

RIUIRENDERER UiDisplayController::Renderer(CBYTE i)
{
	return *this->operator[](i);
}


// [Print] IMPLEMENTATION

SIZE UiDisplayController::write(BYTE)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintString_P, flashStr, col, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return 0;
}

SIZE UiDisplayController::write(PCBYTE buffer, SIZE size)
{

	return 0;
}


// [Print] OVERRIDES

SIZE UiDisplayController::print(FLASH_STRING)
{

	return 0;
}

SIZE UiDisplayController::print(CONST String &)
{

	return 0;
}

SIZE UiDisplayController::print(PCCHAR)
{
}

SIZE UiDisplayController::print(CHAR)
{
}

SIZE UiDisplayController::print(BYTE, INT)
{
}

SIZE UiDisplayController::print(INT, INT)
{
}

SIZE UiDisplayController::print(UINT, INT)
{
}

SIZE UiDisplayController::print(LONG, INT)
{
}

SIZE UiDisplayController::print(DWORD, INT)
{
}

SIZE UiDisplayController::print(DOUBLE, INT)
{
}

SIZE UiDisplayController::print(CONST Printable &)
{
}

SIZE UiDisplayController::println(FLASH_STRING)
{
}

SIZE UiDisplayController::println(CONST String &)
{
}

SIZE UiDisplayController::println(PCCHAR)
{
}

SIZE UiDisplayController::println(CHAR)
{
}

SIZE UiDisplayController::println(BYTE, INT)
{
}

SIZE UiDisplayController::println(INT, INT)
{
}

SIZE UiDisplayController::println(UINT, INT)
{
}

SIZE UiDisplayController::println(LONG, INT)
{
}

SIZE UiDisplayController::println(DWORD, INT)
{
}

SIZE UiDisplayController::println(DOUBLE, INT)
{
}

SIZE UiDisplayController::println(CONST Printable &)
{

	return 0;
}

SIZE UiDisplayController::println()
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintString_P, flashStr, col, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return 0;
}

INT UiDisplayController::printf(PCCHAR format, ...)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::printf, format, col, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return 0;
}

INT UiDisplayController::printf(FLASH_STRING format, ...)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::printf, format, col, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return 0;
}



// [IUiRenderer] IMPLEMENTATION

CBYTE UiDisplayController::Cols() const
{
	BYTE cols = MAX_BYTE;

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		cols = _Renderers[i]->Cols();
		if (cols < MAX_BYTE)
			return cols;
	}

	return cols;
}

CBYTE UiDisplayController::Rows() const
{
	BYTE rows = MAX_BYTE;

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		rows = _Renderers[i]->Rows();
		if (rows < MAX_BYTE)
			return rows;
	}

	return rows;
}

CBOOL UiDisplayController::IsLineWrapEnabled() const
{
	return PtrAny(_RendererCount, _Renderers, &IUiRenderer::IsLineWrapEnabled);
}

VOID UiDisplayController::SetLineWrap(CBOOL wrapLines)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::SetLineWrap, wrapLines);
}

VOID UiDisplayController::CursorOn()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorOn);
}

VOID UiDisplayController::CursorOff()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorOff);
}

VOID UiDisplayController::CursorBlinkOn()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorBlinkOn);
}

VOID UiDisplayController::CursorBlinkOff()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorBlinkOff);
}

CBOOL UiDisplayController::Available()
{
	PtrAll(_RendererCount, _Renderers, &IUiRenderer::Available);
}

VOID UiDisplayController::Clear()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::Clear);
}

VOID UiDisplayController::ClearCol(CBYTE col)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ClearCol, col);
}

VOID UiDisplayController::ClearRow(CBYTE row)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ClearRow, row);
}

VOID UiDisplayController::ScrollLeft()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ScrollLeft);
}

VOID UiDisplayController::ScrollRight()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ScrollRight);
}

VOID UiDisplayController::Home()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::Home);
}

VOID UiDisplayController::CursorPrev()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorPrev);
}

VOID UiDisplayController::CursorNext()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorNext);
}

VOID UiDisplayController::MoveCursor(CBYTE col, CBYTE row)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::MoveCursor, col, row);
}

VOID UiDisplayController::LoadCustomChar(BYTE charIndex, PCBYTE charData)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::LoadCustomChar, charIndex, charData);
}

VOID UiDisplayController::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::LoadCustomChar_P, charIndex, charDataAddr);
}

CBYTE UiDisplayController::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::WriteAt, value, col, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return MAX_BYTE;
}

CBYTE UiDisplayController::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintString, str, col, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return MAX_BYTE;
}

CBYTE UiDisplayController::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintString_P, flashStr, col, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return MAX_BYTE;
}

CBYTE UiDisplayController::PrintStyledLine(PCCHAR str, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintStyledLine, str, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return MAX_BYTE;
}

CBYTE UiDisplayController::PrintStyledLine_P(FLASH_STRING flashStr, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintStyledLine_P, flashStr, row);

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return MAX_BYTE;
}

#ifndef NO_ITTYBITTY_EXTENSIONS

VOID UiDisplayController::DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::DrawScrollBar, percentage, options);
}

VOID UiDisplayController::DrawGraph(BYTE startCol, BYTE row,
	BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::DrawGraph,
		startCol, row, widthChars, percentage, options);
}

VOID UiDisplayController::DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
	BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::DrawSlider,
		startCol, row, widthChars, percentage, options, redraw);
}

#endif

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI