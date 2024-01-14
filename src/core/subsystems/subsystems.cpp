#include "subsystems.h"
#include "../logging.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace subsystems {
    // forward declarations for private subsystem functions
    namespace input {
        void keydown(SDL_KeyboardEvent const &e);
        void keyup(SDL_KeyboardEvent const &e);
    }

    void quit() {
        input::quit();
        display::quit();
        IMG_Quit();
        SDL_Quit();

        LOG_INFO("All subsystems terminated");
    }

    void handle_events() {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    input::keydown(e.key);
                    break;
                case SDL_KEYUP:
                    input::keyup(e.key);
                    break;
                default:
                    break;
            }
        }
    }

    void pause(uint32_t ms) {
        SDL_Delay(ms);
    }

    int init() {
        LOG_INFO("Initializing subsystems");

        if (SDL_Init(SDL_INIT_EVERYTHING)) {
            LOG_ERROR("SDL_Init : %s", SDL_GetError());
            return 0;
        }

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            LOG_ERROR("IMG_Init : ", IMG_GetError());
            return 0;
        }

        if (!display::init()) {
            return 0;
        }

        if (!input::init()) {
            return 0;
        }

        LOG_INFO("All subsystems initialized");

        return 1;
    }
}
