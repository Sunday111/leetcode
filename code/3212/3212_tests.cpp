#include <string>
#include <tuple>

#include "3212.hpp"
#include "namespaces.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<std::string>>>,
    u32>(R"(
[["X","Y","."],["Y",".","."]]
3

[["X","X"],["X","Y"]]
0

[[".","."],[".","."]]
0


)");

using t3212 = SolutionTests<Solution>;

TEST_P(t3212, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto changed = std::make_tuple(
                std::get<0>(inputs) |
                stdv::transform(
                    [](const std::vector<std::string>& row)
                    {
                        std::vector<char> r;
                        r.reserve(row.size());
                        for (auto& x : row)
                        {
                            r.push_back(x[0]);
                        }
                        return r;
                    }) |
                stdr::to<std::vector>());

            auto f = [&](auto&... args)
            {
                return solution.numberOfSubmatrices(args...);
            };
            auto actual = std::apply(f, changed);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3212,
    t3212::parameters(kCases.size()),
    t3212::name);
