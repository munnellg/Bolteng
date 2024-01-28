#include "framerate_system.h"
#include "../components/framerate_component.h"
#include "../subsystems/subsystems.h"
#include "../logging.h"
#include <entt/entt.hpp>
#include <numeric>

FramerateSystem::FramerateSystem(entt::registry *pRegistry) : ComponentSystem(pRegistry) {
}

FramerateSystem::~FramerateSystem() {
}

void FramerateSystem::update(uint64_t deltaTime) {

    auto view = m_pRegistry->view<FramerateComponent>();
    for (auto [entity, framerate]: view.each()) {
        auto frames = framerate.getDeltas();
        framerate.pushDelta(1000ul / std::max(1ul, deltaTime));

        char buf[256] = {0};
        uint64_t max = *std::max_element(frames.begin(), frames.end());
        uint64_t min = *std::min_element(frames.begin(), frames.end());
        uint64_t avg = std::accumulate(frames.begin(), frames.end(), 0) / frames.size();
        sprintf(buf, "Sokoban - avg: %ld - min: %ld - max: %ld", avg, min, max);

        subsystems::display::set_window_title(buf);
    }
}
