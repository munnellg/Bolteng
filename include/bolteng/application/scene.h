#ifndef SCENE_H
#define SCENE_H

#include <cstdint>

class Scene {
public:
    virtual ~Scene() = default;
    virtual void onEnter() = 0;
    virtual void update(uint64_t deltaTime) = 0;
    virtual void onExit() = 0;
};

#endif // SCENE_H
