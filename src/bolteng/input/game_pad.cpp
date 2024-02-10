#include "game_pad.h"
#include "../logging.h"

namespace bolt {
    namespace input {
        std::array<GamePad, MAX_GAME_PADS> game_pads = {
            GamePad(0), // player 1
            GamePad(1), // player 2
            GamePad(2), // player 3
            GamePad(3)  // player 4
        };

        GamePad::GamePad(int playerIndex) : 
            m_powerLevel(1.0f),
            m_enabled(0),
            m_playerIndex(playerIndex)
        {}

        void GamePad::bindButton(ButtonCode button, std::function<int(void)> callback) {
            m_buttonCallbacks[button] = callback;
        }

        void GamePad::bindEvent(GamePadEventCode event, std::function<int(void)> callback) {
            m_eventCallbacks[event] = callback;
        }

        void GamePad::buttonUp(ButtonCode button) {
            if (button < m_buttonState.size()) {
                m_buttonState[button] = false;
            }
        }

        void GamePad::buttonDown(ButtonCode button) {
            if (button < m_buttonState.size()) {
                m_buttonState[button] = true;
            } 

            if (m_buttonCallbacks.contains(button)) {
                m_buttonCallbacks[button]();
            }
        }

        void GamePad::axisMotion(AxisCode axis, float displacement) {
            if (axis < m_axisState.size()) {
                m_axisState[axis] = std::min(1.0f, displacement);
            }
        }

        void GamePad::broadcast(GamePadEventCode code) {
            if (m_eventCallbacks.contains(code)) {
                m_eventCallbacks[code]();
            }
        }
    }
}
