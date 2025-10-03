class Solution
{
public:
    [[nodiscard]] static constexpr int maxBottlesDrunk(
        int full,
        int exchange) noexcept
    {
        int drank = full;
        for (; full >= exchange; ++drank) full -= exchange++ - 1;
        return drank;
    }
};
