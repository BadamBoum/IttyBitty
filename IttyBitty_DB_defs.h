/***********************************************************************************************
* [IttyBitty_DB_defs.h]: HEADERS/TABLE DEFINITIONS FOR STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_DB_DEFS_H
#define _ITTYBITTY_DB_DEFS_H


#include "IttyBitty_fields.h"
#include "IttyBitty_storage.h"


namespace IttyBitty
{
#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS

	// ToBinary() / ToString() BUFFER POINTERS
	EXTERN PBYTE __db_table_def_set_buffer;
	EXTERN PBYTE __db_table_def_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IDbTableDef;
	typedef IDbTableDef IDBTABLEDEF, * PIDBTABLEDEF, & RIDBTABLEDEF, ** PPIDBTABLEDEF, && RRIDBTABLEDEF;
	typedef const IDbTableDef CIDBTABLEDEF, * PCIDBTABLEDEF, & RCIDBTABLEDEF, ** PPCIDBTABLEDEF;

	class DbTableDef;
	typedef DbTableDef DBTABLEDEF, * PDBTABLEDEF, & RDBTABLEDEF, ** PPDBTABLEDEF, && RRDBTABLEDEF;
	typedef const DbTableDef CDBTABLEDEF, * PCDBTABLEDEF, & RCDBTABLEDEF, ** PPCDBTABLEDEF;

	class DbTable;

	template<typename T>
	class TypedDbTableDef;
	template<typename T>
	using TYPEDDBTABLEDEF = TypedDbTableDef<T>;
	template<typename T>
	using PTYPEDDBTABLEDEF = TypedDbTableDef<T> *;
	template<typename T>
	using RTYPEDDBTABLEDEF = TypedDbTableDef<T> &;
	template<typename T>
	using PPTYPEDDBTABLEDEF = TypedDbTableDef<T> **;
	template<typename T>
	using RRTYPEDDBTABLEDEF = TypedDbTableDef<T> &&;
	template<typename T>
	using CTYPEDDBTABLEDEF = const TypedDbTableDef<T>;
	template<typename T>
	using PCTYPEDDBTABLEDEF = const TypedDbTableDef<T> *;
	template<typename T>
	using RCTYPEDDBTABLEDEF = const TypedDbTableDef<T> &;
	template<typename T>
	using PPCTYPEDDBTABLEDEF = const TypedDbTableDef<T> **;

	template<typename T>
	class TypedDbTable;

	// TODO: Not yet implemented.
	class FieldedDbTableDef;
	typedef FieldedDbTableDef FIELDEDDBTABLEDEF, * PFIELDEDDBTABLEDEF, & RFIELDEDDBTABLEDEF, ** PPFIELDEDDBTABLEDEF, && RRFIELDEDDBTABLEDEF;
	typedef const FieldedDbTableDef CFIELDEDDBTABLEDEF, * PCFIELDEDDBTABLEDEF, & RCFIELDEDDBTABLEDEF, ** PPCFIELDEDDBTABLEDEF;

	class IDbTableDefSet;
	typedef IDbTableDefSet IDBTABLEDEFSET, * PIDBTABLEDEFSET, & RIDBTABLEDEFSET, ** PPIDBTABLEDEFSET, && RRIDBTABLEDEFSET;
	typedef const IDbTableDefSet CIDBTABLEDEFSET, * PCIDBTABLEDEFSET, & RCIDBTABLEDEFSET, ** PPCIDBTABLEDEFSET;

	class DbTableDefSet;
	typedef DbTableDefSet DBTABLEDEFSET, * PDBTABLEDEFSET, & RDBTABLEDEFSET, ** PPDBTABLEDEFSET, && RRDBTABLEDEFSET;
	typedef const DbTableDefSet CDBTABLEDEFSET, * PCDBTABLEDEFSET, & RCDBTABLEDEFSET, ** PPCDBTABLEDEFSET;

	template<CBYTE TableDefCount = 0>
	class GenericDbTableDefSet;
	template<CBYTE TableDefCount = 0>
	using GENERICDBTABLEDEFSET = GenericDbTableDefSet<TableDefCount>;
	template<CBYTE TableDefCount = 0>
	using PGENERICDBTABLEDEFSET = GenericDbTableDefSet<TableDefCount> *;
	template<CBYTE TableDefCount = 0>
	using RGENERICDBTABLEDEFSET = GenericDbTableDefSet<TableDefCount> &;
	template<CBYTE TableDefCount = 0>
	using PPGENERICDBTABLEDEFSET = GenericDbTableDefSet<TableDefCount> **;
	template<CBYTE TableDefCount = 0>
	using RRGENERICDBTABLEDEFSET = GenericDbTableDefSet<TableDefCount> &&;
	template<CBYTE TableDefCount = 0>
	using CGENERICDBTABLEDEFSET = const GenericDbTableDefSet<TableDefCount>;
	template<CBYTE TableDefCount = 0>
	using PCGENERICDBTABLEDEFSET = const GenericDbTableDefSet<TableDefCount> *;
	template<CBYTE TableDefCount = 0>
	using RCGENERICDBTABLEDEFSET = const GenericDbTableDefSet<TableDefCount> &;
	template<CBYTE TableDefCount = 0>
	using PPCGENERICDBTABLEDEFSET = const GenericDbTableDefSet<TableDefCount> **;

	class Database;

#pragma endregion


#pragma region ENUMS

	ENUM DbResult : BYTE
	{
		SUCCESS									= 0x00,

		ERROR									= 0x01,
		ERROR_UNKNOWN							= ERROR,

		ERROR_ARGUMENT							= ERROR | 0x20,
		ERROR_ARGUMENT_FILE_NAME_FORMAT			= ERROR_ARGUMENT | 0x10,
		ERROR_ARGUMENT_STORAGE_SPACE_LIMIT		= ERROR_ARGUMENT | 0x08,
		ERROR_ARGUMENT_OUT_OF_RANGE				= ERROR_ARGUMENT | 0x04,
		ERROR_ARGUMENT_NULL_POINTER				= ERROR_ARGUMENT | 0x02,

		ERROR_OPERATION							= ERROR,
		ERROR_OPERATION_UNKOWN					= ERROR_OPERATION,
		ERROR_OPERATION_INTERRUPTED				= ERROR_OPERATION | 0x08,

		ERROR_OPERATION_CREATE					= ERROR_OPERATION | 0xF0,
		ERROR_OPERATION_DELETE					= ERROR_OPERATION | 0xE0,
		ERROR_OPERATION_ADD						= ERROR_OPERATION | 0xD0,
		ERROR_OPERATION_BUFFER_FULL				= ERROR_OPERATION_ADD | 0x08,
		ERROR_OPERATION_REMOVE					= ERROR_OPERATION | 0xC0,
		ERROR_OPERATION_READ					= ERROR_OPERATION | 0x90,
		ERROR_OPERATION_WRITE					= ERROR_OPERATION | 0x80,

		ERROR_MEDIA								= ERROR_OPERATION | 0x40,
		ERROR_MEDIA_UNKNOWN_FAILURE				= ERROR_MEDIA,

		ERROR_MEDIA_OPEN						= ERROR_MEDIA,
		ERROR_MEDIA_OPEN_FAILURE				= ERROR_MEDIA_OPEN,
		ERROR_MEDIA_OPEN_FILE_NOT_FOUND			= ERROR_MEDIA | 0x08,
		ERROR_MEDIA_OPEN_FILE_FORMAT			= ERROR_MEDIA | 0x04,
		ERROR_MEDIA_OPEN_FILE_EMPTY				= ERROR_MEDIA | 0x02,

		ERROR_MEDIA_ALLOCATE					= ERROR_MEDIA | ERROR_OPERATION_CREATE,
		ERROR_MEDIA_ALLOCATE_FAILURE			= ERROR_MEDIA_ALLOCATE,
		ERROR_MEDIA_ALLOCATE_INTERRUPTED		= ERROR_MEDIA_ALLOCATE | ERROR_OPERATION_INTERRUPTED,

		ERROR_MEDIA_ERASE						= ERROR_MEDIA | ERROR_OPERATION_DELETE,
		ERROR_MEDIA_ERASE_FAILURE				= ERROR_MEDIA_ERASE,

		ERROR_MEDIA_READ						= ERROR_MEDIA | ERROR_OPERATION_READ,
		ERROR_MEDIA_READ_FAILURE				= ERROR_MEDIA_READ,
		ERROR_MEDIA_READ_BAD_ADDRESS			= ERROR_MEDIA_READ | 0x08,
		ERROR_MEDIA_READ_INTERRUPTED			= ERROR_MEDIA_READ | ERROR_OPERATION_INTERRUPTED,

		ERROR_MEDIA_WRITE						= ERROR_MEDIA | ERROR_OPERATION_WRITE,
		ERROR_MEDIA_WRITE_FAILURE				= ERROR_MEDIA_WRITE,
		ERROR_MEDIA_WRITE_INTERRUPTED			= ERROR_MEDIA_WRITE | ERROR_OPERATION_INTERRUPTED,
	};

	typedef enum DbResult DBRESULT, * PDBRESULT, & RDBRESULT, ** PPDBRESULT;
	typedef const enum DbResult CDBRESULT, * PCDBRESULT, & RCDBRESULT, ** PPCDBRESULT;

#pragma endregion


#pragma region [IDbTableDef] DEFINITION

	class IDbTableDef : public IStorable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbTableDef() { }


		// ACCESSORS

		VIRTUAL CSIZE RowSize() const = 0;

		VIRTUAL DWORD GetAddrOffset() const = 0;
		VIRTUAL PCCHAR GetTableName() const = 0;


		// MUTATORS

		VIRTUAL VOID SetAddrOffset(RCDWORD) = 0;
		VIRTUAL VOID SetTableName(PCCHAR) = 0;


	protected:

		friend class DbTable;


		// [IDbTableDef] IHELPER METHODS

		VIRTUAL CBYTE TableNameLength() const = 0;


		IDbTableDef() { }
	};

#pragma endregion


#pragma region [DbTableDef] DEFINITION

	class DbTableDef : public IDbTableDef
	{
	protected:

		// CONSTRUCTORS

		DbTableDef(CSIZE = 0, PCCHAR = NULL, RCDWORD = 0);

		EXPLICIT DbTableDef(PCBYTE);
		EXPLICIT DbTableDef(PCCHAR);


		// STATIC FUNCTIONS

		STATIC RDBTABLEDEF NULL_OBJECT();


	public:

		// DESTRUCTOR

		VIRTUAL ~DbTableDef();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:


		// [IDbTableDef] IMPLEMENTATION

		VIRTUAL CSIZE RowSize() const;

		VIRTUAL DWORD GetAddrOffset() const;
		VIRTUAL PCCHAR GetTableName() const;

		VIRTUAL VOID SetAddrOffset(RCDWORD);
		VIRTUAL VOID SetTableName(PCCHAR);


		// [IStorable] IMPLEMENTATION

		VIRTUAL CSTORAGERESULT SaveAsBinary(RCISTORAGE) const;
		VIRTUAL CSTORAGERESULT SaveAsString(RCISTORAGE) const;

		VIRTUAL CSTORAGERESULT LoadFromBinary(RCISTORAGE);
		VIRTUAL CSTORAGERESULT LoadFromString(RCISTORAGE);


		// [ISerializable] IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);

	#ifdef ARDUINO
		VIRTUAL SIZE printTo(Print &) const;
	#endif


	protected:

		friend class DbTableDefSet;
		friend class DbTable;


		// INSTANCE VARIABLES

		SIZE _RowSize = 0;
		PCCHAR _TableName = NULL;
		DWORD _AddrOffset = 0;


		// [IDbTableDef] IHELPER METHODS

		VIRTUAL CBYTE TableNameLength() const;
	};

#pragma endregion


#pragma region [TypedDbTableDef] DEFINITION

	template<typename T>
	CLASS TypedDbTableDef : public DbTableDef
	{
	public:

		// TYPEDEF ALIASES

		typedef T ROW_TYPE;


		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CSIZE ROW_SIZE()
		{
			return T_SIZE;
		}


	protected:

		// CONSTRUCTORS

		TypedDbTableDef(PCCHAR tableName = NULL, RCDWORD addrOffset = 0)
			: DbTableDef(ROW_SIZE(), tableName, addrOffset) { }


	public:

		friend class TypedDbTable<T>;


		// [DbTableDef] OVERRIDES

		CSIZE RowSize() const
		{
			return ROW_SIZE();
		}
	};

#pragma endregion


#pragma region [IDbTableDefSet] DEFINITION

	CLASS IDbTableDefSet : public IStorable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbTableDefSet() { }


		// ACCESSORS

		VIRTUAL CBYTE TableDefCount() const = 0;

		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const = 0;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0) = 0;

		VIRTUAL RCIDBTABLEDEF TableDef(PCCHAR) const = 0;
		VIRTUAL RIDBTABLEDEF TableDef(PCCHAR) = 0;


		// INTERFACE METHODS

		VIRTUAL CSTORAGERESULT MoveTables(CBYTE, RCDWORD) = 0;


	protected:

		// HELPER METHODS

		VIRTUAL CSIZE TableDefsByteSize() const = 0;
		VIRTUAL CSIZE TableDefsStringSize() const = 0;


		IDbTableDefSet() { }
	};

#pragma endregion


#pragma region [DbTableDefSet] DEFINITION

	CLASS DbTableDefSet : public IDbTableDefSet
	{
	protected:

		// CONSTRUCTORS/DESTRUCTOR

		DbTableDefSet(CBYTE = 0);

		EXPLICIT DbTableDefSet(PCBYTE);
		EXPLICIT DbTableDefSet(PCCHAR);

		DbTableDefSet(RCIDBTABLEDEF);
		DbTableDefSet(CBYTE, PPIDBTABLEDEF);


	public:

		VIRTUAL ~DbTableDefSet();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// OPERATORS

		VIRTUAL PCIDBTABLEDEF operator[](CBYTE) const;
		VIRTUAL PIDBTABLEDEF operator[](CBYTE);


		// [IDbTableDefSet] IMPLEMENTATION

		VIRTUAL CBYTE TableDefCount() const;

		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0);

		VIRTUAL RCIDBTABLEDEF TableDef(PCCHAR) const;
		VIRTUAL RIDBTABLEDEF TableDef(PCCHAR);


		// [IStorable] IMPLEMENTATION

		VIRTUAL CSTORAGERESULT SaveAsBinary(RCISTORAGE) const;
		VIRTUAL CSTORAGERESULT SaveAsString(RCISTORAGE) const;

		VIRTUAL CSTORAGERESULT LoadFromBinary(RCISTORAGE);
		VIRTUAL CSTORAGERESULT LoadFromString(RCISTORAGE);


		// [ISerializable] IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);

	#ifdef ARDUINO
		VIRTUAL SIZE printTo(Print &) const;
	#endif


	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		BYTE _TableDefCount = 0;
		PPIDBTABLEDEF _TableDefs = NULL;


		// [IDbTableDefSet] HELPER METHODS

		VIRTUAL CSIZE TableDefsByteSize() const;
		VIRTUAL CSIZE TableDefsStringSize() const;
	};

#pragma endregion


#pragma region [GenericDbTableDefSet] DEFINITION

	template<CBYTE TableDefCount>
	CLASS GenericDbTableDefSet : public DbTableDefSet
	{
	public:

		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE TABLE_DEF_COUNT()
		{
			return TableDefCount;
		}


	protected:

		// CONSTRUCTORS

		GenericDbTableDefSet() : DbTableDefSet(TableDefCount) { }

		GenericDbTableDefSet(PPIDBTABLEDEF tableDefs)
			: DbTableDefSet(TableDefCount, tableDefs) { }


	public:

		// [DbTableDefSet] OVERRIDES

		CBYTE TableDefCount() const
		{
			return TABLE_DEF_COUNT();
		}


	protected:

		friend class Database;


		using DbTableDefSet::_Dispose;
		using DbTableDefSet::_TableDefs;
	};

#pragma endregion
}

#endif
