#include "1301.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::pathsWithMaxScore;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["E23","2X2","12S"] [7,1]
["E12","1X1","21S"] [4,2]
["E11","XXX","11S"] [0,0]
)");

class t1301 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1301, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1301,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
