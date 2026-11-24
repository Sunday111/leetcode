#pragma once

#include "pyramid_bitset/pyramid_bitset.hpp"

template <u32 capacity, typename Word = u64>
[[nodiscard]] consteval size_t pbs_required_buffer_words() noexcept
{
    return PyramidBitset<capacity, Word>::kTotalWords;
}
