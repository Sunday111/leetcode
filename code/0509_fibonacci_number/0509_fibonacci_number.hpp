#include <array>

class Solution
{
public:
    using u32 = uint32_t;

    inline static constexpr auto kFib = []()
    {
        std::array<u32, 31> r;  // NOLINT
        r[0] = 0;
        r[1] = 1;
        for (u32 i = 2; i != r.size(); ++i) r[i] = r[i - 1] + r[i - 2];
        return r;
    }();

    [[nodiscard]] static constexpr u32 fib(u32 n) noexcept { return kFib[n]; }
};
