#ifndef MOUSE_H
#define MOUSE_H

#include "../defines.h"
#include "../subsystems/subsystems.h"

namespace bolt {
    namespace input {
        class Mouse {
        private:
            int m_posX;
            int m_posY;

            friend void subsystems::events::process();
        };
    }
}
#endif
