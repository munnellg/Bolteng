#include "level.h"

#include <array>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../engine/core/logging.h"

Level::Level() noexcept {
    width = 0;
    height = 0;
}

int
Level::tile_at(size_t x, size_t y) {
    size_t i = x + y * width;
    return tiles[i];
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

std::array<std::string, 60> const serialized_levels = {
    "22 11 "
    "____#####_____________"
    "____#___#_____________"
    "____#$__#_____________"
    "__###__$###___________"
    "__#__$__$_#___________"
    "###_#_###_#_____######"
    "#___#_###_#######__..#"
    "#_$__$_____________..#"
    "#####_####_#@####__..#"
    "____#______###__######"
    "____########__________",

    "14 10 "
    "############__"
    "#..__#_____###"
    "#..__#_$__$__#"
    "#..__#$####__#"
    "#..____@_##__#"
    "#..__#_#__$_##"
    "######_##$_$_#"
    "__#_$__$_$_$_#"
    "__#____#_____#"
    "__############",

    "17 10 "
    "________########_"
    "________#_____@#_"
    "________#_$#$_##_"
    "________#_$__$#__"
    "________##$_$_#__"
    "#########_$_#_###"
    "#....__##_$__$__#"
    "##...____$__$___#"
    "#....__##########"
    "########_________",

    "22 13 "
    "______________########"
    "______________#__....#"
    "___############__....#"
    "___#____#__$_$___....#"
    "___#_$$$#$__$_#__....#"
    "___#__$_____$_#__....#"
    "___#_$$_#$_$_$########"
    "####__$_#_____#_______"
    "#___#_#########_______"
    "#____$__##____________"
    "#_$$#$$_@#____________"
    "#___#___##____________"
    "#########_____________",

    "17 13 "
    "________#####____"
    "________#___#####"
    "________#_#$##__#"
    "________#_____$_#"
    "#########_###___#"
    "#....__##_$__$###"
    "#....____$_$$_##_"
    "#....__##$__$_@#_"
    "#########__$__##_"
    "________#_$_$__#_"
    "________###_##_#_"
    "__________#____#_"
    "__________######_",

    "12 11 "
    "######__###_"
    "#..__#_##@##"
    "#..__###___#"
    "#.._____$$_#"
    "#..__#_#_$_#"
    "#..###_#_$_#"
    "####_$_#$__#"
    "___#__$#_$_#"
    "___#_$__$__#"
    "___#__##___#"
    "___#########",

    "13 12 "
    "_______#####_"
    "_#######___##"
    "##_#_@##_$$_#"
    "#____$______#"
    "#__$__###___#"
    "###_#####$###"
    "#_$__###_..#_"
    "#_$_$_$_...#_"
    "#____###...#_"
    "#_$$_#_#...#_"
    "#__###_#####_"
    "####_________",

    "16 17 "
    "__####__________"
    "__#__###########"
    "__#____$___$_$_#"
    "__#_$#_$_#__$__#"
    "__#__$_$__#____#"
    "###_$#_#__####_#"
    "#@#$_$_$__##___#"
    "#____$_#$#___#_#"
    "##__$____$_$_$_#"
    "_####__#########"
    "__###__###______"
    "__#______#______"
    "__#______#______"
    "__#......#______"
    "__#......#______"
    "__#......#______"
    "__########______",
    
    "17 18 "
    "__________#######"
    "__________#__...#"
    "______#####__...#"
    "______#______...#"
    "______#__##__...#"
    "______##_##__...#"
    "_____###_########"
    "_____#_$$$_##____"
    "_#####__$_$_#####"
    "##___#$_$___#___#"
    "#@_$__$____$__$_#"
    "######_$$_$_#####"
    "_____#_$____#____"
    "_____####_###____"
    "________#__#_____"
    "________#__#_____"
    "________#__#_____"
    "________####_____",

    "21 20 "
    "______________####___"
    "_________######__#___"
    "_________#_______#___"
    "_________#__####_###_"
    "_###__#####_###____#_"
    "##@####___$$$_#____#_"
    "#_$$___$$_$___#....##"
    "#__$$$#____$__#.....#"
    "#_$___#_$$_$$_#.....#"
    "###___#__$____#.....#"
    "__#___#_$_$_$_#.....#"
    "__#_#######_###.....#"
    "__#___#__$_$__#.....#"
    "__###_#_$$_$_$#######"
    "____#_#__$______#____"
    "____#_#_$$$_$$$_#____"
    "____#_#_______#_#____"
    "____#_#########_#____"
    "____#___________#____"
    "____#############____",

    "19 15 "
    "__________####_____"
    "_____####_#__#_____"
    "___###__###$_#_____"
    "__##___@__$__#_____"
    "_##__$_$$##_##_____"
    "_#__#$##_____#_____"
    "_#_#_$_$$_#_###____"
    "_#___$_#__#_$_#####"
    "####____#__$$_#___#"
    "####_##_$_________#"
    "#.____###__########"
    "#.._..#_####_______"
    "#...#.#____________"
    "#.....#____________"
    "#######____________",

    "13 16 "
    "__#########__"
    "__#*.*#*.*#__"
    "__#.*.*.*.#__"
    "__#*.*.*.*#__"
    "__#.*.*.*.#__"
    "__#*.*.*.*#__"
    "__###___###__"
    "____#___#____"
    "######_######"
    "#___________#"
    "#_$_$_$_$_$_#"
    "##_$_$_$_$_##"
    "_#$_$_$_$_$#_"
    "_#___$@$___#_"
    "_#__#####__#_"
    "_####___####_",

    "20 13 "
    "____#########_______"
    "__###___##__#####___"
    "###______#__#___####"
    "#__$$_#$_#__#__..._#"
    "#_#__$#@$##_#_#.#._#"
    "#__##_#$__#____..._#"
    "#_$#____$_#_#_#.#._#"
    "#____##__##$_$_..._#"
    "#_$_##___#__#$#.#._#"
    "##_$$__$___$__$..._#"
    "_#$__######____##__#"
    "_#___#____##########"
    "_#####______________",

    "17 13 "
    "################_"
    "#______________#_"
    "#_#_######_____#_"
    "#_#__$_$_$_$#__#_"
    "#_#___$@$___##_##"
    "#_#_#$_$_$###...#"
    "#_#___$_$__##...#"
    "#_###$$$_$_##...#"
    "#_____#_##_##...#"
    "#####___##_##...#"
    "____#####_____###"
    "________#_____#__"
    "________#######__",

    "17 17 "
    "_______####______"
    "____####__#______"
    "___##__#__#______"
    "___#__$_$_#______"
    "_###_#$___####___"
    "_#__$__##$___#___"
    "_#__#_@_$_#_$#___"
    "_#__#______$_####"
    "_##_####$##_____#"
    "_#_$#.....#_#___#"
    "_#__$...*._$#_###"
    "##__#.....#___#__"
    "#___###_#######__"
    "#_$$__#__#_______"
    "#__#_____#_______"
    "######___#_______"
    "_____#####_______",

    "14 15 "
    "#####_________"
    "#___##________"
    "#____#__####__"
    "#_$__####__#__"
    "#__$$_$___$#__"
    "###@_#$____##_"
    "_#__##__$_$_##"
    "_#_$__##_##_.#"
    "_#__#$##$__#.#"
    "_###___$..##.#"
    "__#____#.*...#"
    "__#_$$_#.....#"
    "__#__#########"
    "__#__#________"
    "__####________",
    
    "18 16 "
    "_______#######____"
    "_#######_____#____"
    "_#_____#_$@$_#____"
    "_#$$_#___#########"
    "_#_###......##___#"
    "_#___$......##_#_#"
    "_#_###......_____#"
    "##___####_###_#$##"
    "#__#$___#__$__#_#_"
    "#__$_$$$__#_$##_#_"
    "#___$_$_###$$_#_#_"
    "#####_____$___#_#_"
    "____###_###___#_#_"
    "______#_____#___#_"
    "______########__#_"
    "_____________####_",
    
    "22 13 "
    "______############____"
    "______#__.__##___#____"
    "______#_#._____@_#____"
    "_######_##...#_####___"
    "##__##...####_____####"
    "#_$_##...____$_#__$__#"
    "#_____.._##_#_##_##__#"
    "####$###$#_$__#___#_##"
    "_###__#____##$_$$_#_#_"
    "_#___$$_#_#_$_#_$##_#_"
    "_#__________________#_"
    "_#################__#_"
    "_________________####_",

    "28 20 "
    "________######______________"
    "________#___@####___________"
    "______#####_$___#___________"
    "______#___##____####________"
    "______#_$##__##____#________"
    "______#___#__#####_#________"
    "______#_#$$_$____#_#________"
    "______#__$_$_###_#_#________"
    "______#_#___$__#_#_#________"
    "______#_#__#$#___#_#________"
    "_____##_####___#_#_#________"
    "_____#__$__#####_#_#_####___"
    "____##____$_____$__###__####"
    "#####__###_$_$#_$_#___.....#"
    "#_____##______#__##__#.....#"
    "#_$$$$____######$##___#.##.#"
    "##____##______________#....#"
    "_##__###############___....#"
    "__#__#_____________#####__##"
    "__####_________________####_",

    "20 20 "
    "_______############_"
    "_______#..........#_"
    "_____###.#.#.#.#..#_"
    "_____#___.........#_"
    "_____#@_$_$_$_*.*.#_"
    "____#######_#######_"
    "_####___#____##__#__"
    "##____$_#____#_$_##_"
    "#__#$#_###_###$___##"
    "#_$__$_$___#_$_$_$_#"
    "#__#_$_##_______#$_#"
    "#___$####$####$##__#"
    "####__##___#____#__#"
    "___#$_##___#_#_$$__#"
    "___#___#_$_#__$____#"
    "___###_#_$$_#__$_###"
    "_____#_#____#_$_##__"
    "_____#_########_#___"
    "_____#__________#___"
    "_____############___",

    "16 14 "
    "___##########___"
    "___#..__#___#___"
    "___#..______#___"
    "___#..__#__####_"
    "__#######__#__##"
    "__#____________#"
    "__#__#__##__#__#"
    "####_##__####_##"
    "#__$__#####_#__#"
    "#_#_$__$__#_$__#"
    "#_@$__$___#___##"
    "####_##_#######_"
    "___#____#_______"
    "___######_______",

    "22 20 "
    "____________####______"
    "_############__#####__"
    "_#____#__#__$__#___##_"
    "_#_$_$_$__$_#_$_$___#_"
    "_##$_$___#_@#_$___$_#_"
    "###___############_##_"
    "#__$_$#__#......#_$#__"
    "#_#___#__#......##_#__"
    "#__##_##_#_.....#__#__"
    "#_#______$......_$_#__"
    "#_#_$_##_#......#__#__"
    "#__$_$#__#......#_$#__"
    "#_$___#__##$#####__#__"
    "#_$_$_####_$_$__$_$#__"
    "##_#_____$_$_$_$___###"
    "_#__######_$____$____#"
    "_#_________#_#######_#"
    "_#######_#$__________#"
    "_______#___###########"
    "_______#####__________",

    "25 14 "
    "_______#######___________"
    "_______#__#__####________"
    "_______#_$#$_#__##_______"
    "########__#__#___########"
    "#....__#_$#$_#__$#__#___#"
    "#....#_#_____#$__#______#"
    "#..#.____$#__#_$____#$__#"
    "#..._@##__#$_#$__#__#___#"
    "#...._##_$#_____$########"
    "########__#$$#$__#_______"
    "_______#_$#__#__$#_______"
    "_______#__#__#___#_______"
    "_______####__#####_______"
    "__________####___________",

    "21 19 "
    "___##########________"
    "___#........####_____"
    "___#.#.#....#__#_____"
    "___#........$$_#_____"
    "___#_____.###__####__"
    "_#########__$_#___#__"
    "_#_____$___$_$__$_#__"
    "_#__#____#__$_$#__#__"
    "_##_#####___#__#__#__"
    "_#_$_____#___####_#__"
    "##__$#___#_##__#__#__"
    "#____##$###____#__##_"
    "#_$____$_#__#__#___#_"
    "#####____#_##_#_##_##"
    "____#$#_#__$__$_$___#"
    "____#@#__$#$$$__#___#"
    "____###__$______#####"
    "______##__#__#__#____"
    "_______##########____",

    "23 17 "
    "_______________####____"
    "__________######__#####"
    "____#######_______#___#"
    "____#______$_$_##_#_#_#"
    "____#__####_$__#_____.#"
    "____#______$_#_#_##.#.#"
    "____##$####$_$_$_##.#.#"
    "____#_____#____####.###"
    "____#_$___######__#.#.#"
    "######$$$##______@#.#.#"
    "#______#____#$#$###._.#"
    "#_####_#$$$$$____#_...#"
    "#_#____$_____#___#_...#"
    "#_#___##_##_____###...#"
    "#_######$######__######"
    "#________#____#__#_____"
    "##########____####_____",

    "15 15 "
    "#########______"
    "#_______#______"
    "#_______####___"
    "##_####_#__#___"
    "##_#@##____#___"
    "#_$$$_$__$$#___"
    "#__#_##_$__#___"
    "#__#_##__$_####"
    "####__$$$_$#__#"
    "_#___##___....#"
    "_#_#___#_#.._.#"
    "_#___#_#_##...#"
    "_#####_$__#...#"
    "_____##___#####"
    "______#####____",

    "23 13 "
    "_#################_____"
    "_#...___#____#___###___"
    "##.....__$##_#_#_$_#___"
    "#......#__$__#__$__#___"
    "#......#__#__#_#_#_##__"
    "#########_$__$_#_#__###"
    "__#_____#$##$_##_##___#"
    "_##___$____#_$__$___#_#"
    "_#__##_###_#__#####$#_#"
    "_#_$_$$_____$___$_____#"
    "_#_$____$##$_########_#"
    "_#######__@_##______###"
    "_______######__________",

    "15 17 "
    "_____#######___"
    "_____#@_#__#___"
    "_____#_$___#___"
    "____###_##_#___"
    "_####_$__#_##__"
    "_#_______#__##_"
    "_#_$_$####_$_#_"
    "_#_$$_#__#__$#_"
    "_#$__$___#$__#_"
    "##__$$#___$$_##"
    "#_$$__#__#__$_#"
    "#_____####_$__#"
    "#__#$##..##___#"
    "###_.#....#####"
    "__#_.......##__"
    "__#....___..#__"
    "__###########__",

    "24 11 "
    "________________#####___"
    "_______######_###___####"
    "___#####____###_$_$__$_#"
    "####__##_#$_$____$_#___#"
    "#....___$$_$_$__$___#$##"
    "#.._#_##_#___###$##_#__#"
    "#....____#_###____#____#"
    "#....____#_##__$__###$_#"
    "#..######__$__#__####_##"
    "####____#___###____@__#_"
    "________###############_",

    "14 20 "
    "_#####________"
    "_#___#######__"
    "_#_$_###___#__"
    "_#_$____$$_#__"
    "_##_####___#__"
    "###_#__#_###__"
    "#___#__#@##___"
    "#_$$____$_#___"
    "#___#_#_$_####"
    "#####_#___#__#"
    "_#___$####___#"
    "_#__$_____$__#"
    "_##___#####_##"
    "_##########__#"
    "##....#_$__$_#"
    "#.....#_$$#__#"
    "#.._..#_$__$_#"
    "#.....$___#__#"
    "##__##########"
    "_####_________",

    "15 12 "
    "_#######_______"
    "_#__#__#####___"
    "##__#__#...###_"
    "#__$#__#...__#_"
    "#_$_#$$_...__#_"
    "#__$#__#..._.#_"
    "#___#_$########"
    "##$_______$_$_#"
    "##__#__$$_#___#"
    "_######__##$$@#"
    "______#______##"
    "______########_",

    "18 16 "
    "__####____________"
    "__#__#########____"
    "_##__##_@#___#____"
    "_#__$#_$_$___####_"
    "_#$__$__#_$_$#__##"
    "##__$##_#$_$_____#"
    "#__#__#_#___$$$__#"
    "#_$____$__$##_####"
    "#_$_$_#$#__#__#___"
    "##__###__###$_#___"
    "_#__#...._____#___"
    "_####......####___"
    "___#....####______"
    "___#...##_________"
    "___#...#__________"
    "___#####__________",

    "13 15 "
    "______####___"
    "__#####__#___"
    "_##_____$#___"
    "##_$__##_###_"
    "#@$_$_#_$__#_"
    "####_##___$#_"
    "_#....#$_$_#_"
    "_#....#___$#_"
    "_#....__$$_##"
    "_#..._#_$___#"
    "_######$_$__#"
    "______#___###"
    "______#$_###_"
    "______#__#___"
    "______####___",

    "12 15 "
    "############"
    "##_____##__#"
    "##___$___$_#"
    "####_##_$$_#"
    "#___$_#____#"
    "#_$$$_#_####"
    "#___#_#_$_##"
    "#__#__#__$_#"
    "#_$#_$#____#"
    "#___..#_####"
    "####.._$_#@#"
    "#.....#_$#_#"
    "##....#__$_#"
    "###..##____#"
    "############",

    "20 16 "
    "############__######"
    "#___#____#@####....#"
    "#___$$#_______.....#"
    "#___#_###___##_....#"
    "##_##_###__#___....#"
    "_#_$_$_____#_##_####"
    "_#__$_$##__#_______#"
    "####_#__####_##_##_#"
    "#__#_#$___##_##____#"
    "#_$__$__#_##_#######"
    "#_#_$_$____#_#______"
    "#__$_##_##_#_#______"
    "#_$$_____$$__#______"
    "##_##_###_$__#______"
    "_#____#_#____#______"
    "_######_######______",

    "18 19 "
    "_____####_________"
    "___###__##________"
    "####__$__#________"
    "#___$_$__####_____"
    "#_$___#_$___#_####"
    "#__#__#___$_#_#..#"
    "##$#$_####$####..#"
    "_#___#####_##_...#"
    "_#$#_##@##_##__..#"
    "_#_#____$_____...#"
    "_#___####_###__..#"
    "_###_##_#__##_...#"
    "__##$_####$_###..#"
    "__#___##____#_#..#"
    "_##_$$##__$_#_####"
    "_#_____$$$$_#_____"
    "_#_$_###____#_____"
    "_#___#_######_____"
    "_#####____________",

    "21 15 "
    "###########__________"
    "#......___#########__"
    "#......___#__##___#__"
    "#..###_$____$_____#__"
    "#..._$_$_#__###___#__"
    "#...#$#####____#__#__"
    "###____#___#$__#_$###"
    "__#__$$_$_$__$##__$_#"
    "__#__$___#$#__##____#"
    "__###_##_#__$_#######"
    "___#__$_$_##_##______"
    "___#____$__$__#______"
    "___##___#_#___#______"
    "____#####@#####______"
    "________###__________",

    "14 15 "
    "_#########____"
    "_#....___##___"
    "_#.#.#__$_##__"
    "##....#_#_@##_"
    "#_....#__#__##"
    "#_____#$_##$_#"
    "##_###__$____#"
    "_#$__$_$_$#__#"
    "_#_#__$_$_##_#"
    "_#__###__##__#"
    "_#____##_##_##"
    "_#__$_#__$__#_"
    "_###$_$___###_"
    "___#__#####___"
    "___####_______",

    "23 18 "
    "______________###______"
    "_____________##.###____"
    "_____________#....#____"
    "_#############....#____"
    "##___##_____##....#####"
    "#__$$##__$_@##....____#"
    "#______$$_$#__....#___#"
    "#__$_##_$$_#_#....#__##"
    "#__$_##_$__#_##_###__#_"
    "##_#####_###_________#_"
    "##___$__$_#####_###__#_"
    "#_$###__#_#####_#_####_"
    "#___$___#_______#______"
    "#__$_#$_$_$###__#______"
    "#_$$$#_$___#_####______"
    "#____#__$$_#___________"
    "######___###___________"
    "_____#####_____________",

    "11 11 "
    "______####_"
    "#######_@#_"
    "#_____$__#_"
    "#___$##_$#_"
    "##$#...#_#_"
    "_#_$...__#_"
    "_#_#._.#_##"
    "_#___#_#$_#"
    "_#$__$____#"
    "_#__#######"
    "_####______",

    "20 15 "
    "___________#####____"
    "__________##___##___"
    "_________##_____#___"
    "________##__$$__#___"
    "_______##_$$__$_#___"
    "_______#_$____$_#___"
    "####___#___$$_#####_"
    "#__########_##____#_"
    "#..___________$$$@#_"
    "#.#_#######_##___##_"
    "#.#_#######._#$_$###"
    "#..........._#___$_#"
    "##############__$__#"
    "_____________##__###"
    "______________####__",

    "13 18 "
    "_########____"
    "_#@##___####_"
    "_#_$___$___#_"
    "_#__$_$_$$$#_"
    "_#_$$#_#___#_"
    "##$____$___#_"
    "#__$__$$$$$##"
    "#_$####_#___#"
    "#__$....#___#"
    "#_##....#$$_#"
    "#_##....___##"
    "#___....#__#_"
    "##_#....#$$#_"
    "_#_#....#__#_"
    "_#_________#_"
    "_####_##$###_"
    "____#____#___"
    "____######___",

    "17 16 "
    "____############_"
    "____#__________##"
    "____#__#_#$$_$__#"
    "____#$_#$#__##_@#"
    "___##_##_#_$_#_##"
    "___#___$_#$__#_#_"
    "___#___#_$___#_#_"
    "___##_$_$___##_#_"
    "___#__#__##__$_#_"
    "___#____##_$$#_#_"
    "######$$___#___#_"
    "#....#__########_"
    "#.#..._##________"
    "#....___#________"
    "#....___#________"
    "#########________",

    "25 19 "
    "______######_____________"
    "___#####___#_____________"
    "___#___#_#_#####_________"
    "___#_$_#__$____######____"
    "__##$__###_##_______#____"
    "###__$$_$_$_#__##___#####"
    "#_______$___######_##___#"
    "#__########_#@___#_#__#_#"
    "##_###______####_#$#_#__#"
    "_#_###_####_##.._#___$_##"
    "_#__$__$__#$##.._#$##__##"
    "_#__#_#_#_____..##_##_$_#"
    "_####___#_##_#..#____$__#"
    "____#####____#..#_#_#__##"
    "________######..#___#_##_"
    "_____________#..#####__#_"
    "_____________#.._______#_"
    "_____________##__###__##_"
    "______________#########__",

    "19 11 "
    "________#######____"
    "____#####__#__####_"
    "____#___#___$____#_"
    "_####_#$$_##_##__#_"
    "##______#_#__##_###"
    "#__###_$#$__$__$__#"
    "#...____#_##__#___#"
    "#...#____@_#_###_##"
    "#...#__###__$__$__#"
    "########_##___#___#"
    "__________#########",

    "22 17 "
    "____#########__####___"
    "____#___##__####__#___"
    "____#___$___#__$__#___"
    "____#__#_##_#_____####"
    "____##_$___$_$$#_#___#"
    "____####__#__#_$_$___#"
    "#####__####____###...#"
    "#___#$_#__#_####.....#"
    "#______#__#_#_##.....#"
    "######_#__#$___###...#"
    "___#___##_#_$#___#...#"
    "__##_______$__$#_#####"
    "_##_$$$##__#_$___#____"
    "_#___#__#_###__###____"
    "_#___$__#$_@####______"
    "_#####__#___#_________"
    "_____########_________",

    "19 15 "
    "_#####_____________"
    "_#___#_____________"
    "_#_#_######________"
    "_#______$@######___"
    "_#_$_##$_###___#___"
    "_#_####_$____$_#___"
    "_#_#####_#__#$_####"
    "##__####_##$______#"
    "#__$#__$__#_##_##_#"
    "#_________#_#...#_#"
    "######__###__...__#"
    "_____####_#_#...#_#"
    "__________#_###_#_#"
    "__________#_______#"
    "__________#########",

    "16 15 "
    "_______####_____"
    "_______#__##____"
    "_______#___##___"
    "_______#_$$_##__"
    "_____###$__$_##_"
    "__####____$___#_"
    "###__#_#####__#_"
    "#____#_#....$_#_"
    "#_#___$_....#_#_"
    "#__$_#_#.*..#_#_"
    "###__####_###_#_"
    "__####_@$__##$##"
    "_____###_$_____#"
    "_______#__##___#"
    "_______#########",

    "19 16 "
    "______############_"
    "_____##..____#___#_"
    "____##..*_$____$_#_"
    "___##..*.#_#_#$_##_"
    "___#..*.#_#_#_$__#_"
    "####...#__#____#_#_"
    "#__##_#__________#_"
    "#_@$_$_###__#_#_##_"
    "#_$___$___#_#___#__"
    "###$$___#_#_#_#_#__"
    "__#___$___#_#_#####"
    "__#_$#_#####______#"
    "__#$___#___#___#__#"
    "__#__###___##_____#"
    "__#__#______#____##"
    "__####______######_",

    "21 16 "
    "_____#############___"
    "_____#____###____#___"
    "_____#_____$_$__####_"
    "___####_#___$_$____#_"
    "__##_$__#$####_$_$_#_"
    "###___#_#___###__$_#_"
    "#_$__$__#__$__#_####_"
    "#_##$####_#$#__$__###"
    "#_##__###_#_#_#__$__#"
    "#____@$___$___#_$_#_#"
    "#####__#__##__#_$#__#"
    "__#..._#####$__#__#_#"
    "__#.......#_$$_#$_#_#"
    "__#.......#_________#"
    "__#.......#######__##"
    "__#########_____####_",

    "16 14 "
    "#####_####______"
    "#...#_#__####___"
    "#...###__$__#___"
    "#....##_$__$###_"
    "##....##___$__#_"
    "###..._##_$_$_#_"
    "#_##____#__$__#_"
    "#__##_#_###_####"
    "#_$_#_#$__$____#"
    "#__$_@_$____$__#"
    "#___#_$_$$_$_###"
    "#__######__###__"
    "#_##____####____"
    "###_____________",

    "21 14 "
    "_####________________"
    "##__#####____________"
    "#_______#_#####______"
    "#_$###__###___#______"
    "#..#__$#_#__#_#______"
    "#..#______$$#_###____"
    "#.*#_#__#$_$____#####"
    "#..#__##_____##$#___#"
    "#.*$__$_#_##__$_____#"
    "#..##__$___#___######"
    "#.*##$##___#####_____"
    "#..__$_#####_________"
    "#__#_@_#_____________"
    "########_____________",

    "13 19 "
    "___##########"
    "___#__###___#"
    "___#_$___$__#"
    "___#__####$##"
    "___##_#__#__#"
    "__##__#.*___#"
    "__#__##..#__#"
    "__#_@_#.*#_##"
    "__#_#$#..#$_#"
    "__#_$_#..#__#"
    "__#_#_#**#__#"
    "__#_$_#..#$##"
    "__#____.*#__#"
    "_###__#__#__#"
    "##____####__#"
    "#__#######$##"
    "#_$______$__#"
    "#__##___#___#"
    "#############",

    "23 20 "
    "_#####################_"
    "_#___##__#___#___#___#_"
    "_#_$_____$___$___$___##"
    "#####_#__#___###_##$###"
    "#___#_##$######___#___#"
    "#_$___#_......#___#_$_#"
    "##_#__#_......#####___#"
    "##_#########..#___#_###"
    "#__________#..#_$___#__"
    "#_##_###_###..##_#__###"
    "#_#___#___##..##_###__#"
    "#___@______$..#_______#"
    "#_#___#___##__#___##__#"
    "#####_##############_##"
    "#__________#___#____$_#"
    "#_$__#_$_$_$___#_#____#"
    "#_#$##_$#__##_##____#_#"
    "#__$_$$_####_$__$_#_#_#"
    "#__________#___#______#"
    "#######################",

    "22 15 "
    "_#####################"
    "##___________________#"
    "#____$_#______##_#___#"
    "#__######_###__#$##_##"
    "##$#___##$#....___#_#_"
    "#__#____$_#....##_#_#_"
    "#_$_#_#_#_#....##___#_"
    "#_$_#$$___#....##$#_#_"
    "#_#_$@$##$#....##___#_"
    "#___$$$___#....#____#_"
    "#__$#___#_######_$###_"
    "##__#_###$$__$___$_#__"
    "##_____#_$__$_##___#__"
    "_#####___#___#######__"
    "_____#########________",

    "14 16 "
    "##########____"
    "#________####_"
    "#_######_#__##"
    "#_#_$_$_$__$_#"
    "#_______#$___#"
    "###$__$$#__###"
    "__#__##_#_$##_"
    "__##$#___$_@#_"
    "___#__$_$_###_"
    "___#_#___$__#_"
    "___#_##___#_#_"
    "__##__#####_#_"
    "__#_________#_"
    "__#.......###_"
    "__#.......#___"
    "__#########___",

    "18 12 "
    "_________####_____"
    "_#########__##____"
    "##__$______$_#####"
    "#___##_##___##...#"
    "#_#$$_$_$$#$##...#"
    "#_#____@__#___...#"
    "#__$#_###$$___...#"
    "#_$__$$__$_##....#"
    "###$_______#######"
    "__#__#######______"
    "__####____________",

    "27 20 "
    "______________######_______"
    "__________#####____#_______"
    "__________#__##_#__#####___"
    "__________#___*.#..#___#___"
    "_#####_####_$#.#...____#___"
    "_#___###__##_#*....##_##___"
    "_#_$______##_#..#..##_#____"
    "######_#___#_#*.#####_#____"
    "#___#_$#$#_#_#..#####_#____"
    "#_$__$_____#_#*.____#_#____"
    "##_##__$_###_#__##__#_#____"
    "_#__$__$_###_#####_##_#____"
    "_###$###$###__####_##_#____"
    "####_#_________###__#_#____"
    "#__$_#__$####__###$$#@#####"
    "#______$_#_#__####__#$#___#"
    "####_#__$#_#______________#"
    "___#__$__#_##__##__########"
    "___##__###__########_______"
    "____####___________________",

    "29 20 "
    "_________####________________"
    "_________#__#________________"
    "_________#__########_________"
    "___#######__#______#_________"
    "___#___#_#_#_#_#___##________"
    "___#_$_____$__##__$_#________"
    "__###_$#_#__#_#_____#########"
    "__#__$__#__$#_#_$$_#___#_#__#"
    "_##_#___#_____###____$_#_#__#"
    "_#__#$___#_###__#__#_$$#_#__#"
    "_#____$##_$__#___##_$__#_#_##"
    "####$_$_#____##__#___$____..#"
    "#__#____###_#_$_$_###__###.*#"
    "#_____##__$$_@__$_____##....#"
    "#__##__##___$__#$#__##....*.#"
    "##_#__$__#_#_$##__##....*.###"
    "##_##__$__#_$_#__#....*.###__"
    "#____$_####___#_....*.###____"
    "#___#__#__#__#__..*.###______"
    "########__###########________",

    "26 16 "
    "________#####_____________"
    "________#___####__________"
    "________#_$____####__####_"
    "________#___#_$#__####__#_"
    "###########_#___$___#___#_"
    "#.._____#_$__####_#__#__#_"
    "#..$__#___$__#__$_#_$_.##_"
    "#.*#_#_$_$_##__##____#.#__"
    "#..#$_@_#___##____$$_#.#__"
    "#..#_$_$__$_$_##___##_.#__"
    "#.*$$_#_##___$_#$#_$_#.#__"
    "#..#______##___#_____#.#__"
    "#..#######__###_######.##_"
    "#_$$__________________*.##"
    "#__##################__..#"
    "####________________######"

};

Level
level_load(size_t level_id) {
    Level level;

    if (level_id > serialized_levels.size()) {
        level_id = 0;
    }

    std::istringstream iss(serialized_levels[level_id]);
    iss >> level;

    return std::move(level);
}

size_t
Level::num_levels() {
    return serialized_levels.size();
}
