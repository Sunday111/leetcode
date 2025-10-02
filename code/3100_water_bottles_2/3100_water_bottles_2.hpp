class Solution
{
public:
    [[nodiscard]] static constexpr int maxBottlesDrunk(
        int full,
        int exchange) noexcept
    {
        int drank = full;
        while (full >= exchange)
        {
            full -= exchange++ - 1;
            ++drank;
        }
        return drank;
    }
};
