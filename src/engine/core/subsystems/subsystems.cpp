#include "subsystems.h"
#include "../logging.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>

static std::function<void(SDL_KeyboardEvent)> g_cb_key;
static std::function<void(void)> g_cb_quit;

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

    void register_key_callback(std::function<void(SDL_KeyboardEvent)> keyboard) {
        g_cb_key = keyboard;
    }

    void register_quit_callback(std::function<void(void)> cb_quit) {
        g_cb_quit = cb_quit;
    }

    void handle_events() {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    g_cb_quit();
                    break;
                case SDL_KEYDOWN:
                    g_cb_key(e.key);
                    break;
                case SDL_KEYUP:
                    input::keyup(e.key);
                    break;
                default:
                    break;
            }
        }
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

        if (!render::init()) {
            return 0;
        }

        LOG_INFO("All subsystems initialized");

        return 1;
    }
}
