#include "1700_number_of_students_unable_to_eat.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countStudents;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1] [0,1,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0] 3
)cases");

class t1700_number_of_students_unable_to_eat
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1700_number_of_students_unable_to_eat, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countStudents(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1700_number_of_students_unable_to_eat,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
