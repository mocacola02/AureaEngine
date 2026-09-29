#pragma once

#include <cstdint>

using int8  = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8  = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using uintptr = uintptr_t;
using intptr  = intptr_t;

template<typename T>
inline constexpr T MinInt;

template<> inline constexpr int8  MinInt<int8> = -128;
template<> inline constexpr int16 MinInt<int16> = -32768;
template<> inline constexpr int32 MinInt<int32> = -2147483647 - 1;
template<> inline constexpr int64 MinInt<int64> = -9223372036854775807LL - 1LL;

template<typename T>
inline constexpr T MaxInt;

template<> inline constexpr int8  MaxInt<int8> = 127;
template<> inline constexpr int16 MaxInt<int16> = 32767;
template<> inline constexpr int32 MaxInt<int32> = 2147483647L;
template<> inline constexpr int64 MaxInt<int64> = 9223372036854775807LL;

template<> inline constexpr uint8  MaxInt<uint8> = 0xFFU;
template<> inline constexpr uint16 MaxInt<uint16> = 0xFFFFU;
template<> inline constexpr uint32 MaxInt<uint32> = 0xFFFFFFFFUL;
template<> inline constexpr uint64 MaxInt<uint64> = 0xFFFFFFFFFFFFFFFFULL;

struct int128
{
	int64 low;
	int64 high;

	constexpr int128() noexcept: low(0), high(0) {}
	constexpr int128(const int64 lowValue, const int64 highValue) noexcept : low(lowValue), high(highValue) {}

	bool operator==(const int128& other) const noexcept
	{
		return low == other.low && high == other.high;
	}

	bool operator!=(const int128& other) const noexcept
	{
		return !(*this == other);
	}

	bool operator<(const int128& other) const noexcept
	{
		if (high < other.high)
		{
			return true;
		}
		if (high > other.high)
		{
			return false;
		}

		return low < other.low;
	}

	bool operator<=(const int128& other) const noexcept
	{
		return other >= *this;
	}

	bool operator>(const int128& other) const noexcept
	{
		return other < *this;
	}

	bool operator>=(const int128& other) const noexcept
	{
		return !(*this < other);
	}
};

struct uint128
{
	uint64 low;
	uint64 high;

	constexpr uint128() noexcept: low(0), high(0) {}
	constexpr uint128(const uint64 lowValue, const uint64 highValue) noexcept : low(lowValue), high(highValue) {}

	constexpr void Clear()
	{
		low  = 0;
		high = 0;
	}

	bool operator==(const uint128& other) const noexcept
	{
		return low == other.low && high == other.high;
	}

	bool operator!=(const uint128& other) const noexcept
	{
		return !(*this == other);
	}

	bool operator<(const uint128& other) const noexcept
	{
		if (high < other.high)
		{
			return true;
		}
		if (high > other.high)
		{
			return false;
		}

		return low < other.low;
	}

	bool operator<=(const uint128& other) const noexcept
	{
		return other >= *this;
	}

	bool operator>(const uint128& other) const noexcept
	{
		return other < *this;
	}

	bool operator>=(const uint128& other) const noexcept
	{
		return !(*this < other);
	}
};