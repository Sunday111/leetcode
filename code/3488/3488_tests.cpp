#include "3488.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::solveQueries;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,1,4,1,3,2]
[0,3,5]
[2,-1,3]

[1,2,3,4]
[0,1,2,3]
[-1,-1,-1,-1]


)");

class t3488 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3488, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3488,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
