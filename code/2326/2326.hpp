#pragma once

#include <ranges>
#include <vector>

struct ListNode
{
    int val = 0;
    ListNode* next{};
};

class Solution
{
public:
    __attribute__((no_sanitize("all"))) std::vector<std::vector<int>>
    spiralMatrix(unsigned height, unsigned width, ListNode* head)
    {
        std::vector matrix(height, std::vector<int>(width, -1));
        unsigned offset_x = 0, offset_y = 0;

        using std::views::reverse;
        auto range = [](unsigned n)
        {
            return std::views::iota(unsigned{}, n);
        };

        auto add = [&](unsigned x, unsigned y)
        {
            matrix[offset_y + y][offset_x + x] = head->val;
            head = head->next;
        };

        if (head)
        {
            [&]
            {
                while (true)
                {
                    // add top row
                    for (auto x : range(width))
                    {
                        add(x, 0);
                        if (!head) return;
                    }
                    ++offset_y;
                    if (--height == 0) break;

                    // add right column
                    for (auto y : range(height))
                    {
                        add(width - 1, y);
                        if (!head) return;
                    }
                    if (--width == 0) break;

                    // add bottom row in reverse order
                    for (auto x : range(width) | reverse)
                    {
                        add(x, height - 1);
                        if (!head) return;
                    }
                    if (--height == 0) break;

                    // add left column in reverse order
                    for (auto y : range(height) | reverse)
                    {
                        add(0, y);
                        if (!head) return;
                    }
                    ++offset_x;
                    if (--width == 0) break;
                }
            }();
        }

        return matrix;
    }
};
