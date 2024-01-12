#include "assets.h"
#include "display.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <iostream>
#include <filesystem>

int const TEXTURE_TILE_WIDTH  = 128;
int const TEXTURE_TILE_HEIGHT = 128;

int const SURFACE_LOAD_FAILED = 1;

TileMap tilemap;

int
assets_init(struct Settings const &settings) {
    tilemap = TileMap::build(settings.textures, TEXTURE_TILE_WIDTH, TEXTURE_TILE_HEIGHT);
    return 0;
}

TileMap *
get_tilemap() {
    return &tilemap;
}

void
assets_quit() {
}

TileMap::TileMap() {
   this->texture = nullptr;
}

TileMap::TileMap(SDL_Texture *texture, std::vector<SDL_Rect> tiles) {
    this->texture = texture;
    this->tiles   = tiles;
}


TileMap::TileMap(TileMap&& tile_map) : texture(std::move(tile_map.texture)), tiles(std::move(tile_map.tiles)) {
    tile_map.texture = nullptr;
}


TileMap::~TileMap() {
    if (this->texture) { SDL_DestroyTexture(this->texture); }
}

TileMap& 
TileMap::operator=(TileMap&& tile_map) {
    texture = std::move(tile_map.texture);
    tiles   = std::move(tile_map.tiles);
    tile_map.texture = nullptr;
    return *this;
}

void 
TileMap::render(SDL_Renderer *renderer, int id, int x, int y, int w, int h) {
    SDL_Rect dst = { .x = x, .y = y, .w = w, .h = h };
    if (SDL_RenderCopy(renderer, texture, &tiles[id], &dst)) {
        std::cout << SDL_GetError() << std::endl;
    }
}

TileMap 
TileMap::build(std::filesystem::path path, int tile_width, int tile_height) {
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface) {
        std::cout << SDL_GetError() << std::endl;
        throw SURFACE_LOAD_FAILED;
    }

    int num_horizontal_textures = surface->w / TEXTURE_TILE_WIDTH;
    int num_vertical_textures = surface->h / TEXTURE_TILE_HEIGHT;
    // TODO(gary): generate a warning if the above division yields a remainder.
    // It means that the tile dimensions do not match our expectations
    
    std::vector<SDL_Rect> tiles;
    int num_textures = num_horizontal_textures * num_vertical_textures;
    tiles.reserve(num_textures);
    
    for (int i = 0; i < num_textures; i++) {
        int x = (i * tile_width) % surface->w;
        int y = ((i * tile_width) / surface->w) * tile_height;
        tiles.push_back({ .x = x, .y = y, .w = tile_width, .h = tile_height });
    }

    SDL_Texture *texture = display_texturize(surface);

    SDL_FreeSurface(surface);

    return TileMap(texture, tiles);
}
