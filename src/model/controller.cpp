#include "controller.h"
#include "../bolteng/components/components.h"

#include <glm/glm.hpp>
#include <functional>

Controller::Controller() : 
    m_target(bolt::input::UNBOUND_ENTITY),
    m_pRegistry(nullptr)
{}

int Controller::moveUp() {
    addMoveComponent(0.0f, 1.0f, 4.0f);
    return 0;
}

int Controller::moveDown() {
    addMoveComponent(0.0f, -1.0f, 4.0f);
    return 0;
}

int Controller::moveLeft() {
    addMoveComponent(-1.0f, 0.0f, 4.0f);
    return 0;
}

int Controller::moveRight() {
    addMoveComponent(1.0f, 0.0f, 4.0f);
    return 0;
}

int Controller::bind(entt::entity const target, entt::registry *pRegistry) {
    m_target    = target;
    m_pRegistry = pRegistry;
    return 0;
}

int Controller::bind(bolt::input::GamePad &game_pad) {
    game_pad.bindButton(bolt::input::BUTTON_DPAD_UP, std::bind(&Controller::moveUp, this));
    game_pad.bindButton(bolt::input::BUTTON_DPAD_DOWN, std::bind(&Controller::moveDown, this));
    game_pad.bindButton(bolt::input::BUTTON_DPAD_LEFT, std::bind(&Controller::moveLeft, this));
    game_pad.bindButton(bolt::input::BUTTON_DPAD_RIGHT, std::bind(&Controller::moveRight, this));
    return 0;
}

int Controller::bind(bolt::input::Keyboard &keyboard) {
    keyboard.bind(bolt::input::KEY_W, std::bind(&Controller::moveUp, this));
    keyboard.bind(bolt::input::KEY_S, std::bind(&Controller::moveDown, this));
    keyboard.bind(bolt::input::KEY_A, std::bind(&Controller::moveLeft, this));
    keyboard.bind(bolt::input::KEY_D, std::bind(&Controller::moveRight, this));
    return 0;
}

void Controller::addMoveComponent(float dx, float dy, float speed) {
    if (m_pRegistry == nullptr) { return; }

    // don't add move to something that's already moving
    if (m_pRegistry->try_get<MoveComponent>(m_target)) { return; }
    
    MoveComponent moveComponent;
    moveComponent.m_direction = glm::vec3(dx, dy, 0.0f);
    moveComponent.m_speed = speed;
    m_pRegistry->emplace<MoveComponent>(m_target, moveComponent);
}

