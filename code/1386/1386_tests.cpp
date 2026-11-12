#include "1386.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxNumberOfFamilies;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3 [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]    4
2 [[2,1],[1,8],[2,6]]                       2
4 [[4,3],[1,4],[4,6],[1,7]]                 4
)");

class t1386 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1386, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1386,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
