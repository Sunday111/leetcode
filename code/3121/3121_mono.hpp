#include <bit>
#include <cstdint>
#include <string>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    int numberOfSpecialChars(const std::string& word) noexcept
    {
        u32 p[2]{}, bad{};
        for (char c : word)
        {
            bool l = c > 'Z';             // is lower case?
            auto i = c - 'A' - (l << 5);  // index in alphabet
            [[assume(i < 26)]];           // a promise to the compiler
            bad |= (u32{l} << i) & p[0];  // met lower before upper
            p[l] |= 1 << i;               // mark as visited
        }

        // both cases visited and not marked as bad
        return std::popcount(p[0] & p[1] & ~bad);
    }
};

#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif
