/***********************************************************************************************
* [IttyBitty_storage.h]: DATA PERSISTENCE TO NON-VOLATILE MEDIA
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_STORAGE_H
#define _ITTYBITTY_STORAGE_H


#include "IttyBitty_datum.h"


#pragma region DEFINES



#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	union StorageLocation;
	TYPEDEF_UNION_ALIASES(StorageLocation, STORAGELOCATION);

	class IStorable;
	TYPEDEF_CLASS_ALIASES(IStorable, ISTORABLE);

	class IStorage;
	TYPEDEF_CLASS_ALIASES(IStorage, ISTORAGE);

	class NullStorage;
	TYPEDEF_CLASS_ALIASES(NullStorage, NULLSTORAGE);

	class StorageBase;
	TYPEDEF_CLASS_ALIASES(StorageBase, STORAGEBASE);

#pragma endregion


#pragma region ENUMS

	ENUM StorageResult : BYTE
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
		ERROR_OPERATION_UNKNOWN					= ERROR_OPERATION,
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
		ERROR_MEDIA_WRITE_NOT_ALLOWED			= ERROR_MEDIA_WRITE,
		ERROR_MEDIA_WRITE_INTERRUPTED			= ERROR_MEDIA_WRITE | ERROR_OPERATION_INTERRUPTED,
	};

	TYPEDEF_ENUM_ALIASES(StorageResult, STORAGERESULT);

#pragma endregion


#pragma region [StorageLocation] DEFINITION

	UNION PACKED StorageLocation
	{
		// UNION MEMBERS

		PCCHAR FilePath;

		BYTE ByteAddress;
		WORD WordAddress;
		DWORD DWordAddress;



		// CONSTRUCTORS/DESTRUCTOR

		StorageLocation(PCCHAR filePath) : FilePath(filePath) { }

		EXPLICIT StorageLocation(BYTE byteAddress) : ByteAddress(byteAddress) { }

		EXPLICIT StorageLocation(WORD wordAddress) : WordAddress(wordAddress) { }

		StorageLocation(RCDWORD dwordAddress = 0) : DWordAddress(dwordAddress) { }

		StorageLocation(RCSTORAGELOCATION other)
		{
			this->DWordAddress = other.DWordAddress;
		}

		StorageLocation(RRSTORAGELOCATION other)
		{
			new (this) StorageLocation(other.DWordAddress);
		}

		~StorageLocation()
		{
			this->FreeFilePath();
		}


		// STATIC FUNCTIONS

		STATIC RCSTORAGELOCATION NULL_OBJECT()
		{
			STATIC STORAGELOCATION NULL_STORAGELOCATION;
			return NULL_STORAGELOCATION;
		}


		// OPERATORS

		RSTORAGELOCATION operator =(RCSTORAGELOCATION rValue)
		{
			*this = StorageLocation(rValue);
			return *this;
		}

		RSTORAGELOCATION operator =(RRSTORAGELOCATION rValue)
		{
			*this = StorageLocation(rValue);
			return *this;
		}

		RSTORAGELOCATION operator =(PCCHAR rValue)
		{
			this->FilePath = rValue;
			return *this;
		}

		RSTORAGELOCATION operator =(CBYTE rValue)
		{
			this->ByteAddress = rValue;
			return *this;
		}

		RSTORAGELOCATION operator =(CWORD rValue)
		{
			this->WordAddress = rValue;
			return *this;
		}

		RSTORAGELOCATION operator =(RCDWORD rValue)
		{
			this->DWordAddress = rValue;
			return *this;
		}

		operator PCCHAR() const
		{
			return this->FilePath;
		}

		operator CBYTE() const
		{
			return this->ByteAddress;
		}

		operator CWORD() const
		{
			return this->WordAddress;
		}

		operator RCDWORD() const
		{
			return this->DWordAddress;
		}


		// USER METHODS

		VOID FreeFilePath()
		{
			if (this->FilePath)
			{
				delete[] this->FilePath;
				this->FilePath = NULL;
			}
		}
	};

#pragma endregion


#pragma region [IStorable] DEFINITION

	CLASS IStorable : public ISerializable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IStorable() { }


		// INTERFACE METHODS

		VIRTUAL CSTORAGERESULT Load() = 0;
		VIRTUAL CSTORAGERESULT Save() = 0;

		VIRTUAL CSTORAGERESULT SaveAsBinary() const = 0;
		VIRTUAL CSTORAGERESULT SaveAsString() const = 0;

		VIRTUAL CSTORAGERESULT LoadFromBinary() = 0;
		VIRTUAL CSTORAGERESULT LoadFromString() = 0;


	protected:

		IStorable() { }
	};

#pragma endregion


#pragma region [IStorage] DEFINITION

	CLASS IStorage
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IStorage() { }


		// ACCESSOR/MUTATOR

		VIRTUAL RCSTORAGELOCATION GetStorageLocation() const = 0;
		VIRTUAL VOID SetStorageLocation(RCSTORAGELOCATION) = 0;


		// INTERFACE METHODS

		VIRTUAL CDWORD Capacity() = 0;

		VIRTUAL CBOOL Available() = 0;

		VIRTUAL CSTORAGERESULT Open(CBOOL = FALSE) = 0;
		VIRTUAL CSTORAGERESULT Close() = 0;

		VIRTUAL CSTORAGERESULT Seek(RCDWORD) = 0;

		VIRTUAL CSTORAGERESULT Read(PBYTE, CSIZE) = 0;
		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE) = 0;

		VIRTUAL CSTORAGERESULT Flush() = 0;



	protected:

		IStorage() { }
	};

#pragma endregion


#pragma region [NullStorage] DEFINITION

	CLASS NullStorage final : public IStorage
	{
	public:

		// CONSTRUCTOR

		NullStorage() { }


		// STATIC FUNCTIONS

		STATIC RNULLSTORAGE NULL_OBJECT()
		{
			STATIC NULLSTORAGE NULL_STORAGE;
			return NULL_STORAGE;
		}


		// [IStorage] ACCESSOR/MUTATOR

		VIRTUAL RCSTORAGELOCATION GetStorageLocation() const
		{
			return StorageLocation::NULL_OBJECT();
		}

		VIRTUAL VOID SetStorageLocation(RCSTORAGELOCATION location) { }


		// [IStorage] IMPLEMENTATION

		VIRTUAL CDWORD Capacity()
		{
			return 0;
		}

		VIRTUAL CBOOL Available()
		{
			return TRUE;
		}

		VIRTUAL CSTORAGERESULT Open(CBOOL = FALSE)
		{
			return StorageResult::SUCCESS;
		}

		VIRTUAL CSTORAGERESULT Close()
		{
			return StorageResult::SUCCESS;
		}

		VIRTUAL CSTORAGERESULT Seek(RCDWORD)
		{
			return StorageResult::SUCCESS;
		}

		VIRTUAL CSTORAGERESULT Read(PBYTE, CSIZE)
		{
			return StorageResult::SUCCESS;
		}

		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE)
		{
			return StorageResult::SUCCESS;
		}

		VIRTUAL CSTORAGERESULT Flush()
		{
			return StorageResult::SUCCESS;
		}
	};


	// GLOBAL NULL STORAGE REFERENCE FUNCTION

	STATIC RISTORAGE NULL_STORAGE()
	{
		return NullStorage::NULL_OBJECT();
	}

#pragma endregion


#pragma region [StorageBase] DEFINITION

	CLASS StorageBase : public IStorage
	{
	public:

		// CONSTRUCTOR/DESTRUCTOR

		StorageBase(RCSTORAGELOCATION location = StorageLocation::NULL_OBJECT()) : _Location(location) { }

		VIRTUAL ~StorageBase()
		{
			this->Close();
		}


		// [IStorage] ACCESSOR/MUTATOR

		VIRTUAL RCSTORAGELOCATION GetStorageLocation() const
		{
			return _Location;
		}

		VIRTUAL VOID SetStorageLocation(RCSTORAGELOCATION location)
		{
			_Location = location;
		}


		// USER METHODS

		VIRTUAL CDWORD Capacity()
		{
			return 0;
		}

		VIRTUAL CBOOL Available()
		{
			return TRUE;
		}

		VIRTUAL CSTORAGERESULT Open(CBOOL rwFlag)
		{
			return StorageResult::SUCCESS;
		}

		VIRTUAL CSTORAGERESULT Close()
		{
			return StorageResult::SUCCESS;
		}

		VIRTUAL CSTORAGERESULT Seek(RCDWORD address)
		{
			this->_Location.DWordAddress = address;

			return StorageResult::SUCCESS;
		}

		VIRTUAL CSTORAGERESULT Flush()
		{
			return StorageResult::SUCCESS;
		}


	protected:

		// INSTANCE VARIABLES

		STORAGELOCATION _Location = StorageLocation();
	};

#pragma endregion
}

#endif
