/************************************************************
* Copyright � 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#include "IttyBitty_bytes.h"

using namespace IttyBitty;


/* [BITPROXY/BITREF]: PROXY CLASS TO ALLOW FOR INDIVIDUAL BIT-ADDRESSED MEMORY WRITES */

_BitProxy::_BitProxy(PIBYTEFIELD pParent, SIZE i) : _Parent(pParent), _BitMask(BIT_MASK(i)) { }

_BitProxy::_BitProxy(RCBITREF other) : _Parent(other.Parent()), _BitMask(other.BitMask()) { }

_BitProxy::~_BitProxy() { }

RBITREF _BitProxy::NULL_OBJECT()
{
	STATIC BITREF NULL_BITREF(NULL, 0);
	return NULL_BITREF;
}

_BitProxy::operator BIT() const
{
	return _Parent->Mask(_BitMask) != 0;
}

RBITREF _BitProxy::operator=(RCBITREF crRValue)
{
	*this = (BIT)crRValue;
	return *this;
}

RBITREF _BitProxy::operator=(BIT bit)
{
	_Parent->SetValue(_Parent->Mask(NOT _BitMask) | (bit ? _BitMask : (BYTE)0));
	return *this;
}

BIT _BitProxy::Flip()
{
	return this->operator=(NOT (BIT)this);
}

PIBYTEFIELD _BitProxy::Parent() const
{
	return _Parent;
}

BYTE _BitProxy::BitMask() const
{
	return _BitMask;
}


/* [BYTEIELD] DEFINITION */

ByteField::ByteField()
{
	this->~ByteField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField((BYTE)0);
	//new (this) ByteField((BYTE)0);
}

ByteField::ByteField(RCBYTE byteVal) : _pByte(new BYTE(byteVal)), _DisposeByte(true) { }

ByteField::ByteField(RBYTE byteRef) : _pByte(&byteRef), _DisposeByte(false) { }

ByteField::ByteField(PBYTE pByte) : _pByte(pByte), _DisposeByte(false) { }

ByteField::ByteField(RCBYTEFIELD other)
{
	this->~ByteField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField(other.ByteRef());
	//new (this) ByteField((RBYTE)other);
}
	
ByteField::~ByteField()
{
	if (_DisposeByte)
		delete _pByte;
}

RBYTEFIELD ByteField::NULL_OBJECT()
{
	STATIC BYTEFIELD NULL_BYTEFIELD((BYTE)0);
	return NULL_BYTEFIELD;
}

CSIZE ByteField::Size() const
{
	return sizeof(ByteField);

}

SIZE ByteField::BitWidth() const
{
	return this->ByteSize() * BitPack::BitSize();
}

SIZE ByteField::ByteSize() const
{
	return 1;
}

ByteField::operator CBYTE() const
{
	return MAKE_CONST(*_pByte);
}

ByteField::operator CCHAR() const
{
	return (CCHAR)this->operator CBYTE();
}

ByteField::operator PCBYTE() const
{
	return MAKE_CONST(_pByte);
}

ByteField::operator PPBYTE()
{
	return &_pByte;
}
		
ByteField::operator PCCHAR() const
{
	return (PCCHAR)this->operator PCBYTE();
}

ByteField::operator PPCHAR()
{
	return (PPCHAR)this->operator PPBYTE();
}
		
ByteField::operator PBYTEFIELD() const
{
	return NULL;
}

ByteField::operator PPBYTEFIELD()
{
	STATIC PBYTEFIELD sillyPtr[1] = { this };
	return sillyPtr;
}

BIT ByteField::operator[](SIZE i) const
{
	return this->Bit(i);
}

BITREF ByteField::operator[](SIZE i)
{
	return this->Bit(i);
}

BIT ByteField::Bit(SIZE i) const
{
	return MAKE_CONST(_pBitPack)->Bit(i);
}

BITREF ByteField::Bit(SIZE i)
{
	if (i >= this->BitWidth())
		return BitRef::NULL_OBJECT();

	return BitRef(this, i);
}

BIT ByteField::Flip(SIZE i)
{
	return this->Bit(i).Flip();
}

PPCBYTEFIELD ByteField::Bytes() const
{
	STATIC PCBYTEFIELD thisClone = this;
	return &thisClone;
}

BYTE ByteField::Byte(SIZE i) const
{
	if (i >= this->ByteSize())
		return ByteField::NULL_OBJECT();

	return *_pByte;
}

RIBYTEFIELD ByteField::Byte(SIZE i)
{
	return *this;
}

