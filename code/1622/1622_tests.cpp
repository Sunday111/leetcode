#include "1622.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::string>, std::vector<int>>,
    std::vector<std::optional<int>>>(R"cases(
["append","getIndex","addAll","getIndex","append","getIndex","getIndex","multAll","getIndex","getIndex","addAll","append","multAll","getIndex","getIndex","getIndex"]
[2,0,3,0,7,0,1,2,0,1,3,10,2,0,1,2]
[null,2,null,5,null,5,7,null,10,14,null,null,null,26,34,20]
)cases");

class t1622 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t1622, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [operations, args] = inputs;
    Fancy fancy;
    ASSERT_EQ(operations.size(), args.size());
    ASSERT_EQ(operations.size(), expected.size());
    for (size_t i = 0; i < operations.size(); ++i)
    {
        SCOPED_TRACE(i);
        if (operations[i] == "getIndex")
            ASSERT_EQ(fancy.getIndex(args[i]), expected[i]);
        else
        {
            ASSERT_FALSE(expected[i].has_value());
            if (operations[i] == "append")
                fancy.append(args[i]);
            else if (operations[i] == "addAll")
                fancy.addAll(args[i]);
            else
            {
                ASSERT_EQ(operations[i], "multAll");
                fancy.multAll(args[i]);
            }
        }
    }
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1622,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
