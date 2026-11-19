#include "1356_sort_integers_by_the_number_of_1_bits.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sortByBits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,2,3,4,5,6,7,8] [0,1,2,4,8,3,5,6,7]

[1024,512,256,128,64,32,16,8,4,2,1] [1,2,4,8,16,32,64,128,256,512,1024]
)cases");

class t1356_sort_integers_by_the_number_of_1_bits
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1356_sort_integers_by_the_number_of_1_bits, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.sortByBits(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1356_sort_integers_by_the_number_of_1_bits,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