BYTE ByteField::Value() const
{
	return *_pByte;
}

VOID ByteField::SetValue(BYTE value)
{
	*_pByte = value;
}

VOID ByteField::CopyFrom(RCIBITFIELD<BYTE> other)
{
	*_pByte = other.Value();
}

PBYTE ByteField::Pointer() const
{
	return _pByte;
}

VOID ByteField::PointTo(PBYTE pByte)
{
	_pByte = pByte;
}

VOID ByteField::ReferenceFrom(RCIBITFIELD<BYTE> other)
{
	_pByte = other.Pointer();
}

BYTE ByteField::Mask(BYTE byteMask) const
{
	return MASK(this->Value(), byteMask);
}

BYTE ByteField::Mask(RCIBITFIELD<BYTE> other) const
{
	return MASK(this->Value(), other.Value());
}

ByteField::operator PBYTE()
{
	return _pByte;
}

ByteField::operator RBYTE()
{
	return *_pByte;
}

ByteField::operator PCHAR()
{
	return (PCHAR)_pByte;
}

ByteField::operator RCHAR()
{
	return (RCHAR)*_pByte;
}

ByteField::operator PCBITPACK() const
{
	return MAKE_CONST(_pBitPack);
}

ByteField::operator PBITPACK()
{
	return _pBitPack;
}

PIBYTEFIELD ByteField::CloneByValue() const
{
	return new ByteField(this->Value());
}

PIBYTEFIELD ByteField::CloneByReference() const
{
	return new ByteField(_pByte);
}

BYTE ByteField::LowNybble() const
{
	return LOW_NYBBLE(this->Value());
}

RIBYTEFIELD ByteField::SetLowNybble(BYTE nybbleVal)
{
	*_pByte = (this->HighNybble() << 4) | LOW_NYBBLE(nybbleVal);
	return *this;
}

BYTE ByteField::HighNybble() const
{
	return HIGH_NYBBLE(this->Value());
}

RIBYTEFIELD ByteField::SetHighNybble(BYTE nybbleVal)
{
	*_pByte = HIGH_NYBBLE(nybbleVal) | this->LowNybble();
	return *this;
}


/* [BITFIELD] DEFINITION */

template<typename T>
BitField<T>::BitField() : _DisposalLevel(DisposalLevel::FieldData)
{
	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i++)
		_ByteFieldPtrs[i] = (PBYTEFIELD)NULL;
}

template<typename T>
BitField<T>::BitField(T tVal) : _DisposalLevel(DisposalLevel::None)
{
	this->SetValue(tVal);
}

template<typename T>
BitField<T>::BitField(T * tPtr) : _DisposalLevel(DisposalLevel::None)
{
	this->PointTo(tPtr);
}

template<typename T>
BitField<T>::BitField(PVOID memAddr, SIZE byteWidth) : _DisposalLevel(DisposalLevel::FieldData)
{
	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i++)
	{
		if (i < byteWidth)
			_ByteFieldPtrs[i] = new ByteField((PBYTE)memAddr + i);
		else
			_ByteFieldPtrs[i] = new ByteField((BYTE)0);
	}
}

template<typename T>
BitField<T>::BitField(BYTE byteVals[T_SIZE]) : _DisposalLevel(DisposalLevel::FieldData)
{
	_ByteFieldPtrs = new ByteField[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i++)
		_ByteFieldPtrs[i] = new ByteField((BYTE)byteVals[i]);
}

template<typename T>
BitField<T>::BitField(PBYTE bytePtrs[T_SIZE]) : _DisposalLevel(DisposalLevel::FieldData)
{
	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i++)
		_ByteFieldPtrs[i] = new ByteField(bytePtrs[i]);
}

template<typename T>
BitField<T>::BitField(BYTEFIELD byteFields[T_SIZE]) : _DisposalLevel(DisposalLevel::FieldPtrPtr) // TODO: FieldPtrs?
{
	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];
	
	for (SIZE i = 0; i < T_SIZE; i++)
		_ByteFieldPtrs[i] = &byteFields[i];
}

template<typename T>
BitField<T>::BitField(PBYTEFIELD byteFieldPtrs[T_SIZE]) : _DisposalLevel(DisposalLevel::None)
{
	_ByteFieldPtrs = byteFieldPtrs;
}

template<typename T>
BitField<T>::BitField(RCBITFIELD<T> other)
{
	this->~BitField<T>();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField((PVOID)other.Bytes(), other.ByteSize());
	new (this) BitField<T>((PVOID)other.Bytes(), T_SIZE);
}

