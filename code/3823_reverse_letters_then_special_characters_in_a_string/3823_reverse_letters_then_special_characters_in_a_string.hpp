#include <cctype>
#include <string>

#include "swap_if.hpp"

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
