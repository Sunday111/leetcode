#include "0190_reverse_bits.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<u32>, u32>(R"cases(
43261596 964176192
)cases");

using t0190_reverse_bits = SolutionTests<Solution>;
TEST_P(t0190_reverse_bits, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        { ASSERT_EQ(expected, solution.reverseBits(std::get<0>(inputs))); });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0190_reverse_bits,
    t0190_reverse_bits::parameters(kCases.size()),
    t0190_reverse_bits::name);
