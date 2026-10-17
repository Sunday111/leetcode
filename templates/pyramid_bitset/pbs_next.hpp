#pragma once

#include <algorithm>
#include <cassert>

#include "cast.hpp"
#include "pyramid_bitset/pbs_layers.hpp"
#include "pyramid_bitset/pyramid_bitset.hpp"  // IWYU pragma: export

// Strict successor; returns capacity when absent.
// One top-down pass takes O(log_word_size(capacity)).
template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr size_t pbs_next(
    const PyramidBitset<capacity, Word>& bits,
    size_t position) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    assert(position < capacity);
    size_t result = capacity;
    pbs_for_each_layer_reversed<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            if constexpr (layer + 1 < B::kNumLayers)
            {
                // Refine the fallback from above. Padding bits and the
                // absent sentinel must never become word indices.
                const size_t valid_mask =
                    size_t{0} - size_t{result < B::kLayersSizes[layer]};
                const Word word =
                    bits.words[B::offsets[layer] + (result & valid_mask)];
                const size_t descendant = (result << B::kShift) +
                                          cast<size_t>(std::countr_zero(word));
                result = (descendant & valid_mask) | (capacity & ~valid_mask);
            }

            // A neighbour on the query's path is closer than the fallback.
            const size_t query = position >> (layer * B::kShift);
            const size_t wi = query >> B::kShift;
            const size_t bi = query & B::kMask;
            Word candidates = bits.words[B::offsets[layer] + wi];
            // Separate shifts avoid shifting by the word width.
            candidates >>= bi;
            candidates >>= 1;
            const size_t candidate =
                query + 1 + cast<size_t>(std::countr_zero(candidates));
            const size_t mask = size_t{0} - size_t{candidates != 0};
            result ^= (result ^ candidate) & mask;
        });
    return std::min(result, capacity);
}
