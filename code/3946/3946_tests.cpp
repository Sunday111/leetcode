#include "3946.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumSaleItems;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[6,2],[2,6],[3,4]]
9
4

[[2,4],[3,2],[4,1],[6,4],[12,4]]
8
10

[[6,1],[12,3]]
2
3

[[6,1],[6,1]]
2
4

[[1451,2],[1451,2],[1500,2]]
2
2

[[750,1],[1500,2]]
1
2

[[3,5],[6,3],[4,3],[1,7],[6,5]]
12
8

[[6,2],[6,3],[6,10]]
9
8

[[2,2],[2,7],[1498,100],[1499,100]]
4
4
)");

using t3946 = SolutionTests<Solution>;

TEST_P(t3946, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumSaleItems(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3946,
    t3946::parameters(kCases.size()),
    t3946::name);
