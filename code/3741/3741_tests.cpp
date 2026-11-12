#include "3741.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,1,1,3]
6

[1,1,2,3,2,1,2]
8

[1]
-1


)");

class t3741 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3741, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3741,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
