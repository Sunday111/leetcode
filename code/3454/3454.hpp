#include <algorithm>
#include <vector>

#include "bump_allocator.hpp"
#include "bump_map.hpp"
#include "bump_set.hpp"
#include "bump_vector.hpp"
#include "cast.hpp"
#include "integral_aliases.hpp"

using Storage = GlobalBufferStorage<1u << 25>;

struct Event
{
    u32 x1, x2, y, type;
};

struct Node
{
    u32 covered_cnt : 31 = 0;
    u32 covered_len : 31 = 0;
    u32 left_covered : 1 = 0;
    u32 right_covered : 1 = 0;
};
struct SegmentTree
{
    BumpVector<u32, Storage> vals;
    BumpVector<Node, Storage> tree;

    explicit SegmentTree(const BumpSet<u32, Storage>& st)
        : vals(st.begin(), st.end()),
          tree(4 * st.size())
    {
    }

    void update_range(u32 l, u32 r, u32 delta)
    {
        update_range(l, r, delta, 1, 0, cast<u32>(vals.size()) - 1);
    }

    void update_range(u32 l, u32 r, u32 delta, u32 v, u32 vl, u32 vr)
    {
        if (vl > r || vr < l) return;

        u32 mid = (vl + vr) / 2;
        if (l <= vl && vr <= r)
        {
            tree[v].covered_cnt += delta;
        }
        else
        {
            update_range(l, r, delta, 2 * v, vl, mid);
            update_range(l, r, delta, 2 * v + 1, mid + 1, vr);
        }
        if (tree[v].covered_cnt)
        {
            tree[v].covered_len = vals[vr] - vals[vl] + 1;
            tree[v].left_covered = tree[v].right_covered = true;
        }
        else if (vl == vr)
        {
            tree[v].covered_len = 0;
            tree[v].left_covered = tree[v].right_covered = false;
        }
        else
        {
            tree[v].covered_len =
                tree[2 * v].covered_len + tree[2 * v + 1].covered_len;
            if (tree[2 * v].right_covered && tree[2 * v + 1].left_covered)
            {
                tree[v].covered_len += vals[mid + 1] - vals[mid] - 1;
            }
            tree[v].left_covered = tree[2 * v].left_covered;
            tree[v].right_covered = tree[2 * v + 1].right_covered;
        }
    }
    u32 covered() { return tree[1].covered_len; }
};

class Solution
{
public:
    double separateSquares(std::vector<std::vector<int>>& squares_)
    {
        auto arena = Storage::Instance().StartArena();

        auto& squares =
            reinterpret_cast<std::vector<std::vector<u32>>&>(squares_);

        BumpMap<u32, u32, Storage> mapping;
        BumpSet<u32, Storage> vals;
        for (auto& sq : squares)
        {
            vals.insert(sq[0] - 1);
            vals.insert(sq[0]);
            vals.insert(sq[0] + sq[2] - 1);
            vals.insert(sq[0] + sq[2]);
        }
        for (u32 s = 0; auto v : vals) mapping[v] = s++;

        BumpVector<Event, Storage> events;
        for (auto& sq : squares)
        {
            u32 x1 = sq[0], x2 = sq[0] + sq[2] - 1;
            events.emplace_back(mapping[x1], mapping[x2], sq[1], 1);
            events.emplace_back(
                mapping[x1],
                mapping[x2],
                sq[1] + sq[2],
                0xFFFFFFFF);
        }
        std::ranges::sort(events, std::less{}, &Event::y);

        SegmentTree segtree(vals);

        u32 prev_y = 0;
        u64 total_area = 0;
        for (auto& event : events)
        {
            total_area += u64{event.y - prev_y} * segtree.covered();
            prev_y = event.y;
            segtree.update_range(event.x1, event.x2, event.type);
        }

        u64 current_area = 0;
        prev_y = 0;
        for (auto& event : events)
        {
            u64 next_area =
                current_area + u64{event.y - prev_y} * segtree.covered();
            if (next_area >= (total_area + 1) / 2)
            {
                return prev_y + ((cast<double>(total_area) / 2) -
                                 cast<double>(current_area)) /
                                    segtree.covered();
            }
            else
            {
                current_area = next_area;
            }
            prev_y = event.y;
            segtree.update_range(event.x1, event.x2, event.type);
        }
        std::unreachable();
    }
};
