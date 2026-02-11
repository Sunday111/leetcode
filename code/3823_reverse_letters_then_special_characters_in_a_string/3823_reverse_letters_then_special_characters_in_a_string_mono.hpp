#include <cctype>
#include <concepts>
#include <string>





#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

// Swaps a and b if condition is true. Only for integers. Branchless
template <std::integral Int>
FORCE_INLINE static constexpr void
swap_if(bool condition, Int& a, Int& b) noexcept
{
    Int mask = static_cast<Int>(static_cast<Int>(a ^ b) & -Int{condition});
    a ^= mask, b ^= mask;
}

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr std::string reverseByType(
        std::string& s) noexcept
    {
        const u8 n = s.size() & 0xFF;
        for (u8 i = 0, j = n - 1; i < j;)
        {
            char &ci = s[i], &cj = s[j];
            bool bi = std::isalpha(ci), bj = std::isalpha(cj), bx = bi && bj;
            swap_if(bx, ci, cj);
            i += bx || !bi;
            j -= bx || !bj;
        }
        for (u8 i = 0, j = n - 1; i < j;)
        {
            char &ci = s[i], &cj = s[j];
            bool bi = !std::isalpha(ci), bj = !std::isalpha(cj), bx = bi && bj;
            swap_if(bx, ci, cj);
            i += bx || !bi;
            j -= bx || !bj;
        }
        return std::move(s);
    }
};
