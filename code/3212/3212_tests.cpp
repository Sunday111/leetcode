#include <tuple>

#include "3212_test_cases.hpp"
#include "gtest/gtest.h"
#include "namespaces.hpp"

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
