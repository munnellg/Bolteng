#ifndef SOKOBAN_H
#define SOKOBAN_H

#define GAME_NAME "SOKOBAN"

#include <entt/entt.hpp>

class Sokoban {
public:
    Sokoban();

    bool init();
    bool play();
    void quit();

    void quit_main_loop();

private:
    bool m_quit;
    entt::registry m_registry;
};

#endif // SOKOBAN_H
