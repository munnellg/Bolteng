#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "controller.h"
#include "keyboard.h"
#include "mouse.h"

namespace bolt {
    namespace input {
        int const MAX_CONTROLLERS = 4;
        int const CONTROLLER_STATE_SYNC_FREQ = 10000;

        extern Mouse mouse;
        extern Keyboard keyboard;
        extern std::array<Controller, MAX_CONTROLLERS> controllers;
    }
}

#endif

