#pragma once

#include <cassert>
#include <concepts>
#include <deque>
#include <format>
#include <ranges>
#include <span>
#include <sstream>
#include <vector>

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

    [[nodiscard]] static std::vector<int> StringToArray(std::string_view str)
    {
        std::stringstream stream(std::string{str});
        std::vector<int> r;

        while (!stream.eof())
        {
            assert(std::isdigit(stream.peek()) || stream.peek() == '-');
            int value{};
            stream >> value;
            r.push_back(value);

            if (int p = stream.peek(); p == ',') stream.get();
        }

        return r;
    }

    [[nodiscard]] static LeetCodeList FromString(std::string_view str)
    {
        auto array = StringToArray(str);
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
    std::string r;
    auto i = std::back_inserter(r);
    while (head)
    {
        std::format_to(i, "{},", head->val);
        head = head->next;
    }

    if (!r.empty()) r.pop_back();
    return r;
}
