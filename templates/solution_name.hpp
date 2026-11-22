#pragma once

#ifdef LC_LOCAL_BUILD
#define LC_SOLUTION_NAME(suffix) Solution##suffix
#else
#define LC_SOLUTION_NAME(suffix) Solution
#endif
