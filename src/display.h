#ifndef CKOBAN_DISPLAY_H
#define CKOBAN_DISPLAY_H

#include "settings.h"
#include <SDL2/SDL.h>

#define ERROR_CREATE_WINDOW             1
#define ERROR_CREATE_RENDERER           2
#define ERROR_SET_RENDERER_LOGICAL_SIZE 3
#define ERROR_CREATE_TEXTURE            4
#define ERROR_TEXTURE_LOCK              5
#define ERROR_TEXTURE_COPY              6
#define ERROR_CLEAR_SCREEN              7

void display_title(char *title);

SDL_Texture *display_texturize(SDL_Surface *surface);
SDL_Renderer *get_renderer();

int display_init(struct Settings const &settings);
int display_refresh();
void display_quit();

#endif
