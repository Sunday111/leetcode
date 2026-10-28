#pragma once

#include <bit>
#include <cstddef>

[[nodiscard, gnu::always_inline]] constexpr std::size_t st_required_buffer_size(
    std::size_t n) noexcept
{
    return n * static_cast<std::size_t>(std::bit_width(n));
}
