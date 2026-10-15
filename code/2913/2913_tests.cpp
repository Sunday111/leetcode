#include <random>

#include "2913_test_cases.hpp"
#include "gtest/gtest.h"

class t2913 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2913, Test)
{
    auto [inputs, expected] = k_cases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(k_method_to_test, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2913,
    ::testing::Range(size_t{0}, k_cases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });

TEST(Solution2913, MaximumInputs)
{
    std::vector<int> nums(100, 100);
    Solution solution;
    EXPECT_EQ(solution.sumCounts(nums), 5050u);
    for (u32 i = 0; i < nums.size(); ++i)
    {
        nums[i] = static_cast<int>(i + 1);
    }
    EXPECT_EQ(solution.sumCounts(nums), 8'670'850u);
}

TEST(Solution2913, MatchesBruteForce)
{
    std::mt19937 rng(2913);
    Solution solution;
    for (u32 n = 1; n <= 100; ++n)
    {
        for (u32 trial = 0; trial < 8; ++trial)
        {
            std::vector<int> nums(n);
            for (auto& value : nums)
            {
                value = static_cast<int>(rng() % 100 + 1);
            }
            u32 expected = 0;
            for (u32 l = 0; l < n; ++l)
            {
                bool seen[101]{};
                u32 distinct = 0;
                for (u32 r = l; r < n; ++r)
                {
                    u32 value = static_cast<u32>(nums[r]);
                    if (!seen[value])
                    {
                        seen[value] = true;
                        ++distinct;
                    }
                    expected += distinct * distinct;
                }
            }
            ASSERT_EQ(solution.sumCounts(nums), expected)
                << "n=" << n << ", trial=" << trial;
        }
    }
}

TEST(BIT2913, UpdatesAndStorageReset)
{
    BIT<3> bit(3);
    bit.update(0, 0);
    bit.update(0, 1);
    bit.update(1, 2);
    EXPECT_EQ(bit.query(0, 2), 5u);
    EXPECT_EQ(bit.suffix_sum(1), 3u);
    EXPECT_EQ(bit.suffix_sum(3), 0u);
    BIT<3> reset_bit(3);
    EXPECT_EQ(reset_bit.query(0, 2), 0u);
    EXPECT_EQ(reset_bit.suffix_sum(0), 0u);
}
