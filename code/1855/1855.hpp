#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "upd_max.hpp"

class Solution
{
public:
    u32 maxDistance(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        u32 n1 = cast<u32>(nums1.size()), n2 = cast<u32>(nums2.size()), r = 0;
        for (u32 i = 0, j = 0; i != n1 && j != n2;)
        {
            u32 b = nums1[i] > nums2[j];
            i += b;
            upd_max(j, i & -b);
            upd_max(r, (j - i) & -u32{!b});
            j += !b;
        }
        return r;
    }
};
