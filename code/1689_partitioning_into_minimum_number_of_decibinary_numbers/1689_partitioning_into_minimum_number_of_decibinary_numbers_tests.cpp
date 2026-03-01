#include "1689_partitioning_into_minimum_number_of_decibinary_numberstest_cases.hpp"
#include "gtest/gtest.h"
#include "scan.hpp"
#include "template/signature.hpp"

using MethodSignature = Signature<std::decay_t<decltype(kMethodToTest)>>;
using TestCaseTypes = decltype(std::tuple_cat(
    MethodSignature::Args{},
    std::tuple<MethodSignature::Ret>{}));

inline static const auto kCases = parse_test_cases<TestCaseTypes>(kTestCases);

class t1689_partitioning_into_minimum_number_of_decibinary_numbers
    : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(
    t1689_partitioning_into_minimum_number_of_decibinary_numbers,
    MinOperations)
{
    const auto& [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto actual = std::apply(
        kMethodToTest,
        std::tuple_cat(std::make_tuple(&instance), inputs));
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1689_partitioning_into_minimum_number_of_decibinary_numbers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
