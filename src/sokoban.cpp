#include "sokoban.h"
#include "bolteng/defines.h"
#include "scene/level_scene.h"
#include "bolteng/subsystems/subsystems.h"
#include "bolteng/logging.h"

#include <cstdint>
#include <iostream>
#include <functional>
#include <entt/entt.hpp>

using namespace bolt::input;

Sokoban::Sokoban() : m_quit(false), m_current_level(0) {}

bool Sokoban::init() {
    logging::set_level(logging::Level::debug);

    if(!subsystems::init()) {
        return false;
    }

    bolt::input::game_pads[0].bindButton(BUTTON_LEFT_SHOULDER, std::bind(&Sokoban::prev_level, this));
    bolt::input::game_pads[0].bindButton(BUTTON_RIGHT_SHOULDER, std::bind(&Sokoban::next_level, this));
    bolt::input::game_pads[0].bindEvent(GAME_PAD_CONNECT_EVENT, std::bind(&Sokoban::player_joined, this));
    bolt::input::game_pads[0].bindEvent(GAME_PAD_DISCONNECT_EVENT, std::bind(&Sokoban::player_left, this));

    bolt::input::keyboard.bind(KEY_UP, std::bind(&Sokoban::next_level, this));
    bolt::input::keyboard.bind(KEY_DOWN, std::bind(&Sokoban::prev_level, this));
    bolt::input::keyboard.bind(KEY_ESCAPE, std::bind(&Sokoban::quit_main_loop, this));
    bolt::input::platform.bind(PLATFORM_QUIT, std::bind(&Sokoban::quit_main_loop, this));

    return true;
}

bool Sokoban::play() {
    m_current_level = 0;
    m_level.load_level(m_current_level);

    uint64_t curr = 0, last = 0;

    while (!m_quit) {
        last = curr;
        curr = subsystems::time::get_ticks();

        subsystems::events::process();
        m_level.update(curr - last);
    } 

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

int Sokoban::quit_main_loop() {
    m_quit = true;
    return 0;
}

void Sokoban::quit() {
    // release all memory
    subsystems::quit();
}

