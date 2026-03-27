#include <vector>


// https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] constexpr bool areSimilar(
        const std::vector<std::vector<int>>& mat,
        u8 k) const noexcept
    {
        u8 w = mat[0].size() & 31;
        if ((k % w) == 0 || w == 1) return true;
        for (auto& r : mat)
        {
            for (u8 i = 0, j = k % w; i != w; ++i, ++j)
            {
                j &= -(j != w);
                if (r[i] != r[j]) return false;
            }
        }
        return true;
    }
};
