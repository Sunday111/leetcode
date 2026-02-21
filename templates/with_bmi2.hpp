#pragma once

#include <immintrin.h>
#include <xmmintrin.h>

#define WITH_BMI2 __attribute__((__target__("bmi2")))
