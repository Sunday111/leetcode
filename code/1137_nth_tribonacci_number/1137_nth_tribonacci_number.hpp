#include <array>

using u32 = uint32_t;

class Solution
{
public:
    inline static constexpr auto kAns = []
    {
        std::array<u32, 38> r;  // NOLINT
        r[0] = 0;
        r[1] = r[2] = 1;
        for (u32 i = 3; i != r.size(); ++i)
        {
            r[i] = r[i - 1] + r[i - 2] + r[i - 3];
        }

        return r;
    }();

    [[nodiscard]] static constexpr u32 tribonacci(u32 n) noexcept
    {
        return kAns[n];
    }
};
