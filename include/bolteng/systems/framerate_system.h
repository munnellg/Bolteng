#ifndef FRAMERATE_SYSTEM_H
#define FRAMERATE_SYSTEM_H

#include "component_system.h"

namespace bolt {
    class FramerateSystem : public ComponentSystem {

    public:
        FramerateSystem(entt::registry *m_pRegistry);
        ~FramerateSystem() override;

        void update(uint64_t deltaTime) override;
    };
}
#endif // FRAMERATE_SYSTEM_H
