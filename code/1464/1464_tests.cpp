#include "1464.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxProduct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,2]   12
[1,5,4,5]   16
[3,7]       12
)");

using t1464 = SolutionTests<Solution>;

TEST_P(t1464, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxProduct(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1464,
    t1464::parameters(kCases.size()),
    t1464::name);
