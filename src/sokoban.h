#ifndef SOKOBAN_H
#define SOKOBAN_H

#include "scene/level_scene.h"
#include "bolteng/application/boltapp.h"

class Sokoban : public bolt::BoltApp {
public:
    Sokoban();

protected:
    bool postInit() override;
    bool preQuit() override;
};

#endif // SOKOBAN_H
