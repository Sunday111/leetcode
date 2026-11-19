#include <algorithm>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

struct GraphLink
{
    u8 from;
    u8 to;
};

class OrientedGraph
{
public:
    OrientedGraph(size_t n, bool init_value)
        : n_(n),
          matrix_(n_ * n_, init_value)
    {
    }

    size_t GetBitsetIndex(size_t from, size_t to) const noexcept
    {
        // from is a row, to is a column
        size_t index = from * n_ + to;
        return index;
    }

    void Link(size_t from, size_t to) noexcept { ChangeLink<true>(from, to); }

    void Unlink(size_t from, size_t to) noexcept
    {
        ChangeLink<false>(from, to);
    }

    void BakeLinks()
    {
        std::vector<size_t> incoming_links_count(n_);

        auto add_link = [&](size_t from, size_t to)
        {
            const size_t index = GetBitsetIndex(from, to);
            if (matrix_[index])
            {
                auto link_cmp = [](const GraphLink& a, const GraphLink& b)
                {
                    if (a.from == b.from)
                    {
                        return a.to < b.to;
                    }

                    return a.from < b.from;
                };

                GraphLink link{cast<u8>(from), cast<u8>(to)};
                auto insert_it = std::lower_bound(
                    links_.begin(),
                    links_.end(),
                    link,
                    link_cmp);
                links_.insert(insert_it, link);
                ++incoming_links_count[to];
            }
        };

        for (size_t from = 0; from != n_; ++from)
        {
            for (size_t to = 0; to != from; ++to)
            {
                add_link(from, to);
            }
            for (size_t to = from + 1; to != n_; ++to)
            {
                add_link(from, to);
            }
        }

        for (u8 i = 0; i != cast<u8>(n_); ++i)
        {
            if (incoming_links_count[i] == 0)
            {
                leafs_.push_back(i);
            }
        }
    }

    u8 FindLongestPathLength() const
    {
        u8 max_length = 1;
        std::vector<u8> lengths(n_, 0);
        for (u8 leaf : leafs_)
        {
            lengths[leaf] = 1;
            FindLongestPathLengthRecursive(leaf, lengths, max_length);
        }

        // u8 max_length = 1;
        // for (u8 length: lengths) {
        //     max_length = std::max(max_length, length);
        // }

        return max_length;
    }

    void FindLongestPathLengthRecursive(
        u8 from,
        std::vector<u8>& lengths,
        u8& max_length) const
    {
        auto it = std::lower_bound(
            links_.begin(),
            links_.end(),
            from,
            [](const GraphLink& link, size_t from)
            { return link.from < from; });

        while (it != links_.end() && it->from == from)
        {
            if ((lengths[from] + 1) > lengths[it->to])
            {
                lengths[it->to] = lengths[from] + 1;
                max_length = std::max(lengths[it->to], max_length);
                FindLongestPathLengthRecursive(it->to, lengths, max_length);
            }
            ++it;
        }
    }

    size_t GetLinksCount() const noexcept { return links_.size(); }

    const std::vector<u8> GetLeafs() const noexcept { return leafs_; }

private:
    template <bool value>
    void ChangeLink(size_t from, size_t to) noexcept
    {
        size_t index = GetBitsetIndex(from, to);
        matrix_[index] = value;
    }

private:
    size_t n_;
    std::vector<bool> matrix_;
    std::vector<GraphLink> links_;
    std::vector<u8> leafs_;
};

class Solution
{
public:
    int minDeletionSize(const std::vector<std::string>& rows)
    {
        const u8 rows_count = cast<u8>(rows.size());
        const u8 columns_count = cast<u8>(rows.front().size());

        if (columns_count < 2)
        {
            return 0;
        }

        OrientedGraph g(columns_count, false);
        for (size_t from = 0; from != columns_count; ++from)
        {
            for (size_t to = from + 1; to != columns_count; ++to)
            {
                bool can_link = true;
                for (size_t row = 0; row != rows_count; ++row)
                {
                    if (rows[row][from] > rows[row][to])
                    {
                        can_link = false;
                        break;
                    }
                }

                if (can_link)
                {
                    g.Link(from, to);
                }
            }
        }

        g.BakeLinks();

        std::vector<u8> path_cache;
        size_t max_path = g.FindLongestPathLength();
        const size_t min_deletion = columns_count - max_path;

        return static_cast<int>(min_deletion);
    }
};
