#include "3508_implement_router.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<u32, std::vector<std::vector<u32>>>,
    std::vector<bool>>(R"cases(
3 [[1,4,90],[2,5,90],[1,4,90],[3,5,95],[4,5,105]] [true,true,false,true,true]
)cases");

class t3508_implement_router : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t3508_implement_router, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [capacity, packets] = inputs;
    Router router(capacity);
    ASSERT_EQ(packets.size(), expected.size());
    for (size_t i = 0; i < packets.size(); ++i)
    {
        auto& packet = packets[i];
        ASSERT_EQ(
            router.addPacket(packet[0], packet[1], packet[2]),
            expected[i]);
    }
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3508_implement_router,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
