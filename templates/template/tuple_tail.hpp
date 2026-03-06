#pragma once

#include "tuple_split.hpp"

template <is_specialization<std::tuple> T, std::size_t k>
using tuple_tail =
    std::remove_reference_t<decltype(std::get<1>(tuple_split<k>(T{})))>;
