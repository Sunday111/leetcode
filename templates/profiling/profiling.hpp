#pragma once

#include <cassert>
#include <chrono>
#include <deque>
#include <ranges>
#include <source_location>
#include <vector>

#include "format/property_writer.hpp"
#include "format/quoted.hpp"
#include "integral_aliases.hpp"
#include "tagged_id.hpp"

namespace profiling
{

namespace tags
{
struct EntryID;
struct SourceID;

}  // namespace tags

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;

using EntryId = TaggedID<tags::EntryID, u64>;
using SourceId = TaggedID<tags::SourceID, u32>;

enum class Status : u8
{
    // Function is in progress, source and start time are available
    Started,

    // Stepped in. Child is available
    GotChild,

    // Function has completed execution.
    // This state can transition to GotSibling or LastChild
    Completed,

    GotSibling,
    LastChild,
};

struct ProfilerEntry
{
    SourceId source = kInvalidId;

    TimePoint start;
    TimePoint finish;

    EntryId child = kInvalidId;
    EntryId sibling = kInvalidId;

    Status status = Status::Started;
};

struct SourceInfo
{
    std::string_view name;
    std::source_location location;
};

class Profiler
{
public:
    static Profiler& Instance()
    {
        static Profiler instance;
        return instance;
    }

    inline static constexpr std::string_view kRootNodeName = "root";

    EntryId root_entry_id = kInvalidId;
    EntryId current_entry_id = kInvalidId;
    EntryId last_child_entry_id = kInvalidId;

    std::deque<SourceInfo> sources;
    std::vector<ProfilerEntry> entries;

    [[nodiscard]] inline EntryId BeginEntry(SourceId src_id)
    {
        EntryId current_id = CreateEntry(src_id);

        auto& current = entries[current_id.GetValue()];
        current.start = Clock::now();

        if (last_child_entry_id.IsValid())
        {
            auto& sibling = entries[last_child_entry_id.GetValue()];
            sibling.sibling = current_id;
            sibling.status = Status::GotSibling;
            last_child_entry_id = kInvalidId;
        }
        else
        {
            auto& parent = entries[current_entry_id.GetValue()];
            parent.child = current_id;
            parent.status = Status::GotChild;
        }

        current_entry_id = current_id;
        return current_id;
    }

    void EndEntry([[maybe_unused]] EntryId current_id, EntryId parent_id)
    {
        auto& current = entries[current_id.GetValue()];
        current.finish = Clock::now();
        current.status = Status::Completed;

        assert(current_id == current_entry_id);
        if (last_child_entry_id != kInvalidId)
        {
            auto& last_child = entries[last_child_entry_id.GetValue()];
            last_child.status = Status::LastChild;
        }

        last_child_entry_id = current_entry_id;
        current_entry_id = parent_id;
    }

    void Start(std::source_location location = std::source_location::current())
    {
        assert(
            !root_entry_id.IsValid() && !current_entry_id.IsValid() &&
            !last_child_entry_id.IsValid());
        root_entry_id = CreateEntry(RegisterSource(
            SourceInfo{
                .name = kRootNodeName,
                .location = location,
            }));
        auto& entry = entries[root_entry_id.GetValue()];
        entry.start = Clock::now();
        current_entry_id = root_entry_id;
    }

    void Finish()
    {
        assert(current_entry_id == root_entry_id);
        auto& root_entry = entries[root_entry_id.GetValue()];
        root_entry.finish = Clock::now();
        root_entry.status = Status::Completed;
    }

    [[nodiscard]] inline SourceId RegisterSource(SourceInfo&& info)
    {
        SourceId id = SourceId::FromValue(static_cast<u32>(sources.size()));
        sources.emplace_back(std::move(info));  // NOLINT
        return id;
    }

    [[nodiscard]] inline const SourceInfo& GetSourceInfo(SourceId id) const
    {
        return sources[id.GetValue()];
    }

private:
    [[nodiscard]] EntryId CreateEntry(SourceId src)
    {
        EntryId entry_id =
            EntryId::FromValue(static_cast<EntryId::Repr>(entries.size()));
        auto& entry = entries.emplace_back();
        entry.source = src;
        return entry_id;
    }

    Profiler() {}
};

template <auto = []{}>
profiling::SourceId register_source(
    std::string_view short_name,
    std::source_location location = std::source_location::current())
{
    static auto src_id = profiling::Profiler::Instance().RegisterSource({
        .name = short_name,
        .location = location,
    });
    return src_id;
}

template <auto = []{}>
struct Scope
{
    EntryId entry = kInvalidId;
    EntryId parent = kInvalidId;

    explicit Scope(
        std::string_view short_name,
        std::source_location location =
            std::source_location::current()) noexcept
    {
        auto& p = profiling::Profiler::Instance();
        static auto src_id = p.RegisterSource({
            .name = short_name,
            .location = location,
        });

        parent = p.current_entry_id;
        entry = p.BeginEntry(src_id);
    }

