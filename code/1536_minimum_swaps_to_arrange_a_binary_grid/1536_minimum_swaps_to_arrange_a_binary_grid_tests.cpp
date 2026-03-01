#include <type_traits>

#include "1536_minimum_swaps_to_arrange_a_binary_gridtest_cases.hpp"
#include "gtest/gtest.h"
#include "scan.hpp"
#include "template/signature.hpp"
#include "template/tuple_remove_ref.hpp"

using MethodSignature = Signature<std::decay_t<decltype(kMethodToTest)>>;
using TestCaseTypes = decltype(std::tuple_cat(
    tuple_remove_ref<MethodSignature::Args>{},
    std::tuple<MethodSignature::Ret>{}));

inline static const auto kCases = parse_test_cases<TestCaseTypes>(kTestCases);

class t1536_minimum_swaps_to_arrange_a_binary_grid
    : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1536_minimum_swaps_to_arrange_a_binary_grid, MinOperations)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1536_minimum_swaps_to_arrange_a_binary_grid,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
