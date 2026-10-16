#include <array>
#include <cassert>
#include <cstddef>

#include "integral_aliases.hpp"
#include "mod_int.hpp"

template <std::size_t lim_factorial>
constexpr ModInt
binomial_coefficient(const std::array<ModInt, lim_factorial>& f, u32 n, u32 k)
{
    assert(n >= k);
    return f[n] / (f[k] * f[n - k]);
}
