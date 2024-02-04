#include "controller.h"
#include "../logging.h"

namespace bolt {
    namespace input {
        std::array<Controller, MAX_CONTROLLERS> controllers = {
            Controller(0), // player 1
            Controller(1), // player 2
            Controller(2), // player 3
            Controller(3)  // player 4
        };

        Controller::Controller(int playerIndex) : 
            m_playerIndex(playerIndex),
            m_enabled(0),
            m_powerLevel(1.0f)
        {}

        void Controller::bindButton(ButtonCode button, std::function<int(void)> callback) {
            m_buttonCallbacks[button] = callback;
        }

        void Controller::bindEvent(ControllerEventCode event, std::function<int(void)> callback) {
            m_eventCallbacks[event] = callback;
        }

        void Controller::buttonUp(ButtonCode button) {
            if (button < m_buttonState.size()) {
                m_buttonState[button] = false;
            }
        }

        void Controller::buttonDown(ButtonCode button) {
            if (button < m_buttonState.size()) {
                m_buttonState[button] = true;
            } 

            if (m_buttonCallbacks.contains(button)) {
                m_buttonCallbacks[button]();
            }
        }

        void Controller::axisMotion(AxisCode axis, float displacement) {
            if (axis < m_axisState.size()) {
                m_axisState[axis] = std::min(1.0f, displacement);
            }
        }

        void Controller::broadcast(ControllerEventCode code) {
            if (m_eventCallbacks.contains(code)) {
                m_eventCallbacks[code]();
            }
        }
    }
}
