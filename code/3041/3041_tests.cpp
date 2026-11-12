#include "3041.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSelectedElements;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3]      2
[1,4,7,10]  1
[1,2,2]    3
[2,1,5,1,1] 3
[1] 1
[1000000] 1
[1,1,1,1] 2
[1000000,1000000] 2
[1,1,3,3,5,5] 6
[1,2,4] 3
[63,64,65,65,66] 5
)");

class t3041 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3041, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3041,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
