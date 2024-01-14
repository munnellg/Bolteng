#include "sokoban.h"
#include "core/subsystems/subsystems.h"
#include "core/logging.h"

Sokoban::Sokoban() {}

bool Sokoban::init() {
    // configure logging here if desired
    logging::set_level(logging::Level::debug);

    subsystems::init();

    if (!m_entityManager.createSystems()) {
        return false;
    }

    return true;
}

bool Sokoban::play() {
    subsystems::handle_events();
    m_entityManager.update(10.0);
    subsystems::pause(5000);
    return true;
}

void Sokoban::quit() {
    // release all memory
    subsystems::quit();
}

/*
#include "level.h"
#include "core/entity_manager.h"
#include "util/settings.h"

#include <SDL2/SDL_video.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int quit = 0;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_GLContext glContext;

EntityManager em;

void
clean() {
    if (glContext) { SDL_GL_DeleteContext(glContext); }
    if (renderer)  { SDL_DestroyRenderer(renderer); }
    if (window)    { SDL_DestroyWindow(window); }
    IMG_Quit();
    SDL_Quit();
}

static void
die(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\n");
    va_end(args);
    clean();
    exit(EXIT_FAILURE);
}

int
start(Settings const &settings) {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 0;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "IMG_Init error: " << IMG_GetError() << std::endl;
        return 0;
    }

    window = SDL_CreateWindow("OpenGL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings.window_width, settings.window_height, settings.window_flags | SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        return 0;
    }
    
    GLuint err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "glewInit error: " << glewGetString(err) << std::endl;
        return 0;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    em.createSystems();

    level_load(0);

    return 1;
}

void
render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    level_render();
    SDL_GL_SwapWindow(window);
}

void
handle_events() {
    static int level_id = 0;
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void
display_render_stats(Uint64 current) {
    static Uint64 last_frame = 0;
    static Uint64 frames[100] = {0};
    static Uint64 perf_count_freq = SDL_GetPerformanceFrequency();
    static int p = 0;

    char buf[256] = {0};
    Uint64 sum = 0, min = frames[0], max = frames[0];

    frames[p] = perf_count_freq / std::max(1ul, (current - last_frame));
    last_frame  = current;
    p = (p + 1) % 100;

    for (int i = 0; i < 100; i++) {
        sum += frames[i];
        min = std::min(min, frames[i]);
        max = std::max(max, frames[i]);
    }

    sprintf(buf, "Sokoban - avg: %ld - min: %ld - max: %ld", sum / 100, min, max);
    // display_title(buf);
}

void
play() {
    while (!quit) {
        handle_events();
        em.update(10.0f);
        render();
        display_render_stats(SDL_GetPerformanceCounter());
    }
}

int
main() {
    Settings settings;
    load_settings(settings);

    if (!start(settings)) {
        clean();
        return EXIT_FAILURE;
    }

    play();

    clean();

    return EXIT_SUCCESS;
}
*/
