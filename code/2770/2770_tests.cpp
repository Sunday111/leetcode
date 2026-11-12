#include "2770.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,6,4,1,2] 2 3
[1,3,6,4,1,2] 3 5
[1,3,6,4,1,2] 0 -1
)");

class t2770 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2770, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2770,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
