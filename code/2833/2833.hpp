#include <string>

class Solution
{
public:
    auto furthestDistanceFromOrigin(const std::string& moves) noexcept
    {
        int pl = 0, pr = 0;
        for (char c : moves)
        {
            bool l = c != 'R';
            bool r = c != 'L';
            pl += l - !l;
            pr += r - !r;
        }
        return std::max(pl, pr);
    }
};
