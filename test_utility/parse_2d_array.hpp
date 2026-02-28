#pragma once

#include <cassert>
#include <string_view>
#include <vector>

#include "force_inline.hpp"
#include "scan.hpp"

template <typename T, typename Options = DefaultScannerOptions>
[[nodiscard]] FORCE_INLINE constexpr T parse_from_string(
    std::string_view s,
    const Options& opts = Options{})
{
    T r;
    auto i = do_scan(opts, s, 0, r);
    i = skip_whitespaces(opts, s, i);
    if (i != s.size())
    {
        throw std::runtime_error(
            std::format(
                "Did not consume exact length of the string (i == {})",
                i));
    }

    return r;
}

[[nodiscard]] FORCE_INLINE constexpr std::vector<std::vector<int>> parse2DArray(
    std::string_view s)
{
    return parse_from_string<std::vector<std::vector<int>>>(s);
}
