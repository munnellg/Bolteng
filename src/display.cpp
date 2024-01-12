#include "display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>

static SDL_Window   *window;
static SDL_Renderer *renderer;

void
display_title(char *title) {
    SDL_SetWindowTitle(window, title);
}

SDL_Renderer *
get_renderer() {
    return renderer;
}

void
display_quit() {
    if (renderer) { SDL_DestroyRenderer(renderer); }
    if (window)   { SDL_DestroyWindow(window); }
}

int
display_init(struct Settings const &settings) {
    window = SDL_CreateWindow(
        "Sokoban",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        settings.window_width,
        settings.window_height,
        settings.window_flags
    );

    if (!window) {
        return ERROR_CREATE_WINDOW;
    }

    renderer = SDL_CreateRenderer(window, -1, settings.renderer_flags);

    if (!renderer) {
        return ERROR_CREATE_RENDERER;
    }

    return 0;
}

SDL_Texture *
display_texturize(SDL_Surface *surface) {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture) {
        std::cout << SDL_GetError() << std::endl;
    }

    // TODO(gary): Do error checking to make sure texture was allocated correctly
    return texture;
}

int
display_refresh() {
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    return 0;
}


