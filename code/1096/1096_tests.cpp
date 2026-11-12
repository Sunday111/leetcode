#include "1096.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::braceExpansionII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"{a,b}{c,{d,e}}"        ["ac","ad","ae","bc","bd","be"]
"{{a,z},a{b,c},{ab,z}}" ["a","ab","ac","z"]
"{a,{c,d}}"             ["a","c","d"]
"abc"                   ["abc"]
"{a,aa}z"               ["aaz","az"]
"{b,a}{d,c}"            ["ac","ad","bc","bd"]
"{a,aa}{a,aa}"          ["aa","aaa","aaaa"]
"{{a,a},{a,b}}{b,b}"    ["ab","bb"]
"{{a,b}{c,d},a{c,d}}"   ["ac","ad","bc","bd"]
"{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}"
["aaaaaaaaaa","aaaaaaaaaaa","aaaaaaaaaaaa","aaaaaaaaaaaaa","aaaaaaaaaaaaaa","aaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaa"]
"{a,a,a}{a,a,a}{a,a,a}{a,a,a}{a,a,a}{a,a,a}{a,a,a,a}{a,a,a,a}" ["aaaaaaaa"]
)");

class t1096 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1096, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1096,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
