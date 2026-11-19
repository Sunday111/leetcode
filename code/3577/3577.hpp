#include <algorithm>
#include <span>

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;

    [[nodiscard]] static constexpr u32 countPermutations(
        std::span<const int> complexity) noexcept
    {
        constexpr u32 kMOD = 1'000'000'007;
        if (complexity[0] < std::ranges::min(complexity.subspan(1)))
        {
            u64 r = 1;
            for (u32 i = 1; i != complexity.size(); ++i) (r *= i) %= kMOD;
            return r % kMOD;
        }

        return 0;
    }
};
