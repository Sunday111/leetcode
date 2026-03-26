#include <bit>
#include <cstdint>
#include <string>
#include <vector>

// https://leetcode.com/problems/find-the-string-with-lcp/




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    std::string findTheString(std::vector<std::vector<int>>& lcp)
    {
        auto& m = reinterpret_cast<std::vector<std::vector<u32>>&>(lcp);

        const u16 n = m.size() & 1023;

        // Check obvious stuff
        for (u16 y = 0; y != n; ++y)
        {
            auto& row = m[y];

            // Main diagonal has to start with n in the top left corner
            // and always decrease by one
            if (row[y] != n - y) return "";

            for (u16 x = y + 1; x != n; ++x)
            {
                // must be symmetric across the main diagonal
                // (m == transpose(m))
                if (row[x] != m[x][y]) return "";

                // lsp must not exceed possible length
                if (row[x] > n - x) return "";
            }
        }

        std::string s(n, 0);
        for (u16 i = 0; i != n; ++i)
        {
            u32 bs[2]{};
            for (u16 j = 0; j != i; ++j)
            {
                bs[!m[i][j]] |= 1u << s[j];
            }

            [[unlikely]] if (
                std::popcount(bs[0]) > 1 || std::popcount(bs[1]) == 26 ||
                (bs[0] & bs[1]))
            {
                return "";
            }

            bs[1] = ~bs[1];
            s[i] = std::countr_zero(bs[!bs[0]]) & 31;  // NOLINT
        }

        for (u16 i = 0; i != n; ++i) s[i] += 'a';

        // check lengths
        for (u16 i = 0; i != n - 1; ++i)
        {
            u16 l = lcp[i][i + 1] & 0xFFFF;
            if (s[i + l] == s[i + l + 1] ||
                std::string_view{&s[i], l} != std::string_view{&s[i + 1], l})
            {
                return "";
            }
        }

        return s;
    }
};