    ~Scope() noexcept { Profiler::Instance().EndEntry(entry, parent); }
};

struct SpeedScopeFrame
{
    template <typename FmtContext>
    constexpr auto FormatTo(FmtContext& ctx) const
    {
        using format_utils::PropertyWriter;
        using format_utils::Quoted;
        PropertyWriter w{ctx};

        w.Begin();
        w.Prop(Quoted{"name"}, Quoted{name});
        w.Prop(Quoted{"file"}, Quoted{file});
        w.Prop(Quoted{"line"}, line);
        w.Prop(Quoted{"col"}, col);
        return w.End();
    }

    std::string_view name;
    std::string_view file;
    uint32_t line;
    uint32_t col;
};

struct SpeedScopeShared
{
    template <typename FmtContext>
    constexpr auto FormatTo(FmtContext& ctx) const
    {
        using format_utils::PropertyWriter;
        using format_utils::Quoted;
        PropertyWriter w{ctx};

        w.Begin();
        w.Prop(
            Quoted{"frames"},
            p.sources | std::views::transform(
                            [&](const SourceInfo& source) -> SpeedScopeFrame
                            {
                                return SpeedScopeFrame{
                                    .name = source.name,
                                    .file = source.location.file_name(),
                                    .line = source.location.line(),
                                    .col = source.location.column(),
                                };
                            }));

        return w.End();
    }

    const Profiler& p;
};

struct SpeedScopeEvent
{
    template <typename FmtContext>
    constexpr auto FormatTo(FmtContext& ctx) const
    {
        using format_utils::PropertyWriter;
        using format_utils::Quoted;
        PropertyWriter w{ctx};

        w.Begin();
        w.Prop(Quoted{"type"}, Quoted{type});
        w.Prop(Quoted{"frame"}, frame.GetValue());
        w.Prop(Quoted{"at"}, at);
        return w.End();
    }

    std::string_view type;
    SourceId frame;
    long long at;
};

struct SpeedScopeProfile
{
    template <typename FmtContext>
    constexpr auto FormatTo(FmtContext& ctx) const
    {
        using format_utils::PropertyWriter;
        using format_utils::Quoted;

        auto& root = p.entries[p.root_entry_id.GetValue()];
        auto start_time = root.start;

        auto get_ns = [&](TimePoint t) -> long long
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(
                       t - start_time)
                .count();
        };

        PropertyWriter w{ctx};
        w.Begin();
        w.Prop(Quoted{"type"}, Quoted{"evented"});
        w.Prop(Quoted{"name"}, Quoted{"simple.txt"});
        w.Prop(Quoted{"unit"}, Quoted{"nanoseconds"});
        w.Prop(Quoted{"startValue"}, 0);
        w.Prop(Quoted{"endValue"}, get_ns(root.finish));

        std::vector<SpeedScopeEvent> events;
        events.reserve(p.entries.size() * 2);
        [&](this auto&& self, profiling::EntryId node_id) -> void
        {
            auto& node = p.entries[node_id.GetValue()];
            auto child_id = node.child;
            events.push_back(
                SpeedScopeEvent{
                    .type = "O",
                    .frame = node.source,
                    .at = get_ns(node.start),
                });

            while (child_id.IsValid())
            {
                auto& child = p.entries[child_id.GetValue()];
                self(child_id);
                child_id = child.sibling;
            }

            events.push_back(
                SpeedScopeEvent{
                    .type = "C",
                    .frame = node.source,
                    .at = get_ns(node.finish),
                });
        }(p.root_entry_id);

        w.Prop(Quoted{"events"}, events);

        return w.End();
    }

    const Profiler& p;
};

struct SpeedScopeJSON
{
    template <typename FmtContext>
    constexpr auto FormatTo(FmtContext& ctx) const
    {
        using format_utils::PropertyWriter;
        using format_utils::Quoted;
        PropertyWriter w{ctx};
        w.Begin();
        w.Prop(Quoted{"version"}, Quoted{"0.0.1"});
        w.Prop(
            Quoted{"$schema"},
            Quoted{"https://www.speedscope.app/file-format-schema.json"});
        w.Prop(Quoted{"shared"}, SpeedScopeShared{p});
        std::array<SpeedScopeProfile, 1> profiles{{SpeedScopeProfile{p}}};
        w.Prop(Quoted{"profiles"}, profiles);
        return w.End();
    }

    Profiler& p;
};

}  // namespace profiling

DECLARE_STRUCT_FORMATTER(profiling::SpeedScopeEvent, FormatTo);
DECLARE_STRUCT_FORMATTER(profiling::SpeedScopeFrame, FormatTo);
DECLARE_STRUCT_FORMATTER(profiling::SpeedScopeShared, FormatTo);
DECLARE_STRUCT_FORMATTER(profiling::SpeedScopeProfile, FormatTo);
DECLARE_STRUCT_FORMATTER(profiling::SpeedScopeJSON, FormatTo);
