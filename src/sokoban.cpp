#include "sokoban.h"
#include "bolteng/defines.h"
#include "scene/level_scene.h"
#include "bolteng/subsystems/subsystems.h"
#include "bolteng/logging.h"

#include <cstdint>
#include <iostream>
#include <functional>
#include <entt/entt.hpp>

Sokoban::Sokoban() : bolt::BoltApp(), m_current_level(0) {
    m_post_init = std::bind(&Sokoban::post_init, this);
}

void Sokoban::update(uint64_t const deltaTime) {
    m_level.update(deltaTime);
}

bool Sokoban::post_init() {

    bolt::input::game_pads[0].bindButton(bolt::input::BUTTON_LEFT_SHOULDER, std::bind(&Sokoban::prev_level, this));
    bolt::input::game_pads[0].bindButton(bolt::input::BUTTON_RIGHT_SHOULDER, std::bind(&Sokoban::next_level, this));
    bolt::input::game_pads[0].bindEvent(bolt::input::GAME_PAD_CONNECT_EVENT, std::bind(&Sokoban::player_joined, this));
    bolt::input::game_pads[0].bindEvent(bolt::input::GAME_PAD_DISCONNECT_EVENT, std::bind(&Sokoban::player_left, this));

    bolt::input::keyboard.bind(bolt::input::KEY_UP, std::bind(&Sokoban::next_level, this));
    bolt::input::keyboard.bind(bolt::input::KEY_DOWN, std::bind(&Sokoban::prev_level, this));
    bolt::input::keyboard.bind(bolt::input::KEY_ESCAPE, std::bind(&Sokoban::quit_main_loop, this));

    m_current_level = 0;
    m_level.load_level(m_current_level);

    return true;
}

int Sokoban::prev_level() {
    if (--m_current_level >= 60) {
        m_current_level = 59;
    }

    m_level.load_level(m_current_level);

    return 0;
}

int Sokoban::next_level() {
    if (++m_current_level >= 60) {
        m_current_level = 0;
    }

    m_level.load_level(m_current_level);

    return 0;
}

int Sokoban::player_joined() {
    LOG_INFO("Player joined");
    return 0;
}

int Sokoban::player_left() {
    LOG_INFO("Player left");
    return 0;
}
