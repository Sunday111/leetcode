#include "0401.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::readBinaryWatch;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
)cases");

using t0401 = SolutionTests<Solution>;

TEST_P(t0401, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.readBinaryWatch(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0401,
    t0401::parameters(kCases.size()),
    t0401::name);
