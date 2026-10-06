#pragma once

#include "../Math/Math.h"
#include "Hash.h"

struct UUID
{
	explicit UUID(const uint64 value) : value(value) {}

	uint64 value = 0;

	bool IsValid() const
	{
		return value != 0;
	}

	uint64 Value() const
	{
		return value;
	}

	constexpr UUID operator=(const UUID& other)
	{
		value = other.value;
		return *this;
	}

	constexpr UUID operator=(const uint64 newValue)
	{
		value = newValue;
		return *this;
	}

	constexpr bool operator==(const UUID& other) const
	{
		return value == other.value;
	}

	constexpr bool operator==(const uint64 other) const
	{
		return value == other;
	}

	constexpr bool operator!=(const UUID& other) const
	{
		return !(*this == other);
	}

	constexpr bool operator!=(const uint64 other) const
	{
		return value != other;
	}
};

template<>
struct Hash<UUID>
{
	static constexpr uint32 Get(const UUID& uuid) noexcept
	{
		return Hashing::Fold64To32(Hashing::Mix64(uuid.value));
	}
};