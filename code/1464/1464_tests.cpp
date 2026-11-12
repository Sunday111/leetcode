#include "1464.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxProduct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,2]   12
[1,5,4,5]   16
[3,7]       12
)");

class t1464 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1464, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1464,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
