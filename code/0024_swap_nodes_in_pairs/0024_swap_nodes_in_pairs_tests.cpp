#include "0024_swap_nodes_in_pairs.hpp"
#include "gtest/gtest.h"

TEST(t0024_swap_nodes_in_pairs, test_1)
{
    std::array<ListNode, 4> nodes;  // NOLINT
    nodes[0].next = &nodes[1];
    nodes[0].val = 1;
    nodes[1].next = &nodes[2];
    nodes[1].val = 2;
    nodes[2].next = &nodes[3];
    nodes[2].val = 3;
    nodes[3].next = nullptr;
    nodes[3].val = 4;

    [[maybe_unused]] auto r = Solution::swapPairs(nodes.data());
}
