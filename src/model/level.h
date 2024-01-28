#ifndef LEVEL_H
#define LEVEL_H

#include <array>
#include <istream>
#include <ostream>
#include <vector>

int const TILE_SIZE     = 64;
int const MASK_BOX      = 0x1;
int const MASK_TARGET   = 0x2;
int const MASK_WALL     = 0x4;
int const BOX_ON_TARGET = MASK_BOX | MASK_TARGET;
int const MASK_OCCUPIED = MASK_BOX | MASK_WALL;

struct Level {
    Level() noexcept;

    size_t width;
    size_t height;
    int player_start_x;
    int player_start_y;
    std::vector<int> tiles;

    int tile_at(size_t x, size_t y);
    size_t num_levels();
    friend std::ostream& operator<< (std::ostream& stream, Level const &level);
    friend std::istream& operator>> (std::istream& stream, Level &level);
};

extern Level level_load(size_t level_id);

#endif // LEVEL_H
