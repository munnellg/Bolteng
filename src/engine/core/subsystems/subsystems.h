#ifndef CORE_SUBSYSTEMS_SUBSYSTEMS
#define CORE_SUBSYSTEMS_SUBSYSTEMS

#include <cstdint>
#include <functional>

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
        int init();
        void swap();
        void quit();

        void set_window_title(char const *title);
    }

    namespace input {
        int init();
        void quit();
    }
}

#endif // CORE_SUBSYSTEMS_SUBSYSTEMS
