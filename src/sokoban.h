#ifndef SOKOBAN_H
#define SOKOBAN_H

#include "core/entity_manager.h"

class Sokoban {
public:
    Sokoban();

    bool init();
    bool play();
    void quit();

private:
    EntityManager m_entityManager;
};

#endif // SOKOBAN_H
