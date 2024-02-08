#ifndef SOKOBAN_H
#define SOKOBAN_H

#include "scene/level_scene.h"
#include "bolteng/application/boltapp.h"

class Sokoban : public bolt::BoltApp {
public:
    Sokoban();

    void update(uint64_t const deltaTime);

    bool post_init();

    int next_level();
    int prev_level();
    int player_joined();
    int player_left();

    LevelScene m_level;
    size_t m_current_level; 
private:
    bool m_quit;
};

#endif // SOKOBAN_H
