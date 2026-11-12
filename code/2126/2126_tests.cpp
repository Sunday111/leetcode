#include "2126.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::asteroidsDestroyed;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10
[3,9,19,5,21]
true
5
[4,9,23,4]
false
)");

class t2126 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2126, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2126,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
