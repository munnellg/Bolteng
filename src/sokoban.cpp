#include "sokoban.h"
#include "scene/level_scene.h"
#include "engine/core/subsystems/subsystems.h"
#include "engine/core/logging.h"

#include <cstdint>
#include <iostream>
#include <functional>
#include <entt/entt.hpp>

Sokoban::Sokoban() : m_quit(false), m_current_level(0) {}

bool Sokoban::init() {
    logging::set_level(logging::Level::debug);

    if(!subsystems::init()) {
        return false;
    }


    subsystems::register_key_callback(std::bind(&Sokoban::set_level, this, std::placeholders::_1));
    subsystems::register_quit_callback(std::bind(&Sokoban::quit_main_loop, this));

    return true;
}

bool Sokoban::play() {
    m_current_level = 0;
    m_level.load_level(m_current_level);

    uint64_t curr = 0, last = 0;

    while (!m_quit) {
        last = curr;
        curr = subsystems::time::get_ticks();

        subsystems::handle_events();
        m_level.update(curr - last);
    } 

    return true;
}

void Sokoban::set_level(SDL_KeyboardEvent const &event)  {
    switch (event.keysym.scancode) {
        case SDL_SCANCODE_DOWN:
            if (--m_current_level >= 60) {
                m_current_level = 59;
            }
            m_level.load_level(m_current_level);
            break;
        case SDL_SCANCODE_UP:
            if (++m_current_level >= 60) {
                m_current_level = 0;
            }
            m_level.load_level(m_current_level);
            break;
        default:
            break;
    }
}

void Sokoban::quit_main_loop() {
    m_quit = true;
}

void Sokoban::quit() {
    // release all memory
    subsystems::quit();
}

