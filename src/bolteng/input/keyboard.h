#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../defines.h"
#include "../subsystems/subsystems.h"

#include <array>
#include <map>
#include <functional>

namespace bolt { 
    namespace input {

        class Keyboard {
        public:
            static int const NUM_KEYS = 256;

            void bind(ScanCode key, std::function<int(void)> callback);

        private:
            std::array<bool, NUM_KEYS> m_keystate;
            std::map<ScanCode, std::function<int(void)>> m_callbacks;

            void keydown(ScanCode key);
            void keyup(ScanCode key);

            friend void subsystems::events::process();
        };
    }
}

#endif
