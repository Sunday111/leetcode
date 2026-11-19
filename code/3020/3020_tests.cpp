#include "3020.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumLength;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[12,12,144,144,20736,20736,429981696,429981696] 7
[16,16,256,256,65536,65536]                     5
[5,4,1,2,2]                                     3
[1,3,2,4]                                       1
[1,1]                                           1
[4,36,9,16,1,1,4,121,64,4]                      3
)");

using t3020 = SolutionTests<Solution>;

TEST_P(t3020, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumLength(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3020,
    t3020::parameters(kCases.size()),
    t3020::name);
