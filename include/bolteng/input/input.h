#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "../defines.h"

#include "game_pad.h"
#include "keyboard.h"
#include "mouse.h"
#include "platform.h"

namespace bolt {
    namespace input {
        extern std::array<GamePad, MAX_GAME_PADS> game_pads;
        extern Keyboard keyboard;
        extern Mouse mouse;
        extern Platform platform;
    }
}

#endif