template<typename T>
BitField<T>::~BitField()
{
	switch (_DisposalLevel)
	{
	case DisposalLevel::FieldData:

		for (SIZE i = 0; i < T_SIZE; i++)
			delete _ByteFieldPtrs[i];

	case DisposalLevel::FieldPtrs:

		delete[] _ByteFieldPtrs;
		break;
		
	case DisposalLevel::FieldPtrPtr:

		delete _ByteFieldPtrs;
		break;

	case DisposalLevel::None:

		break;
	}
}

template<typename T>
RBITFIELD<T> BitField<T>::NULL_OBJECT()
{
	STATIC BITFIELD<T> NULL_BITFIELD((BYTE)0);
	return NULL_BITFIELD;
}

template<typename T>
CSIZE BitField<T>::Size() const
{
	return sizeof(TYPEOF(*this));
}

template<typename T>
SIZE BitField<T>::BitWidth() const
{
	return this->ByteSize() * BitPack::BitSize();
}

template<typename T>
SIZE BitField<T>::ByteSize() const
{
	return T_SIZE;
}

template<typename T>
BitField<T>::operator CONST T() const
{
	return this->Value();
}

template<typename T>
BitField<T>::operator SIGNED_TYPE(CONST T)() const
{
	return (SIGNED_TYPE(T))this->Value();
}

template<typename T>
BitField<T>::operator PCBYTE() const
{
	STATIC BYTE bytes[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i ++)
		bytes[i] = _ByteFieldPtrs[i]->Value();

	return bytes;
}

template<typename T>
BitField<T>::operator PPBYTE()
{
	STATIC PPBYTE bytePtrs[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i ++)
		(*bytePtrs)[i] = _ByteFieldPtrs[i]->Pointer();

	return *bytePtrs;
}

template<typename T>
BitField<T>::operator PCCHAR() const
{
	return (PCCHAR)this->operator PCBYTE();
}

template<typename T>
BitField<T>::operator PPCHAR()
{
	return (PPCHAR)this->operator PPBYTE();
}

template<typename T>
BitField<T>::operator PBYTEFIELD() const
{
	return *_ByteFieldPtrs;
}

template<typename T>
BitField<T>::operator PPBYTEFIELD()
{
	return _ByteFieldPtrs;
}

template<typename T>
BIT BitField<T>::operator[](SIZE i) const
{
	return this->Bit(i);
}

template<typename T>
BITREF BitField<T>::operator[](SIZE i)
{
	return this->Bit(i);
}

template<typename T>
BIT BitField<T>::Bit(SIZE i) const
{
	return (BIT)this->Bit(i);
}

template<typename T>
BITREF BitField<T>::Bit(SIZE i)
{
	if (i >= this->BitWidth())
		return BitRef::NULL_OBJECT();
	
	BYTE byteIdx = i / T_SIZE;
	BYTE bitIdx = i % T_SIZE;

	return this->Byte(byteIdx).Bit(bitIdx);
}

template<typename T>
BIT BitField<T>::Flip(SIZE i)
{
	if (i >= this->BitWidth())
		return BitRef::NULL_OBJECT();
	
	return this->Bit(i).Flip();
}

template<typename T>
PPCBYTEFIELD BitField<T>::Bytes() const
{
	return MAKE_CONST_PP(_ByteFieldPtrs);
}

template<typename T>
BYTE BitField<T>::Byte(SIZE i) const
{
	return _ByteFieldPtrs[i]->Value();
}

template<typename T>
RIBYTEFIELD BitField<T>::Byte(SIZE i)
{
	if (i >= this->ByteSize())
		return ByteField::NULL_OBJECT();
	
	return *_ByteFieldPtrs[i];
}

template<typename T>
T BitField<T>::Value() const
{
	T tVal = 0;

	for (SIZE i = 0; i < T_SIZE; i++)
		tVal += _ByteFieldPtrs[i]->Value() * (256 << i);

	return tVal;
}

template<typename T>
VOID BitField<T>::SetValue(T tVal)
{
	this->~BitField<T>();

	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < this->ByteSize(); i ++)
		_ByteFieldPtrs[i] = new ByteField(*((PBYTE)&tVal + i));

	_DisposalLevel = DisposalLevel::FieldData;
}

template<typename T>
VOID BitField<T>::CopyFrom(RCIBITFIELD<T> other)
{	
	this->SetValue(other.Value());
}

