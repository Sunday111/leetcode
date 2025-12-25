#pragma once

#include <format>
#include <type_traits>

namespace format_utils
{
template <typename T>
struct IsFormattable : std::false_type
{
};

template <typename T>
concept Formattable = IsFormattable<T>::value;

struct FormatterWithEmptyParse
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        auto i = ctx.begin(), end = ctx.end();
        if (i != end && *i != '}') throw std::format_error("invalid format");
        return i;
    }
};
}  // namespace format_utils

// This makes a specialization for std::formatter which calls TypeName::Method
// to write type to text stream Must be used in the global namespace and first
// argument must contain type namespace (if any)
#define DECLARE_STRUCT_FORMATTER(TypeName, Method)                          \
    template <>                                                             \
    struct format_utils::IsFormattable<TypeName>                            \
    {                                                                       \
        static constexpr bool kValue = true;                                \
    };                                                                      \
                                                                            \
    template <>                                                             \
    struct std::formatter<TypeName> : format_utils::FormatterWithEmptyParse \
    {                                                                       \
        template <typename FmtContext>                                      \
        constexpr auto format(const TypeName& value, FmtContext& ctx) const \
            -> decltype(ctx.out())                                          \
        {                                                                   \
            value.Method(ctx);                                              \
            return ctx.out();                                               \
        }                                                                   \
    }

#define DECLARE_TEMPLATE_FORMATTER(TypeName, Method)                           \
    template <typename X>                                                      \
    struct format_utils::IsFormattable<TypeName<X>>                            \
    {                                                                          \
        static constexpr bool kValue = true;                                   \
    };                                                                         \
                                                                               \
    template <typename X>                                                      \
    struct std::formatter<TypeName<X>> : format_utils::FormatterWithEmptyParse \
    {                                                                          \
        template <typename FmtContext>                                         \
        constexpr auto format(const TypeName<X>& value, FmtContext& ctx) const \
            -> decltype(ctx.out())                                             \
        {                                                                      \
            value.Method(ctx);                                                 \
            return ctx.out();                                                  \
        }                                                                      \
    }
