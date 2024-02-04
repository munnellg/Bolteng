#include "keyboard.h"

namespace bolt {
    namespace input {
        Keyboard keyboard;

        void Keyboard::bind(ScanCode key, std::function<int(void)> callback) {
            m_callbacks[key] = callback;
        }

        void Keyboard::keyup(ScanCode key) {
            if (key < m_keystate.size()) {
                m_keystate[key] = false;
            }
        }

        void Keyboard::keydown(ScanCode key) {
            if (key < m_keystate.size()) {
                m_keystate[key] = true;
            } 

            if (m_callbacks.contains(key)) {
                m_callbacks[key]();
            }
        }
    }
}
