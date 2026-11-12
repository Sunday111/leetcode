#include "2130.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"  // IWYU pragma: keep
#include "leet_code_list.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::pairSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[5,4,2,1] 6
[4,2,2,3] 7
[1,100000] 100001
)");

class t2130 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2130, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2130,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
