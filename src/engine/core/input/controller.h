#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../defines.h"
#include "../subsystems/subsystems.h"

#include <array>
#include <map>

namespace bolt {
    namespace input {

        class Controller {
        public:
            static int const NUM_BUTTONS = 256;
            static int const NUM_AXIS    = 7;
            Controller(int playerIndex);

            float m_powerLevel;

            void bindButton(ScanCode key, std::function<int(void)> callback);
            void bindEvent(ControllerEventCode eventCode, std::function<int(void)> callback);

        private:
            std::array<bool, NUM_BUTTONS> m_buttonState;
            std::array<float, NUM_AXIS> m_axisState;
            std::map<ButtonCode, std::function<int(void)>> m_buttonCallbacks;

            std::map<ControllerEventCode, std::function<int(void)>> m_eventCallbacks;

            int m_enabled;
            int m_playerIndex;

            void buttonUp(ButtonCode button);
            void buttonDown(ButtonCode button);
            void axisMotion(AxisCode axis, float displacement);

            // signals for when the controller is connected/disconnected
            void broadcast(ControllerEventCode code);

            friend void subsystems::events::process();
        };
    }
}

#endif
