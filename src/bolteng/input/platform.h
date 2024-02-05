#ifndef SYSTEM_H
#define SYSTEM_H

#include "../defines.h"
#include "../subsystems/subsystems.h"

#include <map>

namespace bolt {
    namespace input {
        class Platform {
        public:
            void bind(PlatformCode code, std::function<int(void)> callback);

        private:
            std::map<PlatformCode, std::function<int(void)>> m_callbacks;

            void broadcast(PlatformCode code);

            friend void subsystems::events::process();
        };
    }
}

#endif
