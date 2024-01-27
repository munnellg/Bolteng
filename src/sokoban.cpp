#include "sokoban.h"
#include "scene/level_scene.h"
#include "engine/core/subsystems/subsystems.h"

#include <cstdint>
#include <functional>
#include <entt/entt.hpp>

Sokoban::Sokoban() : m_quit(false) {}

bool Sokoban::init() {
    logging::set_level(logging::Level::debug);

    if(!subsystems::init()) {
        return false;
    }

    subsystems::register_quit_callback(std::bind(&Sokoban::quit_main_loop, this));

    return true;
}

bool Sokoban::play() {
    LevelScene level;

    uint64_t curr = 0, last = 0;

    while (!m_quit) {
        last = curr;
        curr = subsystems::time::get_ticks();

        subsystems::handle_events();
        level.update(curr - last);
    } 

    return true;
}

void Sokoban::quit_main_loop() {
    m_quit = true;
}

void Sokoban::quit() {
    // release all memory
    subsystems::quit();
}

