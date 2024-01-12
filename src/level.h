#ifndef LEVEL_H
#define LEVEL_H

#include <istream>
#include <ostream>
#include <vector>

int const TILE_SIZE     = 64;
int const MASK_BOX      = 0x1;
int const MASK_TARGET   = 0x2;
int const MASK_WALL     = 0x4;
int const BOX_ON_TARGET = MASK_BOX | MASK_TARGET;
int const MASK_OCCUPIED = MASK_BOX | MASK_WALL;

class Level {
public:
    Level() noexcept;
    
    bool is_occupied(size_t x, size_t y);
    bool contains_box(size_t x, size_t y);

    void render();
    int get_tile_at(int x, int y);    
    friend std::ostream& operator<< (std::ostream& stream, Level const &level);
    friend std::istream& operator>> (std::istream& stream, Level &level);

    size_t width;
    size_t height;
    size_t player_start_x;
    size_t player_start_y;
    std::vector<int> tiles;
};

extern void level_render();
extern void load_level(int level_id);
extern Level *get_level();
#endif // LEVEL_H
