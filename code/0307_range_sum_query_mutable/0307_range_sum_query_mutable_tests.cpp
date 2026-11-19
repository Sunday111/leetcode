#include <vector>

#include "0307_range_sum_query_mutable.hpp"
#include "cast.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<
        std::vector<int>,
        std::vector<std::string>,
        std::vector<std::vector<int>>>,
    std::vector<std::optional<int>>>(R"cases(
[1,3,5] ["sumRange","update","sumRange","sumRange"] [[0,2],[1,2],[0,2],[1,1]] [9,null,8,2]
[-5] ["sumRange","update","sumRange","update","sumRange"] [[0,0],[0,0],[0,0],[0,8],[0,0]] [-5,null,0,null,8]
)cases");

class t0307_range_sum_query_mutable : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0307_range_sum_query_mutable, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [source, operations, args] = inputs;
    const auto original = source;
    NumArray array(source);
    ASSERT_EQ(operations.size(), args.size());
    ASSERT_EQ(operations.size(), expected.size());
    for (size_t i = 0; i < operations.size(); ++i)
    {
        SCOPED_TRACE(i);
        const auto index = cast<u16>(args[i][0] & 0xFFFF);
        if (operations[i] == "update")
        {
            array.update(index, args[i][1]);
            ASSERT_FALSE(expected[i].has_value());
        }
        else
        {
            ASSERT_EQ(operations[i], "sumRange");
            ASSERT_EQ(
                expected[i],
                array.sumRange(index, cast<u16>(args[i][1] & 0xFFFF)));
        }
    }
    ASSERT_EQ(source, original);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0307_range_sum_query_mutable,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
