#ifndef CORE_SUBSYSTEMS_SUBSYSTEMS
#define CORE_SUBSYSTEMS_SUBSYSTEMS

#include <cstdint>

namespace subsystems {
    int init();
    void handle_events();
    void pause(uint32_t ms);
    void quit();

    namespace display {
        int init();
        void swap();
        void quit();
    }

    namespace input {
        int init();
        void quit();
    }
}

#endif // CORE_SUBSYSTEMS_SUBSYSTEMS
