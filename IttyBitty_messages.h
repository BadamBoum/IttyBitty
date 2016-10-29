﻿/***********************************************************************************************
* [IttyBitty_messages.h]: BASE SERIAL PROTOCOL DATA STRUCTURES & PARSING LOGIC
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MESSAGES_H
#define _ITTYBITTY_MESSAGES_H


#include "IttyBitty_fields.h"

#ifdef DEBUG_MESSAGES
	#include "IttyBitty_print.h"
#elif defined(ARDUINO)
	#include "Stream.h"
#endif


/* SUPRESS COMPILER WARNINGS RELATED TO FIELD REORDERING */

IGNORE_WARNING(-Wreorder)


namespace IttyBitty
{
#pragma region GLOBAL CONSTANTS & VARIABLES

	EXTERN CWORD SERIAL_DEFAULT_TIMEOUT_MS;

	EXTERN PCCHAR MESSAGE_MARKER;
		
	// Message::ToBytes() / ToString() BUFFER POINTER
	EXTERN PBYTE __message_buffer;

#pragma endregion

	
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IMessage;
	typedef IMessage IMESSAGE, * PIMESSAGE, & RIMESSAGE, ** PPIMESSAGE, && RRIMESSAGE;
	typedef const IMessage CIMESSAGE, *PCIMESSAGE, & RCIMESSAGE, ** PPCIMESSAGE;

	class Message;
	typedef Message MESSAGE, * PMESSAGE, & RMESSAGE, ** PPMESSAGE, && RRMESSAGE;
	typedef const Message CMESSAGE, *PCMESSAGE, & RCMESSAGE, ** PPCMESSAGE;

	template<CBYTE MsgCode, CBYTE ParamCnt>
	class GenericMessage;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using GENERICMESSAGE = GenericMessage<MsgCode, ParamCnt>;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PGENERICMESSAGE = GenericMessage<MsgCode, ParamCnt> *;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RGENERICMESSAGE = GenericMessage<MsgCode, ParamCnt> &;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PPGENERICMESSAGE = GenericMessage<MsgCode, ParamCnt> **;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RRGENERICMESSAGE = GenericMessage<MsgCode, ParamCnt> &&;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using CGENERICMESSAGE = const GenericMessage<MsgCode, ParamCnt>;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PCGENERICMESSAGE = const GenericMessage<MsgCode, ParamCnt> *;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RCGENERICMESSAGE = const GenericMessage<MsgCode, ParamCnt> &;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PPCGENERICMESSAGE = const GenericMessage<MsgCode, ParamCnt> **;

#pragma endregion
	

#pragma region [IMessage] DEFINITION

	INTERFACE IMessage : public ISerializable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IMessage() { }

		// OPERATORS

		VIRTUAL PCIFIELD operator[](CBYTE) const = 0;
		VIRTUAL PIFIELD operator[](CBYTE) = 0;
		

		// ACCESSORS

		VIRTUAL CBYTE GetParamCount() const = 0;
		VIRTUAL CBYTE GetMessageCode() const = 0;
		
		VIRTUAL RCIFIELD Param(CBYTE = 0) const = 0;
		VIRTUAL RIFIELD Param(CBYTE = 0) = 0;


		// USER METHODS

		VIRTUAL BOOL Handle(PVOID = NULL, PCVOID = NULL) = 0;

	protected:

		VIRTUAL CSIZE GetParamsByteSize() const = 0;
		VIRTUAL CSIZE GetParamsStringSize() const = 0;

		IMessage() { }
	};

#pragma endregion
	

#pragma region [Message] DEFINITION

	CLASS Message : public IMessage
	{
	public:


		// CONSTRUCTORS/DESTRUCTOR

		Message(CBYTE messageCode = 0, CBYTE paramCount = 0);

		Message(RCMESSAGE);
		Message(RRMESSAGE);

		EXPLICIT Message(PCBYTE);
		EXPLICIT Message(PCCHAR);

		EXPLICIT Message(CBYTE, PIFIELD);
		EXPLICIT Message(CBYTE, RCIFIELD);
		Message(CBYTE, CBYTE, PPIFIELD);

		VIRTUAL ~Message();


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:
		
		// OPERATORS

		VIRTUAL RMESSAGE operator=(RCMESSAGE);
		VIRTUAL RMESSAGE operator=(RRMESSAGE);

		VIRTUAL PCIFIELD operator[](CBYTE) const;
		VIRTUAL PIFIELD operator[](CBYTE);
		

		// ACCESSORS
		
		VIRTUAL CBYTE GetMessageCode() const;
		VIRTUAL CBYTE GetParamCount() const;
		
		VIRTUAL RCIFIELD Param(CBYTE = 0) const;
		VIRTUAL RIFIELD Param(CBYTE = 0);


		// USER METHODS

		VIRTUAL BOOL Handle(PVOID = NULL, PCVOID = NULL);
		

		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE ByteSize() const;
		VIRTUAL CSIZE StringSize() const;
		VIRTUAL CSIZE ByteWidth() const;
		VIRTUAL CSIZE StringLength() const;

		VIRTUAL PCBYTE ToBytes() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBytes(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);
		
	#ifdef ARDUINO
		VIRTUAL SIZE printTo(Print &) const;
	#endif


	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;
		
		BYTE _MessageCode;
		BYTE _ParamCount;

		PPIFIELD _Params;

		
		// HELPER METHODS

		VIRTUAL CSIZE GetParamsByteSize() const;
		VIRTUAL CSIZE GetParamsStringSize() const;
	};

