#include "gtest/gtest.h"
#include "property_writer.hpp"
#include "quoted.hpp"

using namespace format_utils;  // NOLINT

struct MyStruct
{
    int a, b;
    std::string_view c = "meow";

    template <typename FmtContext>
    constexpr auto FormatTo(FmtContext& ctx) const
    {
        PropertyWriter w{ctx};
        w.Begin();
        w.Prop(Quoted{"a"}, a);
        w.Prop(Quoted{"b"}, b);
        w.Prop(Quoted{"c"}, Quoted{c});
        return w.End();
    }
};

DECLARE_STRUCT_FORMATTER(MyStruct, FormatTo);

TEST(StructFormatterTest, Simple)
{
    std::println("{}", MyStruct{.a = 42, .b = 24});
    ASSERT_EQ(
        std::format("{}", MyStruct{.a = 42, .b = 24}),
        "{\"a\": 42, \"b\": 24, \"c\": \"meow\"}");
}
