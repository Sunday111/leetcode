#pragma once

#include <bit>
#include <tuple>

#include "ceil_div.hpp"
#include "integral_aliases.hpp"

template <u64 value>
using UintForValue = std::tuple_element_t<
    ceil_div(std::bit_width(value), 8),
    std::tuple<u8, u16, u32, u64>>;
