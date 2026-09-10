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