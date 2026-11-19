#include <algorithm>

#include "0301.hpp"
#include "0301_bitset.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution_bitmask::removeInvalidParentheses;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()())()" ["(())()","()()()"]
"(a)())()" ["(a())()","(a)()()"]
")(" [""]
"(a()" ["a()","(a)"]
"(a(b)" ["a(b)","(ab)"]
")a)b(c(" ["abc"]
"abc" ["abc"]
"abcdefghijklmnoqrstuvwxyz" ["abcdefghijklmnoqrstuvwxyz"]
"((((((((((abcde))))))))))" ["((((((((((abcde))))))))))"]
"))((" [""]
")()(" ["()"]
"((((((((((((((((((aaaaa))" ["((aaaaa))"]
"(((k()((" ["(k)","k()"]
"()(()m)" ["()(()m)"]
"())(((()m)(" ["()(()m)"]
)cases");

using t0301 = SolutionTests<Solution_bitmask, Solution_bitset>;

TEST_P(t0301, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual =
                solution.removeInvalidParentheses(std::get<0>(inputs));
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

TEST(t0301Reuse, MultipleCalls)
{
    Solution_bitmask instance{};
    for (auto [inputs, expected] : kCases)
    {
        auto actual =
            std::apply(std::bind_front(kMethodToTest, &instance), inputs);
        std::ranges::sort(expected);
        std::ranges::sort(actual);
        ASSERT_EQ(expected, actual);
    }
}

TEST(t0301Input, Unchanged)
{
    std::string input = ")a)b(c(";
    auto actual = Solution_bitmask{}.removeInvalidParentheses(input);
    EXPECT_EQ(input, ")a)b(c(");
    EXPECT_EQ(actual, (std::vector<std::string>{"abc"}));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0301,
    t0301::parameters(kCases.size()),
    t0301::name);
