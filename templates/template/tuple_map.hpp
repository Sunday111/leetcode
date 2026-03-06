#pragma once

#include <tuple>

#include "concept/is_specialization.hpp"

template <template <typename> typename Converter, typename X>
struct TupleMapImpl;

template <template <typename> typename Converter, typename... Args>
struct TupleMapImpl<Converter, std::tuple<Args...>>
{
    using Result = std::tuple<Converter<Args>...>;
};

template <
    is_specialization<std::tuple> X,
    template <typename> typename Converter>
using tuple_map = typename TupleMapImpl<Converter, X>::Result;
