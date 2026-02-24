

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
