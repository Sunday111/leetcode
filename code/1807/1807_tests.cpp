#include "1807.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::evaluate;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"(name)is(age)yearsold"
[["name","bob"],["age","two"]]
"bobistwoyearsold"

"hi(name)"
[["a","b"]]
"hi?"
)cases");

class t1807 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1807, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1807,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
