#pragma once
#include <cstdint>
#include <limits>

namespace Bake {
#define BIT(x) (1 << x)
	using c8 = char;

	using i32 = int32_t;
	using i16 = int16_t;
	using i8 = int8_t;

	using f32 = float;
	using f64 = double;

	using u32 = uint32_t;
	using u16 = uint16_t;
	using u8 = uint8_t;

	using b8 = bool;

	using usize = size_t;
	using uptr = uintptr_t;

	inline constexpr u32 u32_max = std::numeric_limits<u32>::max();
	inline constexpr u16 u16_max = std::numeric_limits<u16>::max();
	inline constexpr u8 u8_max = std::numeric_limits<u8>::max();

	inline constexpr i32 i32_max = std::numeric_limits<i32>::max();
	inline constexpr i16 i16_max = std::numeric_limits<i16>::max();
	inline constexpr i8 i8_max = std::numeric_limits<i8>::max();
}