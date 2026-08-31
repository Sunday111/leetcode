#include <algorithm>
#include <optional>
#include <vector>



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
    [[nodiscard, gnu::always_inline]] static constexpr bool is_critical_point(
        const ListNode* prev,
        const ListNode* curr) noexcept
    {
        auto a = prev->val, b = curr->val, c = curr->next->val;
        return (a < b && b > c) || (a > b && b < c);
    }

    std::vector<int> nodesBetweenCriticalPoints(const ListNode* head) noexcept
    {
        const ListNode *prev = head, *curr = prev;
        int min_dist = -1, total = -1;

        auto get_next = [&] [[gnu::always_inline]] () -> std::optional<int>
        {
            int distance = 0;
            do
            {
                ++distance;
                prev = curr;
                curr = curr->next;
            } while (curr->next && !is_critical_point(prev, curr));

            if (curr->next) return std::optional{distance};
            return std::nullopt;
        };

        auto d = get_next();
        if (d && (d = get_next()))
        {
            min_dist = total = *d;
            while ((d = get_next()))
            {
                min_dist = std::min(min_dist, *d);
                total += *d;
            }
        }

        return {min_dist, total};
    }
};
