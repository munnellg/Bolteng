#include "assets.h"
#include "camera.h"
#include "audio.h"
#include "settings.h"
#include "display.h"
#include "level.h"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define FRAMES_PER_SECOND      60
#define MS_PER_FRAME           (1000 / FRAMES_PER_SECOND)

#define MAX(x, y) (((x) > (y))? (x) : (y))
#define MIN(x, y) (((x) < (y))? (x) : (y))

struct state {
    int quit;
} state;

static SDL_GameController *controller;

static Camera camera;

void
clean() {
    assets_quit();
    display_quit();
    audio_quit();
    if (controller) { SDL_GameControllerClose(controller); }
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

void
start(struct Settings const &settings) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        die("%s", SDL_GetError());
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        die("%s", IMG_GetError());
    }

    if (display_init(settings)) {
        die("%s", SDL_GetError());
    }
    
    if (audio_init(settings)) {
        die("%s", SDL_GetError());
    }

    if (assets_init(settings)) {
        die("%s", SDL_GetError());
    }

    if (SDL_NumJoysticks() > 0){
        controller = SDL_GameControllerOpen(0); 
    }

    load_level(0);
}

void
render() {
    int screen_width, screen_height;
    SDL_Renderer *renderer = get_renderer();
    Level *level = get_level();
    TileMap *tilemap = get_tilemap();

    std::cout << camera << std::endl;

    if (SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height) != 0) {
        std::cout << SDL_GetError() << std::endl;
    }

    int camera_x1 = (camera.x / TILE_SIZE) * TILE_SIZE;
    int camera_y1 = (camera.y / TILE_SIZE) * TILE_SIZE;
    int camera_x2 = ((camera.x + camera.w) / TILE_SIZE) * TILE_SIZE;
    int camera_y2 = ((camera.y + camera.h) / TILE_SIZE) * TILE_SIZE;

    int offset_x = camera_x1 - camera.x;
    int offset_y = camera_y1 - camera.y;

    int screen_tile_size = TILE_SIZE / camera.zoom;

    for (int world_y = camera_y1; world_y < camera_y2; world_y += TILE_SIZE) {
        for (int world_x = camera_x1; world_x < camera_x2; world_x += TILE_SIZE) {
            int screen_x = (world_x - camera_x1 + offset_x) / camera.zoom;
            int screen_y = (world_y - camera_y1 + offset_y) / camera.zoom;

            tilemap->render(renderer, 88, screen_x, screen_y, screen_tile_size, screen_tile_size); 

            switch (level->get_tile_at(world_x, world_y)) { 
                case 0: 
                    break;
                case MASK_WALL:
                    tilemap->render(renderer, 84, screen_x, screen_y, screen_tile_size, screen_tile_size);
                    break;
                case MASK_BOX:
                    tilemap->render(renderer, 1, screen_x, screen_y, screen_tile_size, screen_tile_size);
                    break;
                case MASK_TARGET: 
                    tilemap->render(renderer, 39, screen_x, screen_y, screen_tile_size, screen_tile_size);
                    break;
                case BOX_ON_TARGET: 
                    tilemap->render(renderer, 1, screen_x, screen_y, screen_tile_size, screen_tile_size);
                    tilemap->render(renderer, 39, screen_x, screen_y, screen_tile_size, screen_tile_size);
                    break;
                default: break;
            }
        }
    }

    display_refresh();
}

void
handle_events() {
    static int level_id = 0;
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                state.quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        state.quit = 1;
                        break;
                    case SDLK_w:
                        camera.y-=8;
                        break;
                    case SDLK_s:
                        camera.y+=8;
                        break;
                    case SDLK_a:
                        camera.x-=8;
                        break;
                    case SDLK_d:
                        camera.x+=8;
                        break;
                    case SDLK_DOWN:
                        level_id--;
                        if (level_id < 0) {
                            level_id = 0;
                        }
                        load_level(level_id);
                        break;
                    case SDLK_UP:

                        level_id++;
                        if (level_id > 59) {
                            level_id = 59;
                        }
                        load_level(level_id);
                        break;
                }
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                printf("Down: %s\n", SDL_GameControllerGetStringForButton((SDL_GameControllerButton) e.cbutton.button));
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

    frames[p] = perf_count_freq / MAX(1, (current - last_frame));
    last_frame  = current;
    p = (p + 1) % 100;

    for (int i = 0; i < 100; i++) {
        sum += frames[i];
        min = MIN(min, frames[i]);
        max = MAX(max, frames[i]);
    }

    sprintf(buf, "Sokoban - avg: %ld - min: %ld - max: %ld", sum / 100, min, max);
    display_title(buf);
}

void
play() {
    while (!state.quit) {
        Uint64 start = SDL_GetTicks();
        handle_events();
        render();
        display_render_stats(SDL_GetPerformanceCounter());
        Sint64 delay = MS_PER_FRAME - (SDL_GetTicks() - start);
        SDL_Delay(MAX(delay, 0));
    }
}

int
main() {
    struct Settings settings;
    load_settings(settings);

    start(settings);

    play();

    clean();

    return EXIT_SUCCESS;
}
