#include "subsystems.h"
#include "../logging.h"
#include "../input/input.h"
#include "../defines.h"

#include <SDL2/SDL_joystick.h>
#include <iostream>
#include <SDL2/SDL.h>

using namespace bolt::input;

namespace subsystems {
    namespace events {
        // handles to joystick/controller devices
        std::array<SDL_GameController*, MAX_GAME_PADS> pControllers = {0};

        int find_open_controller_slot(int start) {
            int i = start;

            do {
                if (!pControllers[i]) { 
                    return i; 
                }
                i = (i + 1) % pControllers.size();
            } while (i != start);

            return -1;
        }

        bool is_already_open(SDL_JoystickID deviceId) {
            return std::any_of(
                    pControllers.begin(),
                    pControllers.end(), 
                    [&](SDL_GameController *gc) { 
                        SDL_Joystick* j = SDL_GameControllerGetJoystick(gc);
                        return SDL_JoystickInstanceID(j) == deviceId; 
                    });
        }

        int disconnect_controller(int iHandle) {
            if (pControllers[iHandle]) {
                SDL_GameControllerClose(pControllers[iHandle]);
                pControllers[iHandle] = nullptr;
                return 1;
            }

            return 0;
        }

        int connect_controller(int deviceId, int iHandle) {
            if (!SDL_IsGameController(deviceId)) {
                return 0;
            }

            if (is_already_open(SDL_JoystickGetDeviceInstanceID(deviceId))) {
                return 0;
            }
            
            SDL_GameController* controller = SDL_GameControllerOpen(deviceId);

            if (!controller) {
                LOG_WARN("SDL_GameControllerOpen error: %s", SDL_GetError());
                return 0;
            }
            
            LOG_INFO("Game Controller %d connected", iHandle);
            pControllers[iHandle] = controller; 

#if SDL_VERSION_ATLEAST(2, 0, 12)
            SDL_JoystickSetPlayerIndex(controller, iHandle);
#endif
            return 1;
        }

        int get_controller_index(SDL_JoystickID deviceId) {
            for (int i = 0; i < pControllers.size(); i++) {
                if (pControllers[i] != nullptr) {
                    SDL_Joystick *j = SDL_GameControllerGetJoystick(pControllers[i]);
                    if (SDL_JoystickInstanceID(j) == deviceId) {
                        return i;
                    }
                }
            }

            return -1;
        }

        int init() {
            for (int i = 0; i < pControllers.size(); i++) { 
                pControllers[i] = nullptr; 
            }

            return 1;
        }

        void process() {
            static int last_poll = 0;

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    // platform events
                    case SDL_QUIT:
                        platform.broadcast(PLATFORM_QUIT);
                        break;
                    case SDL_APP_TERMINATING:
                        break;
                    case SDL_APP_LOWMEMORY:
                        break;
                    case SDL_APP_WILLENTERBACKGROUND:
                        break;
                    case SDL_APP_DIDENTERBACKGROUND:
                        break;
                    case SDL_APP_WILLENTERFOREGROUND:
                        break;
                    case SDL_APP_DIDENTERFOREGROUND:
                        break;
                    case SDL_DISPLAYEVENT:
                        break;
                    case SDL_WINDOWEVENT:
                        break;
                    case SDL_SYSWMEVENT:
                        break;

                    // keyboard events
                    case SDL_KEYDOWN:
                    {
                        keyboard.keydown((ScanCode) e.key.keysym.scancode);
                        break;
                    }
                    case SDL_KEYUP:
                    {
                        keyboard.keyup((ScanCode) e.key.keysym.scancode);
                        break;
                    }
                    case SDL_TEXTEDITING:
                        break;
                    case SDL_TEXTINPUT:
                        break;
                    case SDL_KEYMAPCHANGED:
                        break;

                    // mouse events
                    case SDL_MOUSEMOTION:
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        break;
                    case SDL_MOUSEBUTTONUP:
                        break;
                    case SDL_MOUSEWHEEL:
                        break;

                    // joystick/controller events
                    case SDL_JOYAXISMOTION:
                        break;
                    case SDL_JOYBALLMOTION:
                        break;
                    case SDL_JOYHATMOTION:
                        break;
                    case SDL_JOYBUTTONDOWN:
                        break;
                    case SDL_JOYBUTTONUP:
                        break;
                    case SDL_JOYDEVICEADDED:
                        break;
                    case SDL_JOYDEVICEREMOVED:
                        break;

                    // Game Controller Events
                    case SDL_CONTROLLERAXISMOTION:
                    {
                        int iController = get_controller_index(e.caxis.which);

                        if (iController >= 0) {
                            game_pads[iController].axisMotion(e.caxis.axis, static_cast<float>(e.caxis.value) / 32767.0f);
                        }

                        break;
                    }
                    case SDL_CONTROLLERBUTTONDOWN:
                    {
                        int iController = get_controller_index(e.cbutton.which);

                        if (iController >= 0) {
                            game_pads[iController].buttonDown(e.cbutton.button);
                        }

                        break;
                    }
                    case SDL_CONTROLLERBUTTONUP:
                    {
                        int iController = get_controller_index(e.cbutton.which);

                        if (iController >= 0) {
                            game_pads[iController].buttonUp(e.cbutton.button);
                        }

                        break;
                    }
                    case SDL_CONTROLLERDEVICEADDED:
                    {
                        int iControllerHandle = find_open_controller_slot(0);

                        if (iControllerHandle >= 0) {
                            LOG_DEBUG("connecting to %d", iControllerHandle);
                            if (connect_controller(e.cdevice.which, iControllerHandle)) {
                                game_pads[iControllerHandle].broadcast(GAME_PAD_CONNECT_EVENT);
                            }
                        }

                        break;
                    }
                    case SDL_CONTROLLERDEVICEREMOVED:
                    {
                        int iControllerHandle = get_controller_index(e.cbutton.which);

                        if (iControllerHandle >= 0) {
                            if (disconnect_controller(iControllerHandle)) {
                                game_pads[iControllerHandle].broadcast(GAME_PAD_DISCONNECT_EVENT);
                            }
                        }

                        break;
                    }
                    case SDL_CONTROLLERDEVICEREMAPPED:
                        break;

                    // other
                    case SDL_FINGERDOWN:
                        break;
                    case SDL_FINGERUP:
                        break;
                    case SDL_FINGERMOTION:
                        break;
                    case SDL_DOLLARGESTURE:
                        break;
                    case SDL_DOLLARRECORD:
                        break;
                    case SDL_MULTIGESTURE:
                        break;
                    case SDL_CLIPBOARDUPDATE:
                        break;
                    case SDL_DROPFILE:
                        break;
                    case SDL_DROPTEXT:
                        break;
                    case SDL_DROPBEGIN:
                        break;
                    case SDL_DROPCOMPLETE:
                        break;
                    case SDL_AUDIODEVICEADDED:
                        break;
                    case SDL_AUDIODEVICEREMOVED:
                        break;
                    case SDL_RENDER_TARGETS_RESET:
                        break;
                    case SDL_RENDER_DEVICE_RESET:
                        break;
                    case SDL_USEREVENT:
                        break;
                    case SDL_LASTEVENT: 
                        break;
                    default:
                        break;
                }
            }
        }

        void quit() {
            std::for_each(pControllers.begin(), pControllers.end(), [](auto j) { SDL_GameControllerClose(j); });
        }
    }
}

