#pragma once

#include "NameTable.h"
#include "../Math/Int.h"


class Name
{
public:
	Name() : id_(0) {}

	explicit Name(const char* value) : id_(NameTable::Get().FindOrAdd(value)) {}

	[[nodiscard]] const char* CStr() const
	{
		return NameTable::Get().GetString(id_);
	}

	[[nodiscard]] uint32 Length() const
	{
		return NameTable::Get().GetLength(id_);
	}

	[[nodiscard]] uint32 ID() const
	{
		return id_;
	}

	[[nodiscard]] bool IsEmpty() const
	{
		return id_ == 0;
	}

	static Name None()
	{
		return {};
	}

	// Operators

	bool operator==(const Name& other) const
	{
		return id_ == other.id_;
	}

	bool operator!=(const Name& other) const
	{
		return id_ != other.id_;
	}

private:
	uint32 id_;
};

template<>
struct Hash<Name>
{
	static uint32 Get(const Name& value)
	{
		return Hashing::Mix32(value.ID());
	}
};