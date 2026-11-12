#include "2078.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,1,1,6,1,1,1] 3
[1,8,3,8,3] 4
[0,1] 1
)");

class t2078 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2078, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2078,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
