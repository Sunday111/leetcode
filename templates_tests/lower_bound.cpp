#include "lower_bound.hpp"

#include <gtest/gtest.h>

#include <limits>

#include "integral_aliases.hpp"

TEST(LowerBound, EveryPartition)
{
    for (int size = 0; size != 32; ++size)
    {
        for (int split = 0; split != size + 1; ++split)
        {
            EXPECT_EQ(
                lower_bound(0, size, [split](int i) { return i >= split; }),
                split);
        }
    }
}

template <typename T>
constexpr bool check_extremes()
{
    constexpr T first = std::numeric_limits<T>::min();
    constexpr T last = std::numeric_limits<T>::max();
    for (T split : {first, T{0}, static_cast<T>(last - 1), last})
    {
        if (lower_bound(first, last, [split](T i) { return i >= split; }) !=
            split)
        {
            return false;
        }
    }
    return true;
}

static_assert(check_extremes<signed char>());
static_assert(check_extremes<u8>());
static_assert(check_extremes<long long>());
static_assert(check_extremes<u64>());
