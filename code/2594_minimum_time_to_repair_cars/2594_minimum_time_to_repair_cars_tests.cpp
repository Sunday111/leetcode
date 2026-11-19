#include "2594_minimum_time_to_repair_cars.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::repairCars;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4] 10 16
)cases");

class t2594_minimum_time_to_repair_cars
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2594_minimum_time_to_repair_cars, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.repairCars(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2594_minimum_time_to_repair_cars,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