template<typename T>
T * BitField<T>::Pointer() const
{
	return (T *)_ByteFieldPtrs[0]->Pointer();
}

template<typename T>
VOID BitField<T>::PointTo(T * tPtr)
{
	this->~BitField<T>();

	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < this->ByteSize(); i ++)
		_ByteFieldPtrs[i] = new ByteField((PBYTE)tPtr + i);

	_DisposalLevel = DisposalLevel::FieldData;
}

template<typename T>
VOID BitField<T>::ReferenceFrom(RCIBITFIELD<T> other)
{
	this->~BitField<T>();
	
	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];
	*_ByteFieldPtrs = (PBYTEFIELD)other;

	_DisposalLevel = DisposalLevel::FieldPtrs;
}

template<typename T>
T BitField<T>::Mask(T tMask) const
{
	return MASK(this->Value(), tMask);
}

template<typename T>
T BitField<T>::Mask(RCIBITFIELD<T> other) const
{
	return MASK(this->Value(), other.Value());
}

template<typename T>
PIBITFIELD<T> BitField<T>::CloneByValue() const
{
	return new BitField<T>(this->Value());
}

template<typename T>
PIBITFIELD<T> BitField<T>::CloneByReference() const
{
	return new BitField<T>((PVOID)_ByteFieldPtrs, T_SIZE);
}

/* [WORDFIELD] DEFINITION */

WordField::WordField() : BitField<WORD>() { }

WordField::WordField(WORD wordVal) : BitField<WORD>()
{
	this->SetValue(wordVal);
}

WordField::WordField(RWORD rWord) : BitField<WORD>((PVOID)&rWord, 2) { }

WordField::WordField(PWORD pWord) : BitField<WORD>((PVOID)pWord, 2) { }

WordField::WordField(BYTEFIELD byteFields[2]) : BitField<WORD>(byteFields) { }

WordField::WordField(PBYTEFIELD byteFieldPtrs[2]) : BitField<WORD>(byteFieldPtrs) { }
		
WordField::WordField(RCWORDFIELD other) : BitField<WORD>(other) { }

RWORDFIELD WordField::NULL_OBJECT()
{
	STATIC WORDFIELD NULL_WORDFIELD((WORD)0);
	return NULL_WORDFIELD;
}

//WordField::operator WORD()
//{
//	return (WORD)this->operator SHORT();
//}

//WordField::operator SHORT()
//{
//	return (((SHORT)(BYTE)this->Byte(1)) << 8) OR (BYTE)this->Byte(0);
//}

BYTE WordField::LowByte() const
{
	return this->Byte(0);
}

RIBYTEFIELD WordField::SetLowByte(BYTE byteVal)
{
	RIBYTEFIELD byteField = this->Byte(0);
	byteField.SetValue(byteVal);
	return byteField;
}

BYTE WordField::HighByte() const
{
	return this->Byte(1);
}

RIBYTEFIELD WordField::SetHighByte(BYTE byteVal)
{
	RIBYTEFIELD byteField = this->Byte(1);
	byteField.SetValue(byteVal);
	return byteField;
}


/* [IMANYBITFIELD] DEFINITION */

