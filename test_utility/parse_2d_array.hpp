#pragma once

#include <cassert>
#include <string_view>
#include <vector>

#include "force_inline.hpp"

[[nodiscard]] static constexpr std::tuple<std::vector<int>, size_t> scan1DArray(
    std::string_view s,
    size_t start) noexcept
{
    std::vector<int> result;

    size_t i = start;
    assert(s[i] == '[');
    ++i;

    auto parse_int = [&] INLINE_LAMBDA
    {
        int m = (s[i] == '-') ? -1 : 1;
        i += s[i] == '-';

        assert(std::isdigit(s[i]));

        int v = 0;
        while (std::isdigit(s[i]))
        {
            v *= 10;
            v += s[i++] - '0';
        }

        return v * m;
    };

    if (s[i] == ']') return {{}, start + 2};
    result.push_back(parse_int());

    while (s[i] != ']')
    {
        assert(s[i] == ',');
        ++i;
        result.push_back(parse_int());
    }

    return {result, i + 1};
}

[[nodiscard]] constexpr std::vector<std::vector<int>> parse2DArray(
    std::string_view s) noexcept
{
    assert(s.front() == '[');

    std::vector<std::vector<int>> result;

    size_t i = 1;

    auto arr = [&]()
    {
        auto [a, l] = scan1DArray(s, i);
        result.emplace_back(std::move(a));
        i = l;
    };

    if (s[i] == ']') return result;
    arr();

    while (s[i] != ']')
    {
        assert(s[i] == ',');
        ++i;
        arr();
    }

    return result;
}
