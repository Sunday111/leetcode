#include "3495_minimum_operations_to_make_array_zero.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

[[nodiscard]] constexpr u8 count_divisions_simple(u32 x) noexcept
{
    u8 r = 0;
    while (x) ++r, x /= 4;
    return r;
}

TEST(t3495_minimum_operations_to_make_array_zero, test_sandbox)
{
    u32 begin = 0;
    u8 prev_r = 0;
    constexpr u32 max_x = 1'000'000;

    auto print_line = [&](u32 x)
    {
        std::println(
            "[{:10}, {:10}): {:3} | [{:32b}, {:32b}) | [{:2}:{:2})",
            begin,
            x,
            prev_r,
            begin,
            x,
            16 - std::countl_zero(begin) / 2,
            16 - std::countl_zero(x) / 2);
    };

    for (u32 x = 1; x != max_x; ++x)
    {
        auto expected = count_divisions_simple(x);
        if (expected != prev_r)
        {
            print_line(x);
            begin = x;
            prev_r = expected;
        }
        u8 actual = count_divisions(x);
        ASSERT_EQ(+expected, +actual) << "x = " << x;
    }

    print_line(max_x);
}

TEST(t3495_minimum_operations_to_make_array_zero, test_1)
{
    std::vector<std::vector<int>> queries = parse2DArray("[[1,2],[2,4]]");
    ASSERT_EQ(Solution{}.minOperations(queries), 3);
}
