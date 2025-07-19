#pragma once

#include <array>
#include <span>
#include <string>
#include <vector>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

using u8 = uint8_t;
using u16 = uint16_t;

static constexpr u16 kMaxNodes = 19'000;

struct Node
{
    u16 sibling : 15 = kMaxNodes;
    u16 is_leaf : 1 = 0;
    u16 child = kMaxNodes;
};

class Solver
{
public:
    std::string tmp;
    std::array<Node, kMaxNodes> nodes;
    std::array<std::string, kMaxNodes> tokens;
    std::array<std::string, 40'000> results;
    u16 num_results = 0;

    void rebuildPaths(u16 node) noexcept
    {
        u8 ps = tmp.size() & 0xFF;

        tmp.append(tokens[node]);
        if (nodes[node].is_leaf)
        {
            results[num_results++] = tmp;
        }
        else
        {
            tmp.push_back('/');
            for (u16 child = nodes[node].child; child != kMaxNodes;
                 child = nodes[child].sibling)
            {
                rebuildPaths(child);
            }
        }

        tmp.resize(ps);
    }

    [[nodiscard]] std::vector<std::string> removeSubfolders(
        std::vector<std::string>& paths) noexcept
    {
        num_results = 0;
        constexpr u16 root = 0;
        nodes[root].child = kMaxNodes;
        u16 num_nodes = 1;

        for (std::string& path : paths)
        {
            u16 parent = root;
            u8 len = static_cast<u8>(path.size());
            u8 pos = 0;

            while (true)
            {
                ++pos;
                u8 next_pos = static_cast<u8>(path.find('/', pos));
                next_pos = std::min(next_pos, len);
                std::string_view token{
                    path.begin() + pos,
                    path.begin() + next_pos};

                u16 existing_id = nodes[parent].child;

                while (existing_id != kMaxNodes)
                {
                    auto& node = nodes[existing_id];
                    if (tokens[existing_id] == token) break;
                    existing_id = node.sibling;
                }

                pos = next_pos;
                bool is_last = pos == len;

                if (existing_id == kMaxNodes)
                {
                    u16 new_id = num_nodes++;
                    auto& node = nodes[new_id];
                    tokens[new_id] = token;
                    node.is_leaf = is_last;
                    node.sibling = std::exchange(nodes[parent].child, new_id);
                    node.child = kMaxNodes;

                    parent = new_id;
                    if (is_last)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                if (auto& existing = nodes[existing_id];
                    existing.is_leaf || is_last)
                {
                    existing.child = kMaxNodes;
                    existing.is_leaf = 1;
                    break;
                }

                parent = existing_id;
            }
        }

        rebuildPaths(root);

        // Reuse paths array. It is always bigger than
        // the number of results so no reallocations will happen
        paths.resize(num_results);
        u16 i = 0;
        for (auto& s : std::span{results}.first(num_results))
        {
            paths[i++] = std::move(s);
        }

        return paths;
    }
};

class Solution
{
public:
    [[nodiscard]] FORCE_INLINE static std::vector<std::string> removeSubfolders(
        std::vector<std::string>& folder) noexcept
    {
        static Solver solver;
        return solver.removeSubfolders(folder);
    };
};
