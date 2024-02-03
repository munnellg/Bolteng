#include "sokoban.h"
#include "scene/level_scene.h"
#include "engine/core/subsystems/subsystems.h"
#include "engine/core/logging.h"

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

    subsystems::events::register_quit_callback(std::bind(&Sokoban::quit_main_loop, this));

    return true;
}

bool Sokoban::play() {
    m_current_level = 0;
    m_level.load_level(m_current_level);

    uint64_t curr = 0, last = 0;

    while (!m_quit) {
        last = curr;
        curr = subsystems::time::get_ticks();

        subsystems::events::handle_events();
        update();
        m_level.update(curr - last);
    } 

    return true;
}

void Sokoban::update()  {
    if (keyboard.m_keystate[Keyboard::KEY_UP]) {
        if (--m_current_level >= 60) {
            m_current_level = 59;
        }
        m_level.load_level(m_current_level);
    }

    if (keyboard.m_keystate[Keyboard::KEY_DOWN]) {
        if (++m_current_level >= 60) {
            m_current_level = 0;
        }
        m_level.load_level(m_current_level);
    }
}

void Sokoban::quit_main_loop() {
    m_quit = true;
}

void Sokoban::quit() {
    // release all memory
    subsystems::quit();
}

