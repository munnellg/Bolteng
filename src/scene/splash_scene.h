#ifndef SPLASH_SCENE_H
#define SPLASH_SCENE_H

#include "../bolteng/application/scene.h"

#include <cstdint>

class SplashScene : public Scene {
public:
    SplashScene();

    void onEnter();
    void update(uint64_t);
    void onExit();
};

#endif // SPASH_SCENE_H
