#pragma once

#include "tuple_split.hpp"

template <is_specialization<std::tuple> T, std::size_t k>
using tuple_head =
    std::remove_reference_t<decltype(std::get<0>(tuple_split<k>(T{})))>;
