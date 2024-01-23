#include "subsystems.h"

#include <SDL2/SDL.h>

namespace subsystems {
    namespace input {
        int init() {
            // NOOP
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
