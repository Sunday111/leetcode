#include "0955_delete_columns_to_make_sorted_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::string>>,
    unsigned char>(R"cases(
["ca","bb","ac"] 1

["vdy","vei","zvc","zld"] 2

["bbjwefkpb","axmksfchw"] 1

["koccmoezl","hbccayhbd"] 3

["jsebodtwc","cnneoytml","eeneuyzlu","ewpnmtivg"] 2

["abx","agz","bgc","bfc"] 1

["aa","ac","ab"] 1
)cases");

class t0955_delete_columns_to_make_sorted_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0955_delete_columns_to_make_sorted_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minDeletionSize(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0955_delete_columns_to_make_sorted_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
