#include "0955_delete_columns_to_make_sorted_2.hpp"
#include "solution_tests.hpp"
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

using t0955_delete_columns_to_make_sorted_2 = SolutionTests<Solution>;

TEST_P(t0955_delete_columns_to_make_sorted_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minDeletionSize(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0955_delete_columns_to_make_sorted_2,
    t0955_delete_columns_to_make_sorted_2::parameters(kCases.size()),
    t0955_delete_columns_to_make_sorted_2::name);
