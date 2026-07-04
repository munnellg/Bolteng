#ifndef EULER_H
#define EULER_H

#include "common.h"

namespace bolt {
    namespace maths {
        struct EulerAngles {
            Real roll;
            Real pitch;
            Real yaw;

            EulerAngles();
            EulerAngles(Real roll, Real pitch, Real yaw);

            void identity();

            void canonize();
        };
    }
}

#endif
