#ifndef MATHS_COMMON_H
#define MATHS_COMMON_H

#include <cmath>

namespace bolt {
    namespace maths {
        typedef float Real;

        #ifndef M_PI
        constexpr Real const PI = 3.14159265f;
        #else
        constexpr Real const PI = M_PI;
        #endif

        constexpr Real const TWO_PI       = PI * 2.0;
        constexpr Real const RECIP_PI     = 1.0 / PI;
        constexpr Real const HALF_PI      = PI / 2.0;
        constexpr Real const RECIP_TWO_PI = 0.5 / PI;
    }
}

#endif
