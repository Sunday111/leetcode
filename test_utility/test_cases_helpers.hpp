#pragma once

#include <string_view>
#include <type_traits>

#include "convert_expected_type.hpp"
#include "scan.hpp"
#include "template/signature.hpp"
#include "template/tuple_head.hpp"
#include "template/tuple_map.hpp"

template <auto method>
struct TestMethodInfo
{
    using S = ::Signature<std::decay_t<decltype(method)>>;
    using Args = typename S::Args;
    using ReturnType = typename S::Ret;
    using Inputs = tuple_map<Args, convert_expected_type_t>;
    using Result = std::tuple<convert_expected_type_t<ReturnType>>;
    using TestCaseTypes = decltype(std::tuple_cat(Inputs{}, Result{}));
};

template <auto method, typename Options = DefaultScannerOptions>
[[nodiscard]] auto parse_test_cases(
    std::string_view s,
    const Options& opts = Options{})
{
    using Types = typename TestMethodInfo<method>::TestCaseTypes;
    constexpr auto n = std::tuple_size_v<Types>;
    static_assert(n > 1, "Expect at least one input and one output");
    using Inputs = tuple_head<Types, n - 1>;
    using Result = std::tuple_element_t<n - 1, Types>;
    std::vector<std::tuple<Inputs, Result>> r;

    size_t i = skip_whitespaces(opts, s, 0);
    while (i < s.size())
    {
        i = do_scan(opts, s, i, r.emplace_back());
        i = skip_whitespaces(opts, s, i);
    }

    return r;
}
