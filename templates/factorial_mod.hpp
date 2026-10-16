#include <array>

#include "integral_aliases.hpp"
#include "mod_int.hpp"

template <u32 max_index>
inline constexpr auto factorials_mods()
{
    std::array<ModInt, max_index + 1> r;  // NOLINT
    r[0] = ModInt{1};
    for (u32 i = 1; i != r.size(); ++i)
    {
        r[i] = r[i - 1] * ModInt{i};
    }

    return r;
}
