#include "subsystems.h"
#include "../defines.h"

#include <SDL2/SDL.h>

namespace subsystems {
    namespace input {
        // std::array<SDL_GameController*, 4> controllers;

        int init() {

            return 1;
        }

        void keydown(SDL_KeyboardEvent const &event) {
        }

        void keyup(SDL_KeyboardEvent const &event) {
        }

        void quit() {
            // NOOP
        }
    }
}
