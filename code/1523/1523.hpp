class Solution
{
public:
    [[nodiscard]] static constexpr int countOdds(int l, int h) noexcept
    {
        return ((h - l) >> 1) + ((l | h) & 1);
    }
};
