#include "1886.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findRotation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1],[1,0]]
[[1,0],[0,1]]
true

[[0,1],[1,1]]
[[1,0],[0,1]]
false

[[0,0,0],[0,1,0],[1,1,1]]
[[1,1,1],[0,1,0],[0,0,0]]
true

[[1]]
[[0]]
false
)");

class t1886 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1886, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1886,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
