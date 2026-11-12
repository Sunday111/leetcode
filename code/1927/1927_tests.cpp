#include "1927.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sumGame;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"5023"                                                                      false
"25??"                                                                      true
"?3295???"                                                                  false
"?6?6?000?3"                                                                true
"?0?3105????1834??7382?997?3?????7?63116?566?701?065?13?3??38?7?488?????9"  false
"??????"                                                                    false
"81??"                                                                      false
"0009??"                                                                    true
)");

class t1927 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1927, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1927,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
