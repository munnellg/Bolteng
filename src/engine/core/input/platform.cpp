#include "platform.h"

namespace bolt {
    namespace input {
        Platform platform;

        void Platform::bind(PlatformCode code, std::function<int(void)> callback) {
            m_callbacks[code] = callback;
        }

        void Platform::broadcast(PlatformCode code) {
            if (m_callbacks.contains(code)) {
                m_callbacks[code]();
            }
        }
    }
}
