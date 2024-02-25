#include "util.h"
#include <cmath>
#include <iostream>

namespace bolt {
    namespace maths {
        [[nodiscard]] Real wrap_pi(Real theta) {
            if (fabs(theta) > PI) {
                Real revolutions = std::floor((theta + PI) * RECIP_TWO_PI);
                theta -= revolutions * TWO_PI;
            }

            return theta;
        }
    }
}
