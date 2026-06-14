#include <algorithm>




#ifdef LC_LOCAL_BUILD

struct ListNode
{
    int val{};
    ListNode* next{};
};

#endif

class Solution
{
public:
    int pairSum(ListNode* head) const noexcept
    {
        static int v[100'000];
        int n = 0;
        while (head)
        {
            v[n++] = head->val;
            head = head->next;
        }

        int s = 0;
        for (int i = 0, j = n - 1; i < j; ++i, --j)
        {
            s = std::max(s, v[i] + v[j]);
        }

        return s;
    }
};

#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif
