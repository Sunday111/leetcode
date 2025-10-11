#ifndef __clang__
#define SYNC_STDIO                   \
    auto init = []()                 \
    {                                \
        ios::sync_with_stdio(false); \
        cin.tie(nullptr);            \
        cout.tie(nullptr);           \
        return 'c';                  \
    }();
#else
#define SYNC_STDIO
#endif
