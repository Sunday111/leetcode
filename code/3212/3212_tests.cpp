#include <string>
#include <tuple>

#include "3212.hpp"
#include "gtest/gtest.h"
#include "namespaces.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSubmatrices;
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

class t3212 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3212, Test)
{
    auto [inputs, expected] = kCases[GetParam()];

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

    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, changed);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3212,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
