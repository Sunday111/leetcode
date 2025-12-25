#pragma once

#include "struct_formatter.hpp"

namespace format_utils
{

template <typename T>
struct Quoted
{
    template <typename FmtContext>
    constexpr auto FormatTo(FmtContext& ctx) const
    {
        return std::format_to(ctx.out(), "\"{}\"", value);
    }

    const T& value;
};

}  // namespace format_utils

DECLARE_TEMPLATE_FORMATTER(format_utils::Quoted, FormatTo);
