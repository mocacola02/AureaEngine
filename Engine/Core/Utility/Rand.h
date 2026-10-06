#pragma once

#include "../Math/Int.h"

#include <pcg_random.hpp>

namespace Rand
{
	namespace Internal
	{
		inline pcg32 Generator;

		inline uint32 NextUInt32()
		{
			return Generator();
		}

		inline uint64 NextUInt64()
		{
			return (static_cast<uint64>(Generator()) << 32) |
					static_cast<uint64>(Generator());
		}

		template<typename T>
		T UnsignedRange(T min, T max)
		{
			const uint64 range = static_cast<uint64>(max) - static_cast<uint64>(min) + 1;

			if (range == 0)
			{
				return min + static_cast<T>(NextUInt64());
			}

			const uint64 threshold = -range % range;

			uint64 value = 0;

			while (value < threshold)
			{
				value = NextUInt64();
			}

			return static_cast<T>(static_cast<uint64>(min) + (value % range));
		}

		template<typename T>
		T SignedRange(T min, T max)
		{
			const uint64 range = static_cast<uint64>(max) - static_cast<uint64>(min) + 1;

			if (range == 0)
			{
				return static_cast<T>(static_cast<int64>(NextUInt64()));
			}

			const uint64 threshold = -range % range;

			uint64 value = 0;

			while (value < threshold)
			{
				value = NextUInt64();
			}

			return static_cast<T>(static_cast<uint64>(min) + (value % range));
		}

		inline float UnitFloat()
		{
			return static_cast<float>(NextUInt32() >> 8) * (1.0f / 16777216.0f);
		}

		inline double UnitDouble()
		{
			return static_cast<double>(NextUInt64() >> 11) * (1.0 / 9007199254740992.0);
		}
	}

	inline void Seed(uint64 seed, uint64 stream = 1)
	{
		Internal::Generator.seed(seed, stream);
	}

	inline uint8 RandUInt8()
	{
		return static_cast<uint8>(Internal::NextUInt32());
	}

	inline uint16 RandUInt16()
	{
		return static_cast<uint16>(Internal::NextUInt32());
	}

	inline uint32 RandUInt32()
	{
		return Internal::NextUInt32();
	}

	inline uint64 RandUInt64()
	{
		return Internal::NextUInt64();
	}

	inline int8 RandInt8()
	{
		return Internal::SignedRange<int8>(MinInt<int8>, MaxInt<int8>);
	}

	inline int16 RandInt16()
	{
		return Internal::SignedRange<int16>(MinInt<int16>, MaxInt<int16>);
	}

	inline int32 RandInt32()
	{
		return Internal::SignedRange<int32>(MinInt<int32>, MaxInt<int32>);
	}

	inline int64 RandInt64()
	{
		return Internal::SignedRange<int64>(MinInt<int64>, MaxInt<int64>);
	}

	inline float RandF()
	{
		return Internal::UnitFloat();
	}

	inline double Rand()
	{
		return Internal::UnitDouble();
	}

	inline uint8 RandRangeUInt8(const uint8 min, const uint8 max)
	{
		return Internal::UnsignedRange<uint8>(min, max);
	}

	inline uint16 RandRangeUInt16(const uint16 min, const uint16 max)
	{
		return Internal::UnsignedRange<uint16>(min, max);
	}

	inline uint32 RandRangeUInt32(const uint32 min, const uint32 max)
	{
		return Internal::UnsignedRange<uint32>(min, max);
	}

	inline uint64 RandRangeUInt64(const uint64 min, const uint64 max)
	{
		return Internal::UnsignedRange<uint64>(min, max);
	}

	inline int8 RandRangeInt8(const int8 min, const int8 max)
	{
		return Internal::SignedRange<int8>(min, max);
	}

	inline int16 RandRangeInt16(const int16 min, const int16 max)
	{
		return Internal::SignedRange<int16>(min, max);
	}

	inline int32 RandRangeInt32(const int32 min, const int32 max)
	{
		return Internal::SignedRange<int32>(min, max);
	}

	inline int64 RandRangeInt64(const int64 min, const int64 max)
	{
		return Internal::SignedRange<int64>(min, max);
	}

	inline float RandRangeF(const float min, const float max)
	{
		return min + (Internal::UnitFloat() * (max - min));
	}

	inline double RandRange(const double min, const double max)
	{
		return min + (Internal::UnitDouble() * (max - min));
	}
}