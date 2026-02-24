#include "lc_signly_linked_list_node.hpp"

class Solution
{
public:
    void deleteNode(ListNode* node)
    {
        while (node->next->next)
        {
            node->val = node->next->val;
            node = node->next;
        }
        node->val = node->next->val;
        node->next = nullptr;
    }
};
