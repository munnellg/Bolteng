#include "subsystems.h"
#include "../logging.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace subsystems {

    void quit() {
        events::quit();
        display::quit();
        IMG_Quit();
        SDL_Quit();

        LOG_INFO("All subsystems terminated");
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

        if (!events::init()) {
            return 0;
        }

        if (!render::init()) {
            return 0;
        }

        LOG_INFO("All subsystems initialized");

        return 1;
    }
}
