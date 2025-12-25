#pragma once

#include <format>

namespace format_utils
{

template <typename FmtContext>
struct PropertyWriter
{
    using Iterator = typename FmtContext::iterator;
    explicit PropertyWriter(FmtContext& ctx) : ctx_(ctx), out(ctx.out()) {}

    void Begin() { out = std::format_to(out, "{{"); }

    template <typename Key, typename Value>
    void Prop(Key&& name, Value&& value)
    {
        if (written_any)
        {
            out = std::format_to(out, ", ");
        }

        out = std::format_to(
            out,
            "{}: {}",
            std::forward<Key>(name),
            std::forward<Value>(value));
        written_any = true;
    }

    auto End() { return out = std::format_to(out, "}}"); }

    FmtContext& ctx_;
    Iterator out;
    bool written_any = false;
};
}  // namespace format_utils
