#include <bit>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    std::vector<int> findThePrefixCommonArray(
        std::vector<int>& A,
        std::vector<int>& B)
    {
        auto ta = 0ul, tb = 0ul;
        u32 n = static_cast<u32>(A.size());
        std::vector<int> r(n);
        for (uint32_t i = 0; i != n; ++i)
        {
            ta |= (1ul << A[i]);
            tb |= (1ul << B[i]);
            A[i] = std::popcount(ta & tb);
        }
        return std::move(A);
    }
};
