#pragma once

#include <concepts>
#include <format>
#include <string_view>
#include <type_traits>
#include <utility>

#include "concept/is_specialization.hpp"
#include "force_inline.hpp"
#include "leet_code_binary_tree.hpp"

struct DefaultScannerOptions
{
    [[nodiscard]] FORCE_INLINE static constexpr bool is_ignored_char(
        [[maybe_unused]] char c) noexcept
    {
        return std::isspace(c);
    }

    static constexpr std::string_view tuple_delimeter = "";
};

template <typename T, typename R, typename... Args>
concept invocable_r =
    std::invocable<T, Args...> && requires(T&& f, Args&&... args) {
        {
            std::invoke(f, std::forward<Args>(args)...)
        } -> std::convertible_to<R>;
    };

constexpr void scan_expect(std::string_view s, size_t i, char c)
{
    [[unlikely]] if (s[i] != c)
    {
        throw std::runtime_error(
            std::format("Expected {} at {} but got {}", c, i, s[i]));
    }
}

template <typename Options>
[[nodiscard]] FORCE_INLINE constexpr size_t
skip_whitespaces(const Options& opts, std::string_view s, size_t i) noexcept
{
    while (opts.is_ignored_char(s[i])) ++i;
    return i;
}

template <invocable_r<bool, char> Pred>
constexpr void scan_expect(
    std::string_view s,
    size_t i,
    Pred&& pred,
    std::string_view pred_name)
{
    [[unlikely]] if (!std::forward<Pred>(pred)(s[i]))
    {
        throw std::runtime_error(
            std::format("Expected {} at {} but got {}", pred_name, i, s[i]));
    }
}

template <typename Options, std::same_as<std::string_view> T>
[[nodiscard]] constexpr size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& result)
{
    size_t i = skip_whitespaces(opts, s, start);
    scan_expect(s, i, '\"');
    ++i;
    auto begin = i;
    while (s[i] != '\"') ++i;
    result = s.substr(begin, i - begin);
    return i + 1;
}

template <typename Options, std::same_as<bool> T>
[[nodiscard]] constexpr size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& r)
{
    size_t i = skip_whitespaces(opts, s, start);
    constexpr std::string_view kTrue = "true", kFalse = "false";
    auto sub = s.substr(i);
    if (sub.starts_with(kTrue))
    {
        r = true;
        return i + kTrue.size();
    }

    if (sub.starts_with(kFalse))
    {
        r = false;
        return i + kFalse.size();
    }

    throw std::runtime_error(std::format("Expected true or false at {}", i));
}

template <typename Options, std::same_as<std::string> T>
[[nodiscard]] constexpr size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& result)
{
    std::string_view x;
    size_t i = do_scan(opts, s, start, x);
    result = x;
    return i;
}

template <typename Options, is_specialization<std::optional> T>
[[nodiscard]] constexpr size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& result)
{
    size_t i = skip_whitespaces(opts, s, start);
    if (s.substr(i).starts_with("null"))
    {
        i += 4;
        result = std::nullopt;
    }
    else
    {
        using V = T::value_type;
        result = V{};
        i = do_scan(opts, s, i, *result);
    }

    return i;
}

template <typename Options, is_specialization<LeetCodeBinaryTree> T>
[[nodiscard]] constexpr size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& r)
{
    using NodeType = T::NodeType;
    using ValueType = decltype(NodeType{}.val);
    using Elem = std::optional<ValueType>;
    std::vector<Elem> vals;
    size_t i = do_scan(opts, s, start, vals);
    r = T::FromArray(vals);
    return i;
}

template <typename Options, std::integral T>
    requires(!std::same_as<T, bool>)  // Break ambiguity with boolean parser
[[nodiscard]] constexpr size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& result)
{
    size_t i = skip_whitespaces(opts, s, start);

    T m{1};

    if constexpr (std::is_signed_v<T>)
    {
        if (s[i] == '-')
        {
            m = -1;
            ++i;
            i = skip_whitespaces(opts, s, i);
        }
    }

    auto is_digit = [](char x)
    {
        return std::isdigit(x);
    };

    scan_expect(s, i, is_digit, "digit");

    result = T{0};
    while (std::isdigit(s[i]))
    {
        result *= 10;
        result += static_cast<T>(s[i++] - '0');
    }

    if constexpr (std::is_signed_v<T>)
    {
        result *= m;
    }

    return i;
}

template <typename Options, is_specialization<std::vector> T>
[[nodiscard]] size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& result)
{
    size_t i = skip_whitespaces(opts, s, start);
    scan_expect(s, i, '[');
    ++i;
    i = skip_whitespaces(opts, s, i);

    if (s[i] == ']') return start + 2;

    auto parse_element = [&]() INLINE_LAMBDA
    {
        i = skip_whitespaces(opts, s, i);
        i = do_scan(opts, s, i, result.emplace_back());
        i = skip_whitespaces(opts, s, i);
    };
    parse_element();

    while (s[i] != ']')
    {
        scan_expect(s, i, ',');
        ++i;
        parse_element();
    }

    return i + 1;
}

template <typename Options, is_specialization<std::tuple> T>
[[nodiscard]] size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& result)
{
    size_t i = skip_whitespaces(opts, s, start);

    constexpr auto n = std::tuple_size_v<T>;

    auto parse_element =
        [&]<size_t element_index>(std::integral_constant<size_t, element_index>)
            INLINE_LAMBDA
    {
        i = skip_whitespaces(opts, s, i);
        if constexpr (element_index > 0)
        {
            for (char dlm : opts.tuple_delimeter)
            {
                scan_expect(s, i, dlm);
                ++i;
            }
            i = skip_whitespaces(opts, s, i);
        }
        i = do_scan(opts, s, i, std::get<element_index>(result));
    };

    [&]<size_t... element_index>(std::index_sequence<element_index...>)
    {
        (parse_element(std::integral_constant<size_t, element_index>{}), ...);
    }(std::make_index_sequence<n>());

    return i;
}

template <size_t k, is_specialization<std::tuple> T>
[[nodiscard]] constexpr auto tuple_split(T&& x) noexcept
{
    constexpr auto n = std::tuple_size_v<T>;
    static_assert(k <= n);

    return std::make_tuple(
        [&]<size_t... indices>(std::index_sequence<indices...>)
        {
            return std::make_tuple(std::get<indices>(std::forward<T>(x))...);
        }(std::make_index_sequence<k>()),
        [&]<size_t... indices>(std::index_sequence<indices...>)
        {
            return std::make_tuple(
                std::get<k + indices>(std::forward<T>(x))...);
        }(std::make_index_sequence<n - k>()));
}

template <is_specialization<std::tuple> T, size_t k>
using tuple_head =
    std::remove_reference_t<decltype(std::get<0>(tuple_split<k>(T{})))>;

template <
    is_specialization<std::tuple> Types,
    typename Options = DefaultScannerOptions>
[[nodiscard]] auto parse_test_cases(
    std::string_view s,
    const Options& opts = Options{})
{
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
