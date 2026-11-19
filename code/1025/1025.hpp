class Solution
{
public:
    [[nodiscard]] static constexpr bool divisorGame(int n) noexcept
    {
        return !(n & 1);
    }
};
