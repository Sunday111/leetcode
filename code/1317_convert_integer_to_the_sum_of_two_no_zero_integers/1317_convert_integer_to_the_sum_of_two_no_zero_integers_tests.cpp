#include "1317_convert_integer_to_the_sum_of_two_no_zero_integers.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<int>, int>(R"cases(
2 2
11 11
10000 10000
)cases");

using t1317_convert_integer_to_the_sum_of_two_no_zero_integers =
    SolutionTests<Solution>;
TEST_P(t1317_convert_integer_to_the_sum_of_two_no_zero_integers, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = solution.getNoZeroIntegers(std::get<0>(inputs));
            ASSERT_EQ(actual.size(), 2);
            ASSERT_EQ(actual[0] + actual[1], expected);
            for (int value : actual)
            {
                ASSERT_GT(value, 0);
                ASSERT_EQ(std::to_string(value).find('0'), std::string::npos);
            }
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1317_convert_integer_to_the_sum_of_two_no_zero_integers,
    t1317_convert_integer_to_the_sum_of_two_no_zero_integers::parameters(
        kCases.size()),
    t1317_convert_integer_to_the_sum_of_two_no_zero_integers::name);
