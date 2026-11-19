#include <string>

class Solution
{
public:
    [[nodiscard]] std::string addBinary(std::string& a, std::string& b) noexcept
    {
        if (a.size() < b.size()) std::swap(a, b);

        int carry = 0;
        size_t ia = a.size(), ib = b.size();

        while (ib--)
        {
            --ia;
            int v = (a[ia] - '0') + (b[ib] - '0') + carry;
            carry = v > 1;
            a[ia] = static_cast<char>('0' + (v & 1));
        }

        while (carry && ia--)
        {
            int v = (a[ia] - '0') + carry;
            carry = v > 1;
            a[ia] = static_cast<char>('0' + (v & 1));
        }

        if (carry) a.insert(a.begin(), '1');

        return std::move(a);
    }
};
