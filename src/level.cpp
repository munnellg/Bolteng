#include "level.h"
#include "assets.h"
#include "display.h"
#include "levels.h"

#include <array>
#include <sstream>
#include <vector>
#include <iostream>

static Level level;

Level::Level() noexcept {
    width = 0;
    height = 0;
}

bool 
Level::is_occupied(size_t x, size_t y) {
    if (x >= this->width || y >= this->height) {
        return false;
    }

    return (this->tiles[x + y * this->width] & MASK_OCCUPIED) != 0;
}

bool 
Level::contains_box(size_t x, size_t y) {
    if (x >= this->width || y >= this->height) {
        return false;
    }

    return (this->tiles[x + y * this->width] & MASK_BOX) != 0;
}

void
load_level(int level_id) {
    if (level_id > serialized_levels.size()) {
        return;
    }

    std::istringstream iss(serialized_levels[level_id]);
    iss >> level;
}

int
Level::get_tile_at(int x, int y) {
    if (x < 0 || y < 0 || x >= width * TILE_SIZE || y >= height * TILE_SIZE) {
        return 0;
    }

    x /= TILE_SIZE;
    y /= TILE_SIZE;

    return tiles[x + y * width];
}

Level *
get_level() {
    return &level;
}

std::ostream& 
operator<< (std::ostream& os, Level const &level) {
    os << level.width << " " << level.height << std::endl;

    for (size_t i = 0; i < level.tiles.size(); i++) {
        if (i == level.player_start_x + level.player_start_y * level.width) {
            os << "@";
        } else {
            switch (level.tiles[i]) {
                case 0:             os << "_"; break;
                case MASK_WALL:     os << "#"; break;
                case MASK_BOX:      os << "$"; break;
                case MASK_TARGET:   os << "."; break;
                case BOX_ON_TARGET: os << "*"; break;
                default:            os << "!"; break;
            }
        }

        if ((i + 1) % level.width == 0) {
            os << std::endl;
        }
    }

    return os;
}

std::istream& 
operator>> (std::istream& is, Level &level) {
    is >> level.width >> level.height;
    
    level.tiles.clear();
    level.tiles.reserve(level.width * level.height);

    char glyph;
    for (size_t i = 0; i < level.width * level.height; i++) {
        int tile = 0;
        is >> glyph;

        switch (glyph) {
            case '@':
                level.player_start_x = i % level.width;
                level.player_start_y = i / level.width;
            case '_': break;
            case '$': tile |= MASK_BOX; break;
            case '#': tile |= MASK_WALL; break;
            case '.': tile |= MASK_TARGET; break;
            case '*': tile |= MASK_BOX | MASK_TARGET; break;
            default: break;
        }

        level.tiles.push_back(tile);
    }

    return is;
}

