#include <algorithm>

#include "1948_delete_duplicate_folders_in_system.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<std::string>>>,
    std::vector<std::vector<std::string>>>(R"cases(
[["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]] [["d"],["d","a"]]
[["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]] [["a"],["a","b"],["c"],["c","b"]]
)cases");

using t1948_delete_duplicate_folders_in_system = SolutionTests<Solution>;
TEST_P(t1948_delete_duplicate_folders_in_system, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = solution.deleteDuplicateFolder(std::get<0>(inputs));
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1948_delete_duplicate_folders_in_system,
    t1948_delete_duplicate_folders_in_system::parameters(kCases.size()),
    t1948_delete_duplicate_folders_in_system::name);
