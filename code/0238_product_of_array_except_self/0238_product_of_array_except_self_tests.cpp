#include "0238_product_of_array_except_self.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::productExceptSelf;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4] [24,12,8,6]
)cases");

using t0238_product_of_array_except_self = SolutionTests<Solution>;

TEST_P(t0238_product_of_array_except_self, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.productExceptSelf(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0238_product_of_array_except_self,
    t0238_product_of_array_except_self::parameters(kCases.size()),
    t0238_product_of_array_except_self::name);
