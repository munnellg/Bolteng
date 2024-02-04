#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "../defines.h"

#include "controller.h"
#include "keyboard.h"
#include "mouse.h"
#include "platform.h"

namespace bolt {
    namespace input {
        extern std::array<Controller, MAX_CONTROLLERS> controllers;
        extern Keyboard keyboard;
        extern Mouse mouse;
        extern Platform platform;
    }
}

#endif

