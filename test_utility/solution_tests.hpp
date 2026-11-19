#pragma once

#include <cctype>
#include <cstddef>
#include <functional>
#include <string>
#include <tuple>

#include "gtest/gtest.h"

template <typename... Solutions>
class SolutionTests
    : public ::testing::TestWithParam<std::tuple<size_t, size_t>>
{
    using Base = ::testing::TestWithParam<std::tuple<size_t, size_t>>;
    static_assert(sizeof...(Solutions) > 0);

    template <typename Solution, typename Cases, typename Callback>
    static void run_case(const Cases& cases, size_t index, Callback& callback)
    {
        auto [inputs, expected] = cases.at(index);
        Solution solution{};
        std::invoke(callback, solution, inputs, expected);
    }

    template <typename Solution>
    static std::string solution_name()
    {
        // Use the same demangled type names as Google Test's typed tests.
        auto result = ::testing::internal::GetTypeName<Solution>();
        for (char& c : result)
        {
            if (!std::isalnum(static_cast<unsigned char>(c))) c = '_';
        }
        return result;
    }

public:
    using typename Base::ParamType;

    static auto parameters(size_t count)
    {
        return ::testing::Combine(
            ::testing::Range(size_t{0}, sizeof...(Solutions)),
            ::testing::Range(size_t{0}, count));
    }

    static std::string name(const ::testing::TestParamInfo<ParamType>& info)
    {
        static const std::string names[] = {solution_name<Solutions>()...};
        const auto [solution, index] = info.param;
        return names[solution] + "_C" + std::to_string(index);
    }

    template <typename Cases, typename Callback>
    static void run(const Cases& cases, Callback callback)
    {
        const auto [solution, index] = Base::GetParam();
        ASSERT_LT(solution, sizeof...(Solutions));
        ASSERT_LT(index, cases.size());
        using Run = void (*)(const Cases&, size_t, Callback&);
        constexpr Run runners[] = {&run_case<Solutions, Cases, Callback>...};
        runners[solution](cases, index, callback);
    }

    template <typename Cases, typename Invoke>
    static void check(const Cases& cases, Invoke invoke)
    {
        run(cases,
            [&](auto& solution, auto& inputs, const auto& expected)
            {
                auto actual = std::apply(
                    [&](auto&... args)
                    { return std::invoke(invoke, solution, args...); },
                    inputs);
                ASSERT_EQ(expected, actual);
            });
    }
};
