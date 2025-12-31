#include <concepts>

#include "uint_for_value.hpp"

static_assert(std::same_as<UintForValue<(1 << 8) - 1>, u8>);
static_assert(std::same_as<UintForValue<(1 << 8)>, u16>);
static_assert(std::same_as<UintForValue<(1 << 16) - 1>, u16>);
static_assert(std::same_as<UintForValue<(1 << 16)>, u32>);
static_assert(std::same_as<UintForValue<(1ul << 32) - 1>, u32>);
static_assert(std::same_as<UintForValue<(1ul << 32)>, u64>);
static_assert(std::same_as<UintForValue<~u64{}>, u64>);