#pragma endregion
	

#pragma region [GenericMessage] DEFINITION
	
	template<CBYTE MsgCode, CBYTE ParamCnt = 0>
	CLASS GenericMessage : public Message
	{
	public:

		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE MESSAGE_CODE()
		{
			return MsgCode;
		}

		STATIC CONSTEXPR CSIZE PARAM_COUNT()
		{
			return ParamCnt;
		}


		// CONSTRUCTORS

		GenericMessage() : Message(MsgCode, ParamCnt) { }

		GenericMessage(PIFIELD param) : Message(MsgCode, param) { }

		GenericMessage(RCIFIELD param) : Message(MsgCode, param) { }

		GenericMessage(PPIFIELD params) : Message(MsgCode, ParamCnt, params) { }


		// MESSAGE OVERRIDES

		VOID Handle(...) { }

		CBYTE GetMessageCode() const
		{
			return MESSAGE_CODE();
		}

		CBYTE GetParamCount() const
		{
			return PARAM_COUNT();
		}


	protected:

		using Message::_Dispose;
		using Message::_Params;
	};
	
#pragma endregion
	
	
#ifdef ARDUINO

#pragma region SERIAL/STREAM READING METHODS

	INLINE CBOOL operator >(Stream & stream, PBYTE b)
	{
		return stream.readBytes(b, 1);
	}

	INLINE CBOOL ReadBuffer(Stream & stream, PBYTE buffer, CSIZE length = 1)
	{
		SIZE i = length;

		while (i > 0)
		{
			if (!stream.available())
			{
				delay(SERIAL_DEFAULT_TIMEOUT_MS);
				
				if (!stream.available())
					return FALSE;
			}
				
			INT result = stream.read();
			if (result < 0)
				return FALSE;

			buffer[length - i--] = (CBYTE)result;
		}

		return TRUE;
	}

	template<typename T>
	INLINE CONST T & Read(Stream & stream, PBYTE buffer)
	{
		CBOOL result = ReadBuffer(stream, buffer, T_SIZE);
		
		STATIC T NULL_T = (T)0;
		if (!result)
			return NULL_T;

		return *((T *)buffer);
	}

#pragma endregion
	

#pragma region MESSAGE PARSING METHODS
	
	typedef VOID (* MessageHandler)(PIMESSAGE);


	INLINE PIMESSAGE MessageFromBytes(Stream & stream)
	{
		if (!stream.find(UNCONST(MESSAGE_MARKER), strlen(MESSAGE_MARKER)))
			return NULL;

		SIZE msgSize = 0;
		msgSize = Read<CSIZE>(stream, (PBYTE)&msgSize);
		if (msgSize == 0)
			return NULL;

		CSIZE bufferSize = msgSize - SIZEOF(CSIZE);
		__message_buffer = new byte[bufferSize];

		if (!ReadBuffer(stream, __message_buffer, bufferSize))	
			return NULL;

		PIMESSAGE newMsg = new Message();
		newMsg->FromBytes(__message_buffer);

		delete[] __message_buffer;
		__message_buffer = NULL;

		return newMsg;
	}	

	INLINE PIMESSAGE MessageFromString(Stream & stream)
	{
		if (!stream.find(UNCONST(MESSAGE_MARKER), strlen(MESSAGE_MARKER)))
			return NULL;

	#ifdef DEBUG_MESSAGES
		Serial.print(F("MESSAGE INCOMING [SIZE="));
	#endif

		CHAR valStr[4];
		ReadBuffer(stream, reinterpret_cast<PBYTE>(valStr), 2 * SIZEOF(CSIZE));
		
		SIZE msgSize = 0;
		StringReadValue<SIZE>(msgSize, valStr);
		if (msgSize == 0)
			return NULL;

	#ifdef DEBUG_MESSAGES
		Serial.print(msgSize);
		PrintLineAndFlush("].");
	#endif
		
		CSIZE bufferSize = msgSize - 2 * SIZEOF(CSIZE);
		__message_buffer = new byte[bufferSize];
		__message_buffer[bufferSize - 1] = '\0';

	#ifdef DEBUG_MESSAGES
		Serial.print(bufferSize);
		PrintLineAndFlush(F(" BYTES ALLOCATED.  READING DATA..."));
	#endif

		if (!ReadBuffer(stream, __message_buffer, bufferSize - 1))
			return NULL;

	#ifdef DEBUG_MESSAGES
		Serial.print(F("RAW DATA: "));
		Serial.println((PCCHAR)__message_buffer);
		PrintLineAndFlush(F("BUFFER FILLED.  LOADING..."));
	#endif		
		
		STATIC PIMESSAGE stringMsg = NULL;
		stringMsg = new Message();
		stringMsg->FromString(reinterpret_cast<PCCHAR>(__message_buffer));

	#ifdef DEBUG_MESSAGES
		PrintLineAndFlush(F("MESSAGE LOADED.\n"));
	#endif

		delete[] __message_buffer;
		__message_buffer = NULL;

		return stringMsg;
	}
	
	INLINE VOID WaitForMessage(Stream & stream, MessageHandler msgHandler)
	{
		PIMESSAGE message = NULL;

	#ifdef _DEBUG
		message = MessageFromString(stream);
	#else
		message = MessageFromBytes(stream);
	#endif

		if (message == NULL)
			return;

		if (__message_buffer != NULL)
			delete[] __message_buffer;
		__message_buffer = NULL;

		msgHandler(message);

		delete message;
	}

#pragma endregion

#endif	// #ifdef ARDUINO
}


#endif
