#include <unordered_set>

#include "0022_test_cases.hpp"
#include "gtest/gtest.h"

static_assert(Solution::data[0].empty());
static_assert(Solution::data[8].size() == 16 * kCatalan64[8]);
static_assert(Solution::data[1][0] == '(' && Solution::data[1][1] == ')');

class t0022 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0022, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0022,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });

TEST(ParenthesisStorageTest, AllLevels)
{
    Solution solution;
    for (u8 n = 1; n <= Solution::kMaxN; ++n)
    {
        SCOPED_TRACE(n);
        auto strings = solution.generateParenthesis(n);
        ASSERT_EQ(strings.size(), kCatalan64[n]);
        std::unordered_set<std::string> unique;
        for (const auto& value : strings)
        {
            ASSERT_EQ(value.size(), 2u * n);
            EXPECT_TRUE(unique.insert(value).second);
            int balance = 0;
            for (char c : value)
            {
                ASSERT_TRUE(c == '(' || c == ')');
                balance += c == '(' ? 1 : -1;
                ASSERT_GE(balance, 0);
            }
            EXPECT_EQ(balance, 0);
        }
    }
}
