#include "2452.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::twoEditWords;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["word","note","ants","wood"]
["wood","joke","moat"]
["word","note","wood"]

["yes"]
["not"]
[]
)");

class t2452 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2452, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2452,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
