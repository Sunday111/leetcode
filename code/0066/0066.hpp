#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> plusOne(
        std::vector<int>& digits) noexcept
    {
        int carry = 1;
        for (size_t i = digits.size(); i--;)
        {
            int& v = digits[i];
            v += carry;
            carry = v > 9;
            v %= 10;
        }

        if (carry) digits.insert(digits.begin(), 1);

        return std::move(digits);
    }
};
