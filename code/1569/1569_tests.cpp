#include "1569_test_cases.hpp"
#include "gtest/gtest.h"

class t1569 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1569, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1569,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });

TEST(t1569Boundary, MaximumSkewedTrees)
{
    Solution instance{};
    std::vector<int> nums(1000);
    int value = 1;
    for (auto& num : nums) num = value++;
    EXPECT_EQ(instance.numOfWays(nums), 0u);
    value = 1000;
    for (auto& num : nums) num = value--;
    EXPECT_EQ(instance.numOfWays(nums), 0u);
}

TEST(t1569Boundary, MaximumBalancedTreeThenSingleton)
{
    std::vector<int> nums;
    auto append = [&](this auto&& self, int first, int last) -> void
    {
        if (first > last) return;
        int mid = (first + last) / 2;
        nums.push_back(mid);
        self(first, mid - 1);
        self(mid + 1, last);
    };
    append(1, 1000);
    Solution instance{};
    EXPECT_EQ(instance.numOfWays(nums), 718156653u);
    nums = {1};
    EXPECT_EQ(instance.numOfWays(nums), 0u);
}
