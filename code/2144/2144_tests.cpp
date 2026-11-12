#include "2144.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3] 5
[6,5,7,9,2,2] 23
[5,5] 10
)");

class t2144 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2144, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2144,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
