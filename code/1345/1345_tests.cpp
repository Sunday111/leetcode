#include "1345.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[100,-23,-23,404,100,23,23,23,3,404]    3
[7]                                     0
[7,6,9,6,9,6,9,7]                       1
)");

class t1345 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1345, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1345,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
