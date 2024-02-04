#ifndef SOKOBAN_H
#define SOKOBAN_H

#include "scene/level_scene.h"

#define GAME_NAME "SOKOBAN"

class Sokoban {
public:
    Sokoban();

    bool init();
    bool play();
    void quit();

    int next_level();
    int prev_level();
    int player_joined();
    int player_left();

    int quit_main_loop();

    LevelScene m_level;
    size_t m_current_level; 
private:
    bool m_quit;
};

#endif // SOKOBAN_H
