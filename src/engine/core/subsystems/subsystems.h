#ifndef CORE_SUBSYSTEMS_SUBSYSTEMS
#define CORE_SUBSYSTEMS_SUBSYSTEMS

#include <cstdint>
#include <filesystem>
#include <functional>
#include <entt/entt.hpp>

namespace subsystems {
    int init();
    void handle_events();
    void quit();

    void register_quit_callback(std::function<void(void)> cb_quit);

    namespace time {
        void pause(uint32_t ms);
        uint64_t get_ticks();
        uint64_t get_performance_counter();
        uint64_t get_performance_frequency();
    }

    namespace display {
        extern float aspect;

        int init();
        void swap();
        void quit();

        void set_window_title(char const *title);
    }

    namespace input {
        int init();
        void quit();
    }

    namespace render {
        extern entt::entity camera;
        extern uint32_t shader_program;

        int init();
        void quit();
    }
}

#endif // CORE_SUBSYSTEMS_SUBSYSTEMS
