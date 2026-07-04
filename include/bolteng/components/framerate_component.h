#ifndef PROFILING_FRAMERATE_COMPONENT_H
#define PROFILING_FRAMERATE_COMPONENT_H

#include <array>

class FramerateComponent {
public: 
    constexpr static const size_t MAX_DELTAS = 100;

    FramerateComponent();
    ~FramerateComponent();

    std::array<uint64_t, MAX_DELTAS> const& getDeltas() const;

    void pushDelta(uint64_t const delta);

private:
    std::array<uint64_t, MAX_DELTAS> m_deltas;
    size_t m_currDeltaIdx;
};
#endif // PROFILING_FRAMERATE_COMPONENT_H
