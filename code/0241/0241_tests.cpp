#include "0241.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

inline static constexpr auto kMethodToTest = &Solution::diffWaysToCompute;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"2*3-4*5"   [-34,-14,-10,-10,10]
"2-1-1"     [0,2]
)");

using t0241 = SolutionTests<Solution>;

TEST_P(t0241, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto f = [&](auto&... args)
            {
                return solution.diffWaysToCompute(args...);
            };
            auto actual = std::apply(f, inputs);
            std::ranges::sort(actual);
            std::ranges::sort(expected);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0241,
    t0241::parameters(kCases.size()),
    t0241::name);
