#include "2058.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"  // IWYU pragma: keep
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::nodesBetweenCriticalPoints;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,1]                   [-1,-1]
[5,3,1,2,5,1,2]         [1,3]
[1,3,2,2,3,2,2,2,7]     [3,3]
)");

class t2058 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2058, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2058,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
