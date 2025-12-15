#pragma once

#include <print>

#include "overload.hpp"

struct NoNewLineTag
{
};
inline static constexpr NoNewLineTag no_new_line{};

// By default prints line. But doesn't do that if 'no_new_line' tag is specified
// as the first parameter
template <bool enabled>
inline static constexpr auto Logger = Overload{
    []<typename... Args>(std::format_string<Args...> fmt, Args&&... args)
    {
        if constexpr (enabled)
        {
            std::println(fmt, std::forward<Args>(args)...);
        }
    },

    []<typename... Args>(
        NoNewLineTag,
        std::format_string<Args...> fmt,
        Args&&... args)
    {
        if constexpr (enabled)
        {
            std::print(fmt, std::forward<Args>(args)...);
        }
    },
};
