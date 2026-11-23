#pragma once

#include <cstddef>
#include <type_traits>

#include "bitsets/bitset_view/bitset_view.hpp"  // IWYU pragma: export
#include "bitsets/bitset_view/bsv_set_if.hpp"

template <bool value, BitsetWord Word, std::size_t extent>
    requires(!std::is_const_v<Word>)
[[gnu::always_inline]] constexpr void bsv_set(
    BitsetView<Word, extent> bits,
    std::size_t index) noexcept
{
    bsv_set_if<value>(bits, index, true);
}
