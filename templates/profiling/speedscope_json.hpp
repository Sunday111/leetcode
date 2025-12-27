#pragma once

#include <ranges>
#include <vector>

#include "format/property_writer.hpp"
#include "format/quoted.hpp"
#include "profiling.hpp"

namespace profiling
{
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
            p.GetSources() |
                std::views::transform(
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

        auto& root = p.GetFrames()[p.root_frame_id.GetValue()];
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
        events.reserve(p.GetFrames().size() * 2);
        [&](this auto&& self, profiling::FrameId node_id) -> void
        {
            auto& node = p.GetFrames()[node_id.GetValue()];
            auto child_id = node.child;
            events.push_back(
                SpeedScopeEvent{
                    .type = "O",
                    .frame = node.source,
                    .at = get_ns(node.start),
                });

            while (child_id.IsValid())
            {
                auto& child = p.GetFrames()[child_id.GetValue()];
                self(child_id);
                child_id = child.sibling;
            }

            events.push_back(
                SpeedScopeEvent{
                    .type = "C",
                    .frame = node.source,
                    .at = get_ns(node.finish),
                });
        }(p.root_frame_id);

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
