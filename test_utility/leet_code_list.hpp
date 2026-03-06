#pragma once

#include <cassert>
#include <concepts>
#include <deque>
#include <format>
#include <ranges>
#include <span>

#include "convert_expected_type.hpp"  // IWYU pragma: export
#include "parse_2d_array.hpp"

template <typename T>
concept ListNodeConcept = requires(T a, int x) {
    // Has next property convertible to pointers of the same type
    { a.next } -> std::convertible_to<T*>;

    // Has integral val property
    requires std::integral<std::remove_cvref_t<decltype(a.val)>>;

    // constructible from integral
    T{x};
};

template <ListNodeConcept TNode>
struct LeetCodeList
{
    using NodeType = TNode;
    using ValueType = decltype(NodeType{}.val);

    std::deque<TNode> nodes;
    TNode* head = nullptr;

    [[nodiscard]] TNode* AllocNode(int value)
    {
        nodes.emplace_back(value);
        return &nodes.back();
    }

    template <typename Value, size_t extent = std::dynamic_extent>
        requires(std::same_as<std::decay_t<Value>, int>)
    [[nodiscard]] static LeetCodeList FromArray(std::span<Value, extent> values)
    {
        LeetCodeList<TNode> list;

        if (!values.empty())
        {
            list.head = list.AllocNode(values.front());
            auto prev = list.head;
            for (auto v : values | std::views::drop(1))
            {
                prev->next = list.AllocNode(v);
                prev = prev->next;
            }
        }

        return list;
    }

    [[nodiscard]] static LeetCodeList FromString(std::string_view s)
    {
        auto array = parse_from_string<std::vector<int>>(s);
        auto view = std::span{array};
        return FromArray(view);
    }
};

template <ListNodeConcept TNode>
[[nodiscard]] inline constexpr bool CompareLists(TNode* a, TNode* b)
{
    while (a && b)
    {
        if (a->val != b->val) return false;
        a = a->next;
        b = b->next;
    }

    return !a == !b;
}

template <ListNodeConcept TNode>
[[nodiscard]] inline constexpr std::string ListToString(TNode* head)
{
    std::string r = "[";
    auto i = std::back_inserter(r);
    while (head)
    {
        std::format_to(i, "{},", head->val);
        head = head->next;
    }

    if (r.size() > 1) r.pop_back();
    r.push_back(']');
    return r;
}

template <ListNodeConcept TNode, typename V>
[[nodiscard]] inline constexpr TNode* FindFirst(TNode* head, const V& value)
{
    while (head && head->val != value) head = head->next;
    return head;
}

template <ListNodeConcept Node>
struct ConvertExpectedType<Node*, void>
{
    using Result = LeetCodeList<Node>;
};

template <typename Options, is_specialization<LeetCodeList> T>
[[nodiscard]] constexpr size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& r)
{
    std::vector<typename T::ValueType> vals;
    size_t i = do_scan(opts, s, start, vals);
    r = T::FromArray(std::span{vals});
    return i;
}
