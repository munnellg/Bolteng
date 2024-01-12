#ifndef ASSETS_H
#define ASSETS_H

#include "settings.h"
#include <string>
#include <SDL2/SDL.h>
#include <vector>

extern int const TEXTURE_TILE_WIDTH;
extern int const TEXTURE_TILE_HEIGHT;

extern int const SURFACE_LOAD_FAILED;

int assets_init(struct Settings const &settings);
void assets_quit();

class TileMap {
    public:
        TileMap();
        TileMap(SDL_Texture*texture, std::vector<SDL_Rect> tiles);
        TileMap(TileMap &&tile_map);
        TileMap& operator=(TileMap&&);       // Move assignment operator

        ~TileMap();

        static TileMap build(std::filesystem::path fname, int tile_width, int tile_height); 

        void render(SDL_Renderer *renderer, int id, int x, int y, int w, int h);

    private:
        SDL_Texture *texture;
        std::vector<SDL_Rect> tiles;
};

TileMap *get_tilemap();

#endif // ASSETS_H
