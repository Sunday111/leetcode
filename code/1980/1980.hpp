#include <string>
#include <vector>

class Solution
{
public:
    std::string findDifferentBinaryString(std::vector<std::string>& nums)
    {
        std::string& r = nums[0];
        for (size_t i = 0; auto& s : nums)
        {
            r[i] = static_cast<char>(('1' - s[i]) + '0');
            ++i;
        }
        return std::move(r);
    }
};
