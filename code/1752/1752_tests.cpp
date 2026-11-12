#include "1752.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::check;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,1,2] true
[2,1,3,4] false
[1,2,3] true
)");

class t1752 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1752, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1752,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
