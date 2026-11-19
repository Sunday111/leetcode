#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "gtest/gtest-spi.h"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

namespace solution_tests_test
{
struct MutableMember
{
    int calls = 0;

    int solve(std::vector<int>& values, int bonus)
    {
        int result = values.front() + bonus + calls++;
        values.clear();
        return result;
    }
};

struct ConstMember
{
    int solve(const std::vector<int>& values, int bonus) const noexcept
    {
        return values.front() + bonus;
    }
};

struct StaticMember
{
    static int solve(const std::vector<int>& values, int bonus)
    {
        return values.front() + bonus;
    }
};

struct WrongResult
{
    int operator()(auto&, auto&...) const { return -100; }
};

const auto kCases = parse_test_cases<&MutableMember::solve>(R"(
[3,5] 2 5
[8] -1 7
)");

const std::vector<std::pair<std::string, int>> kRawCases = {
    {"3 5 2", 5},
    {"8 7 -1", 7}};

struct FailingCallback
{
    void operator()(auto&, auto&, auto&) const
    {
        FAIL() << "custom validation failed";
    }
};
}  // namespace solution_tests_test

using SolutionFixture = SolutionTests<
    solution_tests_test::MutableMember,
    solution_tests_test::ConstMember,
    solution_tests_test::StaticMember>;

TEST_P(SolutionFixture, FreshInputsAndInstanceOnEveryInvocation)
{
    const auto before = solution_tests_test::kCases;
    auto invoke = [](auto& solution, auto&... args)
    {
        return solution.solve(args...);
    };
    check(solution_tests_test::kCases, invoke);
    check(solution_tests_test::kCases, invoke);
    EXPECT_EQ(solution_tests_test::kCases, before);
}

TEST_P(SolutionFixture, ReportsWrongResults)
{
    EXPECT_FATAL_FAILURE(
        SolutionFixture::check(
            solution_tests_test::kCases,
            solution_tests_test::WrongResult{}),
        "Expected equality");
}

TEST_P(SolutionFixture, CustomParsingAndValidation)
{
    const auto before = solution_tests_test::kRawCases;
    bool called = false;
    run(solution_tests_test::kRawCases,
        [&](auto& solution, std::string& input, int& expected)
        {
            called = true;
            std::istringstream stream(input);
            std::vector<int> values(2);
            int bonus = 0;
            ASSERT_TRUE(stream >> values[0] >> values[1] >> bonus);
            EXPECT_EQ(solution.solve(values, bonus), expected);
            input.clear();
            expected = 0;
        });
    EXPECT_TRUE(called);
    EXPECT_EQ(solution_tests_test::kRawCases, before);
}

TEST_P(SolutionFixture, ReportsCustomAssertionFailures)
{
    EXPECT_FATAL_FAILURE(
        SolutionFixture::run(
            solution_tests_test::kCases,
            solution_tests_test::FailingCallback{}),
        "custom validation failed");
}

TEST_P(SolutionFixture, SupportsMoveOnlyCallbacks)
{
    run(solution_tests_test::kCases,
        [value = std::make_unique<int>(42)](auto&, auto&, auto&)
        { EXPECT_EQ(*value, 42); });
}

INSTANTIATE_TEST_SUITE_P(
    Utility,
    SolutionFixture,
    SolutionFixture::parameters(solution_tests_test::kCases.size()),
    SolutionFixture::name);

TEST(SolutionTests, GeneratesEverySolutionCasePair)
{
    using Param = SolutionFixture::ParamType;
    const ::testing::internal::ParamGenerator<Param> parameters =
        SolutionFixture::parameters(2);
    const std::vector<Param> actual(parameters.begin(), parameters.end());
    const std::vector<Param> expected =
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}};
    EXPECT_EQ(actual, expected);
}

TEST(SolutionTests, EmptyCasesProduceNoParameters)
{
    const ::testing::internal::ParamGenerator<SolutionFixture::ParamType>
        parameters = SolutionFixture::parameters(0);
    EXPECT_EQ(parameters.begin(), parameters.end());
}

TEST(SolutionTests, NamesIdentifyTheTypeAndCase)
{
    EXPECT_EQ(
        SolutionFixture::name({{0, 1}, 1}),
        "solution_tests_test__MutableMember_C1");
    EXPECT_EQ(
        SolutionFixture::name({{2, 0}, 4}),
        "solution_tests_test__StaticMember_C0");
}

TEST(SolutionTests, SingleSolutionUsesTheSameInterface)
{
    using Single = SolutionTests<solution_tests_test::ConstMember>;
    const ::testing::internal::ParamGenerator<Single::ParamType> parameters =
        Single::parameters(1);
    ASSERT_NE(parameters.begin(), parameters.end());
    EXPECT_EQ(*parameters.begin(), (Single::ParamType{0, 0}));
    EXPECT_EQ(Single::name({{0, 0}, 0}), "solution_tests_test__ConstMember_C0");
    EXPECT_EQ(++parameters.begin(), parameters.end());
}
