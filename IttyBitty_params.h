/***********************************************************************************************
* [IttyBitty_params.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE PARAMS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_PARAMS_H
#define _ITTYBITTY_PARAMS_H


#include "IttyBitty_datum.h"


namespace IttyBitty
{
#pragma region GLOBAL CONSTANTS & VARIABLES
		
	// ToBinary() / ToString() BUFFER POINTER
	EXTERN PBYTE __param_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IParam;
	typedef IParam IPARAM, * PIPARAM, & RIPARAM, ** PPIPARAM, && RRIPARAM;
	typedef const IParam CIPARAM, *PCIPARAM, & RCIPARAM, ** PPCIPARAM;

	class ParamBase;
	typedef ParamBase PARAMBASE, * PPARAMBASE, & RPARAMBASE, ** PPPARAMBASE, && RRPARAMBASE;
	typedef const ParamBase CPARAMBASE, * PCPARAMBASE, & RCPARAMBASE, ** PPCPARAMBASE;

	class Param;
	typedef Param PARAM, * PPARAM, & RPARAM, ** PPPARAM, && RRPARAM;
	typedef const Param CPARAM, * PCPARAM, & RCPARAM, ** PPCPARAM;

	class VarLengthParam;
	typedef VarLengthParam VARLENGTHPARAM, * PVARLENGTHPARAM, & RVARLENGTHPARAM, ** PPVARLENGTHPARAM, && RRVARLENGTHPARAM;
	typedef const VarLengthParam CVARLENGTHPARAM, * PCVARLENGTHPARAM, & RCVARLENGTHPARAM, ** PPCVARLENGTHPARAM;

	template<typename T = BYTE>
	class TypedParam;
	template<typename T = BYTE>
	using TYPEDPARAM = TypedParam<T>;
	template<typename T = BYTE>
	using PTYPEDPARAM = TypedParam<T> *;
	template<typename T = BYTE>
	using RTYPEDPARAM = TypedParam<T> &;
	template<typename T = BYTE>
	using PPTYPEDPARAM = TypedParam<T> **;
	template<typename T = BYTE>
	using RRTYPEDPARAM = TypedParam<T> &&;
	template<typename T = BYTE>
	using CTYPEDPARAM = const TypedParam<T>;
	template<typename T = BYTE>
	using PCTYPEDPARAM = const TypedParam<T> *;
	template<typename T = BYTE>
	using RCTYPEDPARAM = const TypedParam<T> &;
	template<typename T = BYTE>
	using PPCTYPEDPARAM = const TypedParam<T> **;

	template<typename T = PBYTE>
	class VarLengthTypedParam;
	template<typename T = PBYTE>
	using VARLENGTHTYPEDPARAM = VarLengthTypedParam<T>;
	template<typename T = PBYTE>
	using PVARLENGTHTYPEDPARAM = VarLengthTypedParam<T> *;
	template<typename T = PBYTE>
	using RVARLENGTHTYPEDPARAM = VarLengthTypedParam<T> &;
	template<typename T = PBYTE>
	using PPVARLENGTHTYPEDPARAM = VarLengthTypedParam<T> **;
	template<typename T = PBYTE>
	using RRVARLENGTHTYPEDPARAM = VarLengthTypedParam<T> &&;
	template<typename T = PBYTE>
	using CVARLENGTHTYPEDPARAM = const VarLengthTypedParam<T>;
	template<typename T = PBYTE>
	using PCVARLENGTHTYPEDPARAM = const VarLengthTypedParam<T> *;
	template<typename T = PBYTE>
	using RCVARLENGTHTYPEDPARAM = const VarLengthTypedParam<T> &;
	template<typename T = PBYTE>
	using PPCVARLENGTHTYPEDPARAM = const VarLengthTypedParam<T> **;

#pragma endregion


#pragma region INTERFACE DEFINITIONS


	// [IParam] DEFINITION

	INTERFACE IParam : public IDatum
	{
	public:

		// INTERFACE METHODS
	};

#pragma endregion


#pragma region [ParamBase] DEFINITION - TAGGED UNION BASE

	CLASS ParamBase : public IParam
	{
	public:

		// /DESTRUCTOR

		VIRTUAL ~ParamBase();
		
		
		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;
		VIRTUAL CSIZE ByteWidth() const;
		VIRTUAL CSIZE StringLength() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);

	#ifdef ARDUINO

		VIRTUAL BOOL Transmit(HardwareSerial & = SERIAL_PORT_HARDWARE);
		VIRTUAL BOOL Transmit(BYTE i2cAddr, TwoWire & = Wire);
				
		VIRTUAL SIZE printTo(Print &) const;

	#endif


		// IParam IMPLEMENTATION

		VIRTUAL CONST DataSize GetDataSize() const;
		VIRTUAL CONST DataType GetDataType() const;
		

	protected:

		// INSTANCE VARIABLES
		
		BOOL _Dispose = FALSE;

		ConstValue _Value;
		DataType _DataType;
	};

#pragma endregion


#pragma region [Param] DEFINITION - TAGGED UNION

	CLASS Param : public ParamBase
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		EXPLICIT Param(CONST DataType = DataType::BYTE_DATUM);

		Param(RCPARAM);
		Param(RRPARAM);

		EXPLICIT Param(RCCONSTVALUE, CONST DataType = DataType::BYTE_DATUM);

		EXPLICIT Param(RCCHAR);
		EXPLICIT Param(RCBYTE);
		EXPLICIT Param(RCBOOL);
		EXPLICIT Param(RCSHORT);
		EXPLICIT Param(RCWORD);
		EXPLICIT Param(RCLONG);
		EXPLICIT Param(RCDWORD);
		EXPLICIT Param(RCFLOAT);


		// STATIC FUNCTIONS

		STATIC RPARAM NULL_OBJECT();
		
		
		// OPERATORS

		VIRTUAL RPARAM operator =(RCPARAM);
		VIRTUAL RPARAM operator =(RRPARAM);

		VIRTUAL RPARAM operator =(RCCONSTVALUE);

		VIRTUAL operator RCCHAR() const;
		VIRTUAL operator RCBYTE() const;
		VIRTUAL operator RCBOOL() const;
		VIRTUAL operator RCSHORT() const;
		VIRTUAL operator RCWORD() const;
		VIRTUAL operator RCLONG() const;
		VIRTUAL operator RCDWORD() const;
		VIRTUAL operator RCFLOAT() const;
	};

#pragma endregion


#pragma region VarLengthParam DECLARATION - VARIABLE-LENGTH TAGGED UNION

	CLASS VarLengthParam : public Param
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		EXPLICIT VarLengthParam(CONST DataType = DataType::BYTES_DATUM, CSIZE = 0);

		VarLengthParam(RCVARLENGTHPARAM);
		VarLengthParam(RRVARLENGTHPARAM);

		EXPLICIT VarLengthParam(RCCONSTVALUE, CONST DataType = DataType::BYTES_DATUM, CSIZE = 0);

		EXPLICIT VarLengthParam(PCBYTE, CSIZE = 0);
		EXPLICIT VarLengthParam(PCCHAR);
		EXPLICIT VarLengthParam(PCBITPACK, CSIZE = 0);

		VIRTUAL ~VarLengthParam();
		
		
		// OPERATORS

		VIRTUAL RVARLENGTHPARAM operator =(RCVARLENGTHPARAM);
		VIRTUAL RVARLENGTHPARAM operator =(RRVARLENGTHPARAM);
		
		VIRTUAL operator PCBYTE() const;
		VIRTUAL operator PCCHAR() const;
		VIRTUAL operator PCBITPACK() const;


		// Param OVERRIDES

		VIRTUAL CSIZE ByteWidth() const final;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);
		

	protected:

		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region [TypedParam] DEFINITION - TEMPLATED TAGGED UNION
	
	template<typename T>
	CLASS TypedParam : public ParamBase
	{
	public:

		// CONSTRUYCTORS/DESTRUCTOR

		TypedParam()
		{
			_Dispose = TRUE;

			_DataType = TypedParam<T>::FindDataType();
		}

		TypedParam(RCTYPEDPARAM<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
		}

		TypedParam(RRTYPEDPARAM<T> other)
		{
			this->~ParamBase();
			new (this) TypedParam<T>(other._Value);
		}

		TypedParam(RCCONSTVALUE value)
		{
			_Value = value;
			_DataType = TypedParam<T>::FindDataType();
		}

		EXPLICIT TypedParam(T & value)
		{
			this->~ParamBase();
			new (this) TypedParam<T>(value);
		}

		EXPLICIT TypedParam(SIGNED_TYPE(T &) value)
		{
			this->~ParamBase();
			new (this) TypedParam<T>(value);
		}


		// STATIC METHODS

		STATIC RTYPEDPARAM<T> NULL_OBJECT()
		{
			STATIC TypedParam<T> NULL_TYPEDPARAM;
			return NULL_TYPEDPARAM;
		}
		
		
		// OPERATORS

		VIRTUAL RTYPEDPARAM<T> operator =(RCTYPEDPARAM<T> rValue)
		{
			*this = TypedParam<T>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDPARAM<T> operator =(RRTYPEDPARAM<T> rValue)
		{
			*this = TypedParam<T>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDPARAM<T> operator =(RCCONSTVALUE rValue)
		{
			_Value = rValue;
			return *this;
		}


		VIRTUAL operator UNSIGNED_TYPE(CONST T &)() const
		{
			return (UNSIGNED_TYPE(CONST T &))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(CONST T &)() const
		{
			return (SIGNED_TYPE(CONST T &))_Value;
		}


		// META-MEMBERS

		typedef T ParamType;


	protected:
		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return DataType::BYTE_DATUM;
		}
	};

#pragma endregion


#pragma region TypedParam PARTIAL SPECIALIZATIONS

	template<>
	class TypedParam<CHAR>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::CHAR_DATUM;
			}
	};

	template<>
	class TypedParam<BYTE>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTE_DATUM;
			}
	};

	template<>
	class TypedParam<BOOL>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BOOL_DATUM;
			}
	};

	template<>
	class TypedParam<SHORT>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::SHORT_DATUM;
			}
	};

	template<>
	class TypedParam<WORD>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::WORD_DATUM;
			}
	};

	template<>
	class TypedParam<LONG>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::LONG_DATUM;
			}
	};

	template<>
	class TypedParam<DWORD>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::DWORD_DATUM;
			}
	};

	template<>
	class TypedParam<FLOAT>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::FLOAT_DATUM;
			}
	};

#pragma endregion

	
#pragma region [VarLengthTypedParam] DEFINITION - TEMPLATED, VARIABLE-LENGTH TAGGED UNION

	template<typename T>
	PCCHAR StringReadValue(T &, PCCHAR, CBYTE = 0x10);

	template<typename T>
	CLASS VarLengthTypedParam : public TypedParam<T>
	{
	public:

		// CONSTRUYCTORS/DESTRUCTOR

		VarLengthTypedParam(CSIZE length = 0) : TypedParam<T>()
		{
			_Value = new T[length];
			_DataType = VarLengthTypedParam<T>::FindDataType();
			_Length = length;
		}

		VarLengthTypedParam(RCVARLENGTHTYPEDPARAM<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
			_Length = other._Length;
		}

		VarLengthTypedParam(RRVARLENGTHTYPEDPARAM<T> other)
		{
			this->~VarLengthTypedParam<T>();
			new (this) VarLengthTypedParam<T>(other._Value);
		}

		VarLengthTypedParam(RCCONSTVALUE value, CSIZE length = 0)
		{
			_Value = value;
			_DataType = VarLengthTypedParam<T>::FindDataType();

			if (_DataType == DataType::STRING_DATUM)
			{
				if (value.String == NULL)
					_Length = 0;
				else
					_Length = strlen((PCCHAR)_Value);
			}
			else
			{
				_Length = length;
			}
		}

		EXPLICIT VarLengthTypedParam(T & value)
		{
			new (this) VarLengthTypedParam<T>(value);
		}

		VIRTUAL ~VarLengthTypedParam()
		{
			if (!_Dispose)
				return;

			//if (_Length > 0 || _DataType == DataType::STRING_DATUM)
			//	_Value.FreeData();
		}
		
		
		// OPERATORS

		VIRTUAL operator CONST T() const
		{
			return (CONST T)_Value;
		}

		VIRTUAL operator UNSIGNED_TYPE(T &)()
		{
			return (T)_Value;
		}


		//  IParam OVERRIDES

		VIRTUAL CSIZE ByteWidth() const final
		{
			if (_Length > 0)
				return _Length;

			return ParamBase::ByteWidth();
		}
		
		VIRTUAL VOID FromBinary(PCBYTE data) final
		{
			PCBYTE bufferPtr = data;

			_Length = *reinterpret_cast<PCSIZE>(bufferPtr);
	
			ParamBase::FromBinary(data);
		}
		
		VIRTUAL VOID FromString(PCCHAR data) final
		{
			PCCHAR bufferPtr = data;

			bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

			ParamBase::FromString(data);
			
			// TODO
			//bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);
	
			//BYTE bytes[this->ByteWidth()];

			//for (BYTE i = 0; i < this->ByteWidth(); i++)
			//	bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);
		}


	protected:

		using TypedParam<T>::_Dispose;
		using TypedParam<T>::_Value;
		using TypedParam<T>::_DataType;
		using TypedParam<T>::IttyBitty::__param_buffer;

		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return TypedParam<T>::FindDataType();
		}


		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region VarLengthTypedParam PARTIAL SPECIALIZATIONS

	template<>
	class VarLengthTypedParam<PBYTE>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTES_DATUM;
			}
	};

	template<>
	class VarLengthTypedParam<PCHAR>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::STRING_DATUM;
			}
	};

	template<>
	class VarLengthTypedParam<BOOL>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BIT_DATUM;
			}
	};

#pragma endregion
	

#pragma region PARAM PARSING METHODS
	
	INLINE PIPARAM ParamFromBytes(PCBYTE data)
	{
		PIPARAM param = NULL;

		SIZE length = static_cast<SIZE>(*data);

		if (length == 0 || length > 4)
			param = new VarLengthParam();
		else
			param = new Param();

		param->FromBinary(data);

		return param;
	}
	
	INLINE PIPARAM ParamFromString(PCCHAR data)
	{
		PIPARAM param = NULL;
		SIZE length = 0;

		StringReadValue<SIZE>(length, data);

		if (length == 0 || length > 4)
			param = new VarLengthParam();
		else
			param = new Param();

		param->FromString(data);

		return param;
	}

#pragma endregion
}


#endif