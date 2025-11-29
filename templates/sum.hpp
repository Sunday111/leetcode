#include <ranges>

#include "force_inline.hpp"

inline static constexpr auto sum =
    []<typename Range>(
        Range&& range,
        auto init = std::ranges::range_value_t<Range>{}) INLINE_LAMBDA
{
    for (auto&& v : std::forward<Range>(range))
    {
        init += v;
    }

    return init;
};
