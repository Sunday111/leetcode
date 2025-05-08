#include <algorithm>

#include "0039_combination_sum.hpp"
#include "0039_combination_sum_2.hpp"
#include "0039_combination_sum_3.hpp"
#include "gtest/gtest.h"

inline static constexpr auto sorted = [](auto& arrays) -> decltype(auto)
{
    std::ranges::for_each(arrays, std::ranges::sort);
    std::ranges::sort(arrays);
    return arrays;
};

TEST(t0039_combination_sum, test_1)
{
    std::vector<int32_t> candidates{2, 3, 6, 7};
    int32_t target = 7;
    std::vector<std::vector<int32_t>> expected{{2, 2, 3}, {7}};
    auto actual = Solution{}.combinationSum(candidates, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0039_combination_sum, test_2)
{
    std::vector<int32_t> candidates{38};
    int32_t target = 35;
    std::vector<std::vector<int32_t>> expected{};
    auto actual = Solution{}.combinationSum(candidates, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0039_combination_sum, test_solutions)
{
    std::vector<int32_t> candidates{1, 2, 3};
    for (int32_t target = 1; target != 41; ++target)
    {
        auto expected = Solution2{}.combinationSum(candidates, target);
        auto actual = Solution3{}.combinationSum(candidates, target);
        ASSERT_EQ(sorted(expected), sorted(actual)) << "target: " << target;
    }
}
