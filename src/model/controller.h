#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <entt/entt.hpp>
#include "../bolteng/input/input.h"

class Controller {
public:
    Controller();

    int bind(entt::entity const entity, entt::registry *pRegistry);
    int bind(bolt::input::GamePad &game_pad);
    int bind(bolt::input::Keyboard &keyboard);

    int moveUp();
    int moveDown();
    int moveLeft();
    int moveRight();

private:
    entt::entity m_target;
    entt::registry *m_pRegistry;

    void addMoveComponent(float dx, float dy, float speed);
};

#endif // CONTROLLER_H
