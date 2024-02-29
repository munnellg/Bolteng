#include "subsystems.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

namespace bolt {
    namespace subsystems {
        namespace time {
            void pause(uint32_t ms) {
                SDL_Delay(ms);
            }

            uint64_t get_ticks() {
                return SDL_GetTicks();
            }

            uint64_t get_performance_counter() {
                return SDL_GetPerformanceCounter();
            }

            uint64_t get_performance_frequency() {
                return SDL_GetPerformanceFrequency();
            }
        }
    }
}
