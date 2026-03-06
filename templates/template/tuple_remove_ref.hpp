#pragma once

#include <type_traits>

#include "tuple_map.hpp"

template <is_specialization<std::tuple> X>
using tuple_remove_ref = tuple_map<X, std::remove_reference_t>;
