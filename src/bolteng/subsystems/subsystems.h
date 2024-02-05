#ifndef CORE_SUBSYSTEMS_SUBSYSTEMS
#define CORE_SUBSYSTEMS_SUBSYSTEMS

#include <functional>

namespace subsystems {
    int init();
    void quit();

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

    namespace events {
        int init();

        void process();

        void quit();
    }

    namespace render {
        extern uint32_t shader_program;

        int init();
        void quit();
    }
}

#endif // CORE_SUBSYSTEMS_SUBSYSTEMS
