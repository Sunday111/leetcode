#include <random>

#include "2913.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto k_method_to_test = &Solution::sumCounts;
inline static const auto k_cases = parse_test_cases<k_method_to_test>(R"(
[1] 1
[1,1] 3
[1,2,1] 15
[2,2] 3
[7,7,7,7,7] 15
[1,2,3,4] 50
[1,2,1,2,1] 45
[1,1,2,2,1] 39
[1,2,3,1,2,3] 116
[100,1,100] 15
[1,2,3,4,5,1] 185
)");

using t2913 = SolutionTests<Solution>;

TEST_P(t2913, Test)
{
    check(
        k_cases,
        [](auto& solution, auto&... args)
        { return solution.sumCounts(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2913,
    t2913::parameters(k_cases.size()),
    t2913::name);

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
