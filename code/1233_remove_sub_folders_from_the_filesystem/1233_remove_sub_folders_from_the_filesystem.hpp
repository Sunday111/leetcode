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
    char* token_ptr = nullptr;
    u16 sibling = kMaxNodes;
    u16 child = kMaxNodes;
    u8 token_size = 0;
    bool is_leaf = 0;

    [[nodiscard]] FORCE_INLINE constexpr std::string_view token() const noexcept
    {
        return std::string_view{token_ptr, token_size};
    }
};

static_assert(sizeof(Node) == 16);
static_assert(alignof(Node) == 8);

class Solver
{
public:
    std::string tmp;
    std::array<Node, kMaxNodes> nodes;
    std::array<std::string, 40'000> results;
    u16 num_results = 0;

    void rebuildPaths(u16 node) noexcept
    {
        u8 ps = tmp.size() & 0xFF;

        tmp.append(nodes[node].token());
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
        tmp.reserve(128);

        for (std::string& path : paths)
        {
            u16 parent = root;
            u8 len = static_cast<u8>(path.size());
            u8 pos = 0;

            while (true)
            {
                char* const token_ptr = &path[++pos];
                const u8 next_pos =
                    std::min(len, static_cast<u8>(path.find('/', pos)));
                const u8 token_size = next_pos - std::exchange(pos, next_pos);
                const bool is_last = pos == len;

                u16 existing_id = nodes[parent].child;
                const std::string_view token{token_ptr, token_size};
                while (existing_id != kMaxNodes)
                {
                    auto& node = nodes[existing_id];
                    if (node.token() == token) break;
                    existing_id = node.sibling;
                }

                if (existing_id == kMaxNodes)
                {
                    u16 id = num_nodes++;
                    nodes[id] = {
                        .token_ptr = token_ptr,
                        .sibling = std::exchange(nodes[parent].child, id),
                        .child = kMaxNodes,
                        .token_size = token_size,
                        .is_leaf = is_last,
                    };

                    parent = id;
                    if (is_last)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                parent = existing_id;
                if (auto& existing = nodes[existing_id];
                    existing.is_leaf || is_last)
                {
                    existing.child = kMaxNodes;
                    existing.is_leaf = true;
                    break;
                }
            }
        }

        rebuildPaths(root);

        // Reuse paths array. It is always bigger than
        // the number of results so no reallocations will happen
        paths.resize(num_results);
        u16 i = 0;
        for (auto& s : std::span{results}.first(num_results))
        {
            paths[i++] = s;
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
