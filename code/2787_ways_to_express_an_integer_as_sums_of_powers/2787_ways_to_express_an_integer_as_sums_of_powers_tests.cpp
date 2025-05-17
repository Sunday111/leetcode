#include "2787_ways_to_express_an_integer_as_sums_of_powers.hpp"
#include "gtest/gtest.h"

TEST(t2787_ways_to_express_an_integer_as_sums_of_powers, test_1)
{
    ASSERT_EQ(Solution{}.numberOfWays(10, 2), 1);
}

TEST(t2787_ways_to_express_an_integer_as_sums_of_powers, test_2)
{
    std::vector<int32_t> precomputed;
    for (int32_t x = 1; x != 6; ++x)
    {
        for (int32_t n = 1; n != 301; ++n)
        {
            auto r = Solution{}.numberOfWays(n, x);
            precomputed.push_back(r);
        }
    }

    for (int32_t x = 1; x != 6; ++x)
    {
        for (int32_t n = 1; n != 301; ++n)
        {
            auto r =
                precomputed[std::bit_cast<uint32_t>((x - 1) * 300 + n - 1)];
            ASSERT_EQ(r, Solution{}.numberOfWays(n, x));
        }
    }

    std::println("{}", precomputed);
    std::println("{}", precomputed.size());
}
