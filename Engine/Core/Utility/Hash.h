#pragma once

#include "../Math/Int.h"


template<typename T>
struct Hash;

namespace Hashing
{
	constexpr uint64 Mix64(uint64 value)
	{
		value ^= value >> 30ULL;
		value *= 0xbf58476d1ce4e5b9ULL;

		value ^= value >> 27ULL;
		value *= 0x94d049bb133111ebULL;

		value ^= value >> 31ULL;

		return value;
	}

	constexpr uint32 Mix32(uint32 value)
	{
		value ^= value >> 16U;
		value *= 0x7feb352dU;

		value ^= value >> 15U;
		value *= 0x846ca68bU;

		value ^= value >> 16U;

		return value;
	}

	constexpr uint64 Combine64(const uint64 first, const uint64 second)
	{
		return Mix64(first ^ second + 0x9e3779b97f4a7c15ULL + (first << 6ULL) + (first >> 2ULL));
	}

	constexpr uint32 Combine32(const uint32 first, const uint32 second)
	{
		return Mix32(first ^ second + 0x9e3779b9U + (first << 6U) + (first >> 2U));
	}

	constexpr uint32 Fold64To32(const uint64 value)
	{
		return static_cast<uint32>(value ^ (value >> 32ULL));
	}

	constexpr uint32 FNV1a(const char* data, const uint32 length)
	{
		constexpr uint32 offset = 2166136261U;

		uint32 hash = offset;

		if (!data)
		{
			return hash;
		}

		for (uint32 i = 0U; i < length; ++i)
		{
			constexpr uint32 prime = 16777619U;
			hash ^= static_cast<uint8>(data[i]);

			hash *= prime;
		}

		return hash;
	}
}

// Unsigned

template<>
struct Hash<uint8>
{
	static constexpr uint32 Get(const uint8 value)
	{
		return Hashing::Mix32(value);
	}
};

template<>
struct Hash<uint16>
{
	static constexpr uint32 Get(const uint16 value)
	{
		return Hashing::Mix32(value);
	}
};

template<>
struct Hash<uint32>
{
	static constexpr uint32 Get(const uint32 value)
	{
		return Hashing::Mix32(value);
	}
};

template<>
struct Hash<uint64>
{
	static constexpr uint32 Get(const uint64 value)
	{
		return Hashing::Fold64To32(Hashing::Mix64(value));
	}
};

// Signed

template<>
struct Hash<int8>
{
	static constexpr uint32 Get(const int8 value)
	{
		return Hashing::Mix32(static_cast<uint32>(value));
	}
};

template<>
struct Hash<int16>
{
	static constexpr uint32 Get(const int16 value)
	{
		return Hashing::Mix32(static_cast<uint32>(value));
	}
};

template<>
struct Hash<int32>
{
	static constexpr uint32 Get(const int32 value)
	{
		return Hashing::Mix32(static_cast<uint32>(value));
	}
};

template<>
struct Hash<int64>
{
	static constexpr uint32 Get(const int64 value)
	{
		return Hashing::Fold64To32(Hashing::Mix64(static_cast<uint64>(value)));
	}
};

// Bool

template<>
struct Hash<bool>
{
	static constexpr uint32 Get(const bool value)
	{
		return Hashing::Mix32(value ? 1U : 0U);
	}
};

// Character

template<>
struct Hash<char>
{
	static constexpr uint32 Get(const char value)
	{
		return Hashing::Mix32(static_cast<uint8>(value));
	}
};

// Pointers
// This hashes the pointer address, not the object being pointed to

template<typename T>
struct Hash<T*>
{
	static uint32 Get(const T* value)
	{
		const auto address = static_cast<uint32>(reinterpret_cast<uintptr>(value));

		return Hashing::Mix32(address);
	}
};