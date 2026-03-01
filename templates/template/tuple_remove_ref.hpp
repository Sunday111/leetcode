#pragma once

#include <tuple>

#include "concept/is_specialization.hpp"

template <typename X>
struct TupleRemoveRefImpl;

template <typename... Args>
struct TupleRemoveRefImpl<std::tuple<Args...>>
{
    using Result = std::tuple<std::remove_reference_t<Args>...>;
};

template <is_specialization<std::tuple> X>
using tuple_remove_ref = typename TupleRemoveRefImpl<X>::Result;
