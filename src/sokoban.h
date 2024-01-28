#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <SDL2/SDL.h>
#include "scene/level_scene.h"

#define GAME_NAME "SOKOBAN"

class Sokoban {
public:
    Sokoban();

    bool init();
    bool play();
    void quit();

    void set_level(SDL_KeyboardEvent const &event);
    void quit_main_loop();

    LevelScene m_level;
    size_t m_current_level; 
private:
    bool m_quit;
};

#endif // SOKOBAN_H
