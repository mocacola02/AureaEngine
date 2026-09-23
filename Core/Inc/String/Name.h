#pragma once

#include "NameTable.h"
#include "String.h"
#include "../Math/Int.h"


class Name
{
public:
	Name() : id_(0) {}

	explicit Name(const char* value, const bool unique = false)
	{
		if (value == nullptr || *value == '\0')
		{
			id_ = 0;
			return;
		}

		if (!unique)
		{
			id_ = NameTable::Get().FindOrAdd(value);
		}
		else
		{
			const uint32 suffix = NameTable::Get().GetUniqueSuffixCounter(value);
			String valueStr = String(value);
			valueStr.Append(String(suffix));
			const char* finalValue = valueStr.CStr();

			id_ = NameTable::Get().FindOrAdd(finalValue);
			NameTable::Get().IncrementUniqueSuffixCounter(finalValue);
		}
	}

	explicit Name(const String& value, const bool unique = false)
	{
		if (value.IsEmpty())
		{
			id_ = 0;
			return;
		}

		if (!unique)
		{
			id_ = NameTable::Get().FindOrAdd(value.CStr());
		}
		else
		{
			const uint32 suffix = NameTable::Get().GetUniqueSuffixCounter(value.CStr());
			String valueStr = value;
			valueStr.Append(String(suffix));
			const char* finalValue = valueStr.CStr();

			id_ = NameTable::Get().FindOrAdd(finalValue);
			NameTable::Get().IncrementUniqueSuffixCounter(finalValue);
		}
	}

	[[nodiscard]] const char* CStr() const
	{
		return NameTable::Get().GetString(id_);
	}

	[[nodiscard]] const String& ToString() const
	{
		return String(CStr());
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