/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (defined(ITTYBITTY_SLIM) || defined(EXCLUDE_ITTYBITTY_DB)) && !defined(EXCLUDE_ITTYBITTY_DB_TABLES)
	#define EXCLUDE_ITTYBITTY_DB_TABLES
#endif

#ifndef EXCLUDE_ITTYBITTY_DB_TABLES


#include "IttyBitty_DB_tables.h"

using namespace IttyBitty;


#pragma region [DbTable] IMPLEMENTATION
/*
// CONSTRUCTORS/DESTRUCTOR

DbTable::DbTable()
{
}

DbTable::DbTable(PCBYTE)
{
}

DbTable::DbTable(PCCHAR)
{
}

DbTable::~DbTable()
{
}

		
// PROTECTED DISPOSAL METHOD

VOID DbTable::Dispose()
{
}


// [IDbTable] IMPLEMENTATION
		
CDWORD DbTable::Size() const
{
}

CDWORD DbTable::Capacity() const
{
}

CSIZE DbTable::RowCount() const
{
}

CSIZE DbTable::RowsAvailable() const
{
}

CDBRESULT DbTable::Grow(CDWORD, CBOOL = FALSE)
{
}

CDBRESULT DbTable::Shrink(CDWORD, CBOOL = FALSE)
{
}

CDBRESULT DbTable::SelectAll(PBYTE &, RSIZE)
{
}

CDBRESULT DbTable::Find(CSIZE, PBYTE, PSIZE = NULL)
{
}

CDBRESULT DbTable::Insert(PCBYTE, CSIZE = MAX_DbTable::T(SIZE))
{
}

CDBRESULT DbTable::Update(PCBYTE, CSIZE, PSIZE = NULL)
{
}

CDBRESULT DbTable::Delete(CSIZE)
{
}

CDBRESULT DbTable::Truncate()
{
}
				

// [IStorable] IMPLEMENTATION

MEDIARESULT DbTable::SaveAsBinary(RCISTORAGE) const
{
}

MEDIARESULT DbTable::SaveAstring(RCISTORAGE) const
{
}

MEDIARESULT DbTable::LoadFromBinary(RCISTORAGE)
{
}

MEDIARESULT DbTable::LoadFromString(RCISTORAGE)
{
}


// [ISerializable] IMPLEMENTATION

CSIZE DbTable::BinarySize() const
{
}

CSIZE DbTable::StringSize() const
{
}

CSIZE DbTable::ByteWidth() const
{
}

CSIZE DbTable::StringLength() const
{
}

PCBYTE DbTable::ToBinary() const
{
}

PCCHAR DbTable::ToString() const
{
}

VOID DbTable::FromBinary(PCBYTE)
{
}

VOID DbTable::FromString(PCCHAR)
{
}
		
#ifdef ARDUIN

SIZE DbTable::printTo(Print &) const
{
}

#endif
*/
#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB_TABLES