#include "0190.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<u32>, u32>(R"cases(
43261596 964176192
)cases");

using t0190 = SolutionTests<Solution>;
TEST_P(t0190, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        { ASSERT_EQ(expected, solution.reverseBits(std::get<0>(inputs))); });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0190,
    t0190::parameters(kCases.size()),
    t0190::name);
