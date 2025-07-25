#pragma once

#ifdef __GNUC__
#define HOT_PATH __attribute__((hot))
#else
#define FORCE_INLINE inline
#endif
