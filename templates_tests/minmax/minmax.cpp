#include <gtest/gtest.h>

#include <climits>
#include <concepts>

#include "minmax/max3.hpp"
#include "minmax/max4.hpp"
#include "minmax/min3.hpp"
#include "minmax/min4.hpp"
#include "minmax/ref/max3_ref.hpp"
#include "minmax/ref/max4_ref.hpp"
#include "minmax/ref/min3_ref.hpp"
#include "minmax/ref/min4_ref.hpp"

namespace
{
constexpr bool
matches(auto value, auto ref, const int& expected, const auto&... args)
{
    static_assert(std::same_as<decltype(value(args...)), int>);
    static_assert(std::same_as<decltype(ref(args...)), const int&>);
    return value(args...) == expected && &ref(args...) == &expected;
}
}  // namespace

TEST(MinMax, ValuesAndReferences)
{
    constexpr int low = INT_MIN, low_tie = INT_MIN;
    constexpr int high = INT_MAX, high_tie = INT_MAX;
    static_assert(matches(min2, min2_ref, low, high, low));
    static_assert(matches(max2, max2_ref, high, low, high));
    static_assert(matches(min2, min2_ref, low, low, low_tie));
    static_assert(matches(max2, max2_ref, high, high, high_tie));
    static_assert(matches(min3, min3_ref, low, high, 0, low));
    static_assert(matches(max3, max3_ref, high, low, 0, high));
    static_assert(matches(min3, min3_ref, low, high, low, low_tie));
    static_assert(matches(max3, max3_ref, high, low, high, high_tie));
    static_assert(matches(min4, min4_ref, low, high, 1, 0, low));
    static_assert(matches(max4, max4_ref, high, low, 0, 1, high));
    static_assert(matches(min4, min4_ref, low, high, low, low_tie, 0));
    static_assert(matches(max4, max4_ref, high, low, high, high_tie, 0));
}