template<typename T>
ManyBitField<T>::ManyBitField() : BitField<T>()
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(T tVal) : BitField<T>((PBYTE)&tVal)
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(T * tPtr) : BitField<T>((PPBYTE)tPtr)
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(PVOID memAddr, SIZE byteWidth) : BitField<T>(memAddr, byteWidth)
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(BYTE byteVals[T_SIZE]) : BitField<T>(byteVals)
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(PBYTE bytePtrs[T_SIZE]) : BitField<T>(bytePtrs)
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(BYTEFIELD byteFields[T_SIZE]) : BitField<T>(byteFields)
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(PBYTEFIELD byteFieldPtrs[T_SIZE]) : BitField<T>(byteFieldPtrs)
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(WORDFIELD wordFields[T_SIZE / 2])
{
	PBYTEFIELD byteFieldPtrs[4];

	for (SIZE i = 0; i < 2; i ++)
	{
		byteFieldPtrs[i * 2] = ((PWORDFIELD)(&wordFields + i))->Byte(i * 2);
		byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(&wordFields + i))->Byte(i * 2 + 1);
	}
	
	this->~ManyBitField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ManyBitField(byteFieldPtrs);
	new (this) ManyBitField(byteFieldPtrs);
	
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(PWORDFIELD wordFields[T_SIZE / 2])
{
	PBYTEFIELD byteFieldPtrs[4];

	for (SIZE i = 0; i < 2; i ++)
	{
		byteFieldPtrs[i * 2] = ((PWORDFIELD)(wordFields + i))->Byte(i * 2);
		byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(wordFields + i))->Byte(i * 2 + 1);
	}
	
	this->~ManyBitField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ManyBitField(byteFieldPtrs;
	new (this) ManyBitField(byteFieldPtrs);
	
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::ManyBitField(RCMANYBITFIELD<T> other) : BitField<T>(other)
{
	this->InitWordFields();
}

template<typename T>
ManyBitField<T>::~ManyBitField()
{
	switch (_DisposalLevel)
	{
	case DisposalLevel::FieldData:

		for (SIZE i = 0; i < T_SIZE; i++)
			delete _WordFieldPtrs[i];

	case DisposalLevel::FieldPtrs:

		delete[] _WordFieldPtrs;
		break;
		
	case DisposalLevel::FieldPtrPtr:

		delete _WordFieldPtrs;
		break;

	case DisposalLevel::None:

		break;
	}
}

template<typename T>
RMANYBITFIELD<T> ManyBitField<T>::NULL_OBJECT()
{
	STATIC RMANYBITFIELD<T> NULL_MANYBITFIELD((T)0);
	return NULL_MANYBITFIELD;
}

template<typename T>
SIZE ManyBitField<T>::WordSize() const
{
	return T_SIZE / 2;
}

template<typename T>
ManyBitField<T>::operator PPWORD() const
{
	STATIC PPWORD wordPtrs[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i ++)
		(*wordPtrs)[i] = _WordFieldPtrs[i]->Pointer();

	return *wordPtrs;
}

template<typename T>
ManyBitField<T>::operator PPSHORT() const
{
	return (PPSHORT)this->operator PPWORD();
}

template<typename T>
WORD ManyBitField<T>::Word(SIZE i) const
{
	return (WORD)this->Word(i);
}

template<typename T>
RIWORDFIELD ManyBitField<T>::Word(SIZE i)
{
	if (i > this->ByteSize() / 2)
		return WordField::NULL_OBJECT();

	return *_WordFieldPtrs[i];
}

template<typename T>
VOID ManyBitField<T>::InitWordFields()
{
	if (_WordFieldPtrs != NULL)
		delete[] _WordFieldPtrs;
	
	_WordFieldPtrs = new PWORDFIELD[this->WordSize()];

	for (SIZE i = 0; i < this->WordSize(); i++)
		_WordFieldPtrs[i] = new WordField((PBYTEFIELD)(this->Bytes() + i * 2));
}


/* [DWORDFIELD] DEFINITION */

DWordField::DWordField() : ManyBitField<DWORD>() { }

DWordField::DWordField(DWORD wordVal) : ManyBitField<DWORD>()
{
	this->SetValue(wordVal);
}

DWordField::DWordField(RDWORD rDWord) : ManyBitField<DWORD>((PVOID)&rDWord, 4) { }

DWordField::DWordField(PDWORD pDWord) : ManyBitField<DWORD>((PVOID)pDWord, 4) { }

DWordField::DWordField(BYTEFIELD byteFields[4]) : ManyBitField<DWORD>(byteFields) { }

DWordField::DWordField(PBYTEFIELD byteFieldPtrs[4]) : ManyBitField<DWORD>(byteFieldPtrs) { }

DWordField::DWordField(WORDFIELD wordFields[2]) : ManyBitField<DWORD>(wordFields) { }

DWordField::DWordField(PWORDFIELD wordFieldPtrs[2]) : ManyBitField<DWORD>(wordFieldPtrs) { }
		
DWordField::DWordField(RCDWORDFIELD other) : ManyBitField<DWORD>(other) { }

RDWORDFIELD DWordField::NULL_OBJECT()
{
	STATIC DWORDFIELD NULL_DWORDFIELD((DWORD)0);
	return NULL_DWORDFIELD;
}

WORD DWordField::LowWord() const
{
	return this->Word(0);
}

RIWORDFIELD DWordField::SetLowWord(WORD wordVal)
{
	RIWORDFIELD wordField = this->Word(0);
	wordField.SetValue(wordVal);
	return wordField;
}
		
WORD DWordField::HighWord() const
{
	return this->Word(1);
}

RIWORDFIELD DWordField::SetHighWord(WORD wordVal)
{
	RIWORDFIELD wordField = this->Word(1);
	wordField.SetValue(wordVal);
	return wordField;
}
