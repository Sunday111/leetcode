#pragma once

#include <cassert>
#include <limits>

#include "ctz.hpp"
#include "pyramid_bitset/pbs_layers.hpp"
#include "pyramid_bitset/pyramid_bitset.hpp"  // IWYU pragma: export
#include "uint_for_value.hpp"

// Inclusive successor; returns capacity when absent.
// One top-down pass takes O(log_word_size(capacity)).
template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr UintForValue<capacity>
pbs_next_inclusive(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType position) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    using Index = UintForValue<capacity>;
    constexpr Index index_mask = std::numeric_limits<Index>::max();
    assert(position < capacity);
    typename B::WordType first_word = bits.words[position >> B::kShift];
    first_word >>= position & B::kMask;
    if (first_word != 0)
    {
        Index result = (Index{position} + ctz(first_word)) & index_mask;
        if (result > capacity) result = capacity;
        return result;
    }
    Index result = capacity;
    pbs_for_each_layer_reversed<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            constexpr Index offset = B::offsets[layer];
            constexpr Index layer_size = B::kLayersSizes[layer];
            if constexpr (layer + 1 < B::kNumLayers)
            {
                if (result < layer_size)
                {
                    const Word word = bits.words[offset + result];
                    u8 first = B::kWordSize;
                    if (word != 0) first = ctz(word);
                    result = ((result << B::kShift) + first) & index_mask;
                }
                else
                {
                    result = capacity;
                }
            }

            // A neighbour on the query's path is closer than the fallback.
            const Index query = position >> (layer * B::kShift);
            const Index wi = query >> B::kShift;
            const u8 bi = query & B::kMask;
            typename B::WordType candidates = bits.words[offset + wi];
            // Separate shifts avoid shifting by the word width.
            constexpr u8 skip = layer != 0;
            candidates >>= bi;
            candidates >>= skip;
            u8 first = B::kWordSize;
            if (candidates != 0) first = ctz(candidates);
            const Index candidate = (query + skip + first) & index_mask;
            const Index mask = (Index{0} - Index{candidates != 0}) & index_mask;
            result ^= (result ^ candidate) & mask;
        });
    if (result > capacity) result = capacity;
    return result;
}
