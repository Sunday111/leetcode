#include <unordered_set>

#include "0022.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::generateParenthesis;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1       ["()"]
2       ["()()","(())"]
3       ["()()()","()(())","(())()","(()())","((()))"]
)cases");

static_assert(Solution::data[0].empty());
static_assert(Solution::data[8].size() == 16 * kCatalan64[8]);
static_assert(Solution::data[1][0] == '(' && Solution::data[1][1] == ')');

using t0022 = SolutionTests<Solution>;

TEST_P(t0022, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.generateParenthesis(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0022,
    t0022::parameters(kCases.size()),
    t0022::name);

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
