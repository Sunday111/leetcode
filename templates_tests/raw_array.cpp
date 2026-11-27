#include "raw_array.hpp"

#include <type_traits>

static_assert(std::is_empty_v<RawArray<int, 0>>);
static_assert(std::is_aggregate_v<RawArray<int, 3>>);

constexpr auto squares = []
{
    RawArray<int, 3> result{};
    for (int i = 0; i != 3; ++i) result.data[i] = i * i;
    return result;
}();

static_assert(std::is_same_v<decltype(squares.data), int[3]>);
static_assert(
    squares.data[0] == 0 && squares.data[1] == 1 && squares.data[2] == 4);
