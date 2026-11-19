#include <algorithm>
#include <unordered_set>

#include "0022.hpp"
#include "0022_stack.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution_precomputed::generateParenthesis;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 ["()"]
2 ["()()","(())"]
3 ["()()()","()(())","(())()","(()())","((()))"]
)cases");

static_assert(Solution_precomputed::data[0].empty());
static_assert(Solution_precomputed::data[8].size() == 16 * kCatalan64[8]);
static_assert(
    Solution_precomputed::data[1][0] == '(' &&
    Solution_precomputed::data[1][1] == ')');

using t0022 = SolutionTests<Solution_precomputed, Solution_stack>;

TEST_P(t0022, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = solution.generateParenthesis(std::get<0>(inputs));
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0022,
    t0022::parameters(kCases.size()),
    t0022::name);

TEST(ParenthesisStorageTest, AllLevels)
{
    Solution_precomputed solution;
    for (u8 n = 1; n <= Solution_precomputed::kMaxN; ++n)
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
