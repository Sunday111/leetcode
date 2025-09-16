#pragma once

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))
