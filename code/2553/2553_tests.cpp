#include "2553.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::separateDigits;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[13,25,83,77] [1,3,2,5,8,3,7,7]
[7,1,3,9]     [7,1,3,9]
)");

class t2553 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2553, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2553,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
