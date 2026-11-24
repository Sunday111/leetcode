#pragma once

#include <concepts>

#include "integral_aliases.hpp"

// Shared by both sorters. Calls using this storage must not overlap.
struct RadixSortStorage
{
    template <std::unsigned_integral Word, u32 capacity>
    inline static Word scratch[capacity];

    // All digit widths through 16 bits use the same histogram.
    template <u8 bits>
    alignas(u32) inline static u8 counts[sizeof(u32) << bits];
};
