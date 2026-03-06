#include <algorithm>

#include "lc_signly_linked_list_node.hpp"

class Solution
{
public:
    int pairSum(ListNode* head)
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
