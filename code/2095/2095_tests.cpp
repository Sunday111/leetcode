#include "2095.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"  // IWYU pragma: keep
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::deleteMiddle;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,4,7,1,2,6] [1,3,4,1,2,6]
[1,2,3,4]       [1,2,4]
[2,1]           [2]
)");

class t2095 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2095, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2095,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
