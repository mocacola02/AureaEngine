#pragma once

#include "Hash.h"
#include "../Math/Math.h"

#include <SDL3/SDL_stdinc.h>

struct UUID
{
	uint128 value;

	constexpr UUID() = default;
	constexpr UUID(const uint64 low, const uint64 high) : value(uint128(low, high)) {}

	static UUID Generate()
	{
		uint64 low  = (static_cast<uint64>(SDL_rand_bits()) << 32ULL) | static_cast<uint64>(SDL_rand_bits());
		uint64 high = (static_cast<uint64>(SDL_rand_bits()) << 32ULL) | static_cast<uint64>(SDL_rand_bits());

		low  &= 0x3FFFFFFFFFFFFFFFULL;
		low  |= 0x8000000000000000ULL;

		high &= 0xFFFFFFFFFFFF0FFFULL;
		high |= 0x0000000000004000ULL;

		return UUID(low, high);
	}

	constexpr bool IsValid() const
	{
		return value.low != 0 || value.high != 0;
	}

	constexpr void Clear()
	{
		value.Clear();
	}

	constexpr bool operator==(const UUID& other) const
	{
		return value == other.value;
	}

	constexpr bool operator!=(const UUID& other) const
	{
		return !(*this == other);
	}

	constexpr bool operator<(const UUID& other) const
	{
		return value < other.value;
	}

	constexpr bool operator<=(const UUID& other) const
	{
		return value <= other.value;
	}

	constexpr bool operator>(const UUID& other) const
	{
		return value > other.value;
	}

	constexpr bool operator>=(const UUID& other) const
	{
		return value >= other.value;
	}

	constexpr explicit operator bool() const
	{
		return IsValid();
	}
};

template<>
struct Hash<UUID>
{
	static constexpr uint64 Get(const UUID& uuid)
	{
		return Hashing::Combine64(uuid.value.high, uuid.value.low);
	}
};