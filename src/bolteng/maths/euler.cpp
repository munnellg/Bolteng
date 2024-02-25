#include "euler.h"

#include "common.h"
#include "util.h"

namespace bolt {
    namespace maths {
        EulerAngles::EulerAngles() : 
            roll(0.0),
            pitch(0.0),
            yaw(0.0)
        {}

        EulerAngles::EulerAngles(Real r, Real p, Real y) :
            roll(r),
            pitch(p),
            yaw(y)
        {}

        void EulerAngles::identity() {
            roll = pitch = yaw = 0.0;
        }

        void EulerAngles::canonize() {
            pitch = wrap_pi(pitch);

            if (pitch < -HALF_PI) {
                pitch = -PI - pitch;
                yaw += PI;
                roll += PI;
            } else if (pitch > HALF_PI) {
                pitch = PI - pitch;
                yaw += PI;
                roll += PI;
            }

            if (fabs(pitch) > HALF_PI - 1e-4) {
                yaw += roll;
                roll = 0.0;
            } else {
                // not in gimbel lock.
                roll = wrap_pi(roll);
            }

            yaw = wrap_pi(yaw);
        }
    }
}
