#include "2265.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"  // IWYU pragma: keep
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::averageOfSubtree;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,8,5,0,1,null,6]  5
[1]                 1
)");

class t2265 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2265, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2265,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
