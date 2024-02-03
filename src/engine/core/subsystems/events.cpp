#include "subsystems.h"
#include "../logging.h"
#include "../input/input.h"

#include <SDL2/SDL_joystick.h>
#include <iostream>
#include <SDL2/SDL.h>

static std::function<void(void)> g_cb_quit;
using namespace bolt::input;

namespace bolt {
    namespace input {
        Mouse mouse;
        Keyboard keyboard;
        std::array<Controller, MAX_CONTROLLERS> controllers;
    }
}

namespace subsystems {
    namespace events {
        // handles to joystick/controller devices
        std::array<SDL_Joystick*, MAX_CONTROLLERS> pJoysticks = {0};

        void sync_controller_state(int i) {
            SDL_Joystick *joystick = pJoysticks[i];
            
            // check if the controller is assigned yet 
            if (joystick == nullptr) { 
                // skip this one if not
                return;
            }

            // check if the controller has been disconnected
            if (!SDL_JoystickGetAttached(joystick)) {
                LOG_INFO("Controller %d disconnected", i);
                
                // close the handle if we've lost connection
                SDL_JoystickClose(joystick);
                pJoysticks[i] = nullptr;

                return;
            }

            // sync data that is likely to change
            switch (SDL_JoystickCurrentPowerLevel(pJoysticks[i])) {
                case SDL_JOYSTICK_POWER_UNKNOWN:
                    controllers[i].m_powerLevel = 0.5f;
                    break;
                case SDL_JOYSTICK_POWER_EMPTY:
                    controllers[i].m_powerLevel = 0.0f;
                    break;
                case SDL_JOYSTICK_POWER_LOW:
                    controllers[i].m_powerLevel = 0.1f;
                    break;
                case SDL_JOYSTICK_POWER_MEDIUM:
                    controllers[i].m_powerLevel = 0.5f;
                    break;
                case SDL_JOYSTICK_POWER_FULL:
                    controllers[i].m_powerLevel = 1.0f;
                    break;
                case SDL_JOYSTICK_POWER_WIRED:
                    controllers[i].m_powerLevel = 1.0f;
                    break;
                case SDL_JOYSTICK_POWER_MAX:
                    controllers[i].m_powerLevel = 1.0f;
                    break;
            }
        }

        void sync_all_controller_states() {
            for (int i = 0; i < MAX_CONTROLLERS; i++) {
                sync_controller_state(i);
            }
        }

        int find_open_controller_slot(int start) {
            int i = start;

            do {
                if (!pJoysticks[i]) { 
                    return i; 
                }
                i = (i + 1) % pJoysticks.size();
            } while (i != start);

            return -1;
        }

        bool is_already_open(SDL_JoystickID deviceId) {
            return std::any_of(
                    pJoysticks.begin(),
                    pJoysticks.end(), 
                    [&](SDL_Joystick *j) { 
                        return SDL_JoystickInstanceID(j) == deviceId; 
                    });
        }

        void scan_input_devices() {
            int const num_joysticks = SDL_NumJoysticks();

            int iJoystickHandle = find_open_controller_slot(0);

            for (int i = 0; i < num_joysticks && iJoystickHandle > 0; i++) {
                if (is_already_open(SDL_JoystickGetDeviceInstanceID(i))) {
                    continue;
                }
                
                SDL_Joystick* joystick = SDL_JoystickOpen(i);

                if (!joystick) {
                    LOG_WARN("SDL_JoystickOpen error: %s", SDL_GetError());
                    continue;
                }
                
                LOG_INFO("Joystick %d connected", i);
                pJoysticks[iJoystickHandle] = joystick; 

#if SDL_VERSION_ATLEAST(2, 0, 12)
                SDL_JoystickSetPlayerIndex(joystick, iJoystickHandle);
#endif
                sync_controller_state(iJoystickHandle);
                
                // find the next controller we can connect to
                iJoystickHandle = find_open_controller_slot(iJoystickHandle);
            }
        }

        int init() {
            scan_input_devices();
            return 1;
        }

        void handle_events() {
            static int last_poll = 0;

            // poll device state every N seconds
            if (subsystems::time::get_ticks() - last_poll > CONTROLLER_STATE_SYNC_FREQ) {
                sync_all_controller_states();
                scan_input_devices();
                last_poll = subsystems::time::get_ticks();
            }

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    case SDL_QUIT:
                        g_cb_quit();
                        break;
                    case SDL_KEYDOWN:
                        keyboard.m_keystate[e.key.keysym.scancode] = true;
                        break;
                    case SDL_KEYUP:
                        keyboard.m_keystate[e.key.keysym.scancode] = false;
                        break;
                    
                    default:
                        break;
                }
            }
        }

        void register_quit_callback(std::function<void(void)> cb_quit) {
            g_cb_quit = cb_quit;
        }

        void quit() {
            std::for_each(pJoysticks.begin(), pJoysticks.end(), [](auto j) { SDL_JoystickClose(j); });
        }
    }
}

namespace bolt {
    namespace input {
        int const Keyboard::KEY_0 = SDL_SCANCODE_0;
        int const Keyboard::KEY_1 = SDL_SCANCODE_1;
        int const Keyboard::KEY_2 = SDL_SCANCODE_2;
        int const Keyboard::KEY_3 = SDL_SCANCODE_3;
        int const Keyboard::KEY_4 = SDL_SCANCODE_4;
        int const Keyboard::KEY_5 = SDL_SCANCODE_5;
        int const Keyboard::KEY_6 = SDL_SCANCODE_6;
        int const Keyboard::KEY_7 = SDL_SCANCODE_7;
        int const Keyboard::KEY_8 = SDL_SCANCODE_8;
        int const Keyboard::KEY_9 = SDL_SCANCODE_9;
        int const Keyboard::KEY_A = SDL_SCANCODE_A;
        int const Keyboard::KEY_AC_BACK = SDL_SCANCODE_AC_BACK;
        int const Keyboard::KEY_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS;
        int const Keyboard::KEY_AC_FORWARD = SDL_SCANCODE_AC_FORWARD;
        int const Keyboard::KEY_KP_DBLAMPERSAND = SDL_SCANCODE_KP_DBLAMPERSAND;
        int const Keyboard::KEY_AC_HOME = SDL_SCANCODE_AC_HOME;
        int const Keyboard::KEY_AC_REFRESH = SDL_SCANCODE_AC_REFRESH;
        int const Keyboard::KEY_AC_SEARCH = SDL_SCANCODE_AC_SEARCH;
        int const Keyboard::KEY_AC_STOP = SDL_SCANCODE_AC_STOP;
        int const Keyboard::KEY_AGAIN = SDL_SCANCODE_AGAIN;
        int const Keyboard::KEY_ALTERASE = SDL_SCANCODE_ALTERASE;
        int const Keyboard::KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE;
        int const Keyboard::KEY_APPLICATION = SDL_SCANCODE_APPLICATION;
        int const Keyboard::KEY_AUDIOMUTE = SDL_SCANCODE_AUDIOMUTE;
        int const Keyboard::KEY_AUDIONEXT = SDL_SCANCODE_AUDIONEXT;
        int const Keyboard::KEY_AUDIOPLAY = SDL_SCANCODE_AUDIOPLAY;
        int const Keyboard::KEY_AUDIOPREV = SDL_SCANCODE_AUDIOPREV;
        int const Keyboard::KEY_AUDIOSTOP = SDL_SCANCODE_AUDIOSTOP;
        int const Keyboard::KEY_B = SDL_SCANCODE_B;
        int const Keyboard::KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH;
        int const Keyboard::KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE;
        int const Keyboard::KEY_BRIGHTNESSDOWN = SDL_SCANCODE_BRIGHTNESSDOWN;
        int const Keyboard::KEY_BRIGHTNESSUP = SDL_SCANCODE_BRIGHTNESSUP;
        int const Keyboard::KEY_C = SDL_SCANCODE_C;
        int const Keyboard::KEY_CALCULATOR = SDL_SCANCODE_CALCULATOR;
        int const Keyboard::KEY_CANCEL = SDL_SCANCODE_CANCEL;
        int const Keyboard::KEY_CAPSLOCK = SDL_SCANCODE_CAPSLOCK;
        int const Keyboard::KEY_CLEAR = SDL_SCANCODE_CLEAR;
        int const Keyboard::KEY_CLEARAGAIN = SDL_SCANCODE_CLEARAGAIN;
        int const Keyboard::KEY_COMMA = SDL_SCANCODE_COMMA;
        int const Keyboard::KEY_COMPUTER = SDL_SCANCODE_COMPUTER;
        int const Keyboard::KEY_COPY = SDL_SCANCODE_COPY;
        int const Keyboard::KEY_CRSEL = SDL_SCANCODE_CRSEL;
        int const Keyboard::KEY_CURRENCYSUBUNIT = SDL_SCANCODE_CURRENCYSUBUNIT;
        int const Keyboard::KEY_CURRENCYUNIT = SDL_SCANCODE_CURRENCYUNIT;
        int const Keyboard::KEY_CUT = SDL_SCANCODE_CUT;
        int const Keyboard::KEY_D = SDL_SCANCODE_D;
        int const Keyboard::KEY_DECIMALSEPARATOR = SDL_SCANCODE_DECIMALSEPARATOR;
        int const Keyboard::KEY_DELETE = SDL_SCANCODE_DELETE;
        int const Keyboard::KEY_DISPLAYSWITCH = SDL_SCANCODE_DISPLAYSWITCH;
        int const Keyboard::KEY_DOWN = SDL_SCANCODE_DOWN;
        int const Keyboard::KEY_E = SDL_SCANCODE_E;
        int const Keyboard::KEY_EJECT = SDL_SCANCODE_EJECT;
        int const Keyboard::KEY_END = SDL_SCANCODE_END;
        int const Keyboard::KEY_EQUALS = SDL_SCANCODE_EQUALS;
        int const Keyboard::KEY_ESCAPE = SDL_SCANCODE_ESCAPE;
        int const Keyboard::KEY_EXECUTE = SDL_SCANCODE_EXECUTE;
        int const Keyboard::KEY_EXSEL = SDL_SCANCODE_EXSEL;
        int const Keyboard::KEY_F = SDL_SCANCODE_F;
        int const Keyboard::KEY_F1 = SDL_SCANCODE_F1;
        int const Keyboard::KEY_F10 = SDL_SCANCODE_F10;
        int const Keyboard::KEY_F11 = SDL_SCANCODE_F11;
        int const Keyboard::KEY_F12 = SDL_SCANCODE_F12;
        int const Keyboard::KEY_F13 = SDL_SCANCODE_F13;
        int const Keyboard::KEY_F14 = SDL_SCANCODE_F14;
        int const Keyboard::KEY_F15 = SDL_SCANCODE_F15;
        int const Keyboard::KEY_F16 = SDL_SCANCODE_F16;
        int const Keyboard::KEY_F17 = SDL_SCANCODE_F17;
        int const Keyboard::KEY_F18 = SDL_SCANCODE_F18;
        int const Keyboard::KEY_F19 = SDL_SCANCODE_F19;
        int const Keyboard::KEY_F2 = SDL_SCANCODE_F2;
        int const Keyboard::KEY_F20 = SDL_SCANCODE_F20;
        int const Keyboard::KEY_F21 = SDL_SCANCODE_F21;
        int const Keyboard::KEY_F22 = SDL_SCANCODE_F22;
        int const Keyboard::KEY_F23 = SDL_SCANCODE_F23;
        int const Keyboard::KEY_F24 = SDL_SCANCODE_F24;
        int const Keyboard::KEY_F3 = SDL_SCANCODE_F3;
        int const Keyboard::KEY_F4 = SDL_SCANCODE_F4;
        int const Keyboard::KEY_F5 = SDL_SCANCODE_F5;
        int const Keyboard::KEY_F6 = SDL_SCANCODE_F6;
        int const Keyboard::KEY_F7 = SDL_SCANCODE_F7;
        int const Keyboard::KEY_F8 = SDL_SCANCODE_F8;
        int const Keyboard::KEY_F9 = SDL_SCANCODE_F9;
        int const Keyboard::KEY_FIND = SDL_SCANCODE_FIND;
        int const Keyboard::KEY_G = SDL_SCANCODE_G;
        int const Keyboard::KEY_GRAVE = SDL_SCANCODE_GRAVE;
        int const Keyboard::KEY_H = SDL_SCANCODE_H;
        int const Keyboard::KEY_HELP = SDL_SCANCODE_HELP;
        int const Keyboard::KEY_HOME = SDL_SCANCODE_HOME;
        int const Keyboard::KEY_I = SDL_SCANCODE_I;
        int const Keyboard::KEY_INSERT = SDL_SCANCODE_INSERT;
        int const Keyboard::KEY_J = SDL_SCANCODE_J;
        int const Keyboard::KEY_K = SDL_SCANCODE_K;
        int const Keyboard::KEY_KBDILLUMDOWN = SDL_SCANCODE_KBDILLUMDOWN;
        int const Keyboard::KEY_KBDILLUMTOGGLE = SDL_SCANCODE_KBDILLUMTOGGLE;
        int const Keyboard::KEY_KBDILLUMUP = SDL_SCANCODE_KBDILLUMUP;
        int const Keyboard::KEY_KP_0 = SDL_SCANCODE_KP_0;
        int const Keyboard::KEY_KP_00 = SDL_SCANCODE_KP_00;
        int const Keyboard::KEY_KP_000 = SDL_SCANCODE_KP_000;
        int const Keyboard::KEY_KP_1 = SDL_SCANCODE_KP_1;
        int const Keyboard::KEY_KP_2 = SDL_SCANCODE_KP_2;
        int const Keyboard::KEY_KP_3 = SDL_SCANCODE_KP_3;
        int const Keyboard::KEY_KP_4 = SDL_SCANCODE_KP_4;
        int const Keyboard::KEY_KP_5 = SDL_SCANCODE_KP_5;
        int const Keyboard::KEY_KP_6 = SDL_SCANCODE_KP_6;
        int const Keyboard::KEY_KP_7 = SDL_SCANCODE_KP_7;
        int const Keyboard::KEY_KP_8 = SDL_SCANCODE_KP_8;
        int const Keyboard::KEY_KP_9 = SDL_SCANCODE_KP_9;
        int const Keyboard::KEY_KP_A = SDL_SCANCODE_KP_A;
        int const Keyboard::KEY_KP_AMPERSAND = SDL_SCANCODE_KP_AMPERSAND;
        int const Keyboard::KEY_KP_AT = SDL_SCANCODE_KP_AT;
        int const Keyboard::KEY_KP_B = SDL_SCANCODE_KP_B;
        int const Keyboard::KEY_KP_BACKSPACE = SDL_SCANCODE_KP_BACKSPACE;
        int const Keyboard::KEY_KP_BINARY = SDL_SCANCODE_KP_BINARY;
        int const Keyboard::KEY_KP_C = SDL_SCANCODE_KP_C;
        int const Keyboard::KEY_KP_CLEAR = SDL_SCANCODE_KP_CLEAR;
        int const Keyboard::KEY_KP_CLEARENTRY = SDL_SCANCODE_KP_CLEARENTRY;
        int const Keyboard::KEY_KP_COLON = SDL_SCANCODE_KP_COLON;
        int const Keyboard::KEY_KP_COMMA = SDL_SCANCODE_KP_COMMA;
        int const Keyboard::KEY_KP_D = SDL_SCANCODE_KP_D;
        int const Keyboard::KEY_KP_DBLVERTICALBAR = SDL_SCANCODE_KP_DBLVERTICALBAR;
        int const Keyboard::KEY_KP_DECIMAL = SDL_SCANCODE_KP_DECIMAL;
        int const Keyboard::KEY_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE;
        int const Keyboard::KEY_KP_E = SDL_SCANCODE_KP_E;
        int const Keyboard::KEY_KP_ENTER = SDL_SCANCODE_KP_ENTER;
        int const Keyboard::KEY_KP_EQUALS = SDL_SCANCODE_KP_EQUALS;
        int const Keyboard::KEY_KP_EQUALSAS400 = SDL_SCANCODE_KP_EQUALSAS400;
        int const Keyboard::KEY_KP_EXCLAM = SDL_SCANCODE_KP_EXCLAM;
        int const Keyboard::KEY_KP_F = SDL_SCANCODE_KP_F;
        int const Keyboard::KEY_KP_GREATER = SDL_SCANCODE_KP_GREATER;
        int const Keyboard::KEY_KP_HASH = SDL_SCANCODE_KP_HASH;
        int const Keyboard::KEY_KP_HEXADECIMAL = SDL_SCANCODE_KP_HEXADECIMAL;
        int const Keyboard::KEY_KP_LEFTBRACE = SDL_SCANCODE_KP_LEFTBRACE;
        int const Keyboard::KEY_KP_LEFTPAREN = SDL_SCANCODE_KP_LEFTPAREN;
        int const Keyboard::KEY_KP_LESS = SDL_SCANCODE_KP_LESS;
        int const Keyboard::KEY_KP_MEMADD = SDL_SCANCODE_KP_MEMADD;
        int const Keyboard::KEY_KP_MEMCLEAR = SDL_SCANCODE_KP_MEMCLEAR;
        int const Keyboard::KEY_KP_MEMDIVIDE = SDL_SCANCODE_KP_MEMDIVIDE;
        int const Keyboard::KEY_KP_MEMMULTIPLY = SDL_SCANCODE_KP_MEMMULTIPLY;
        int const Keyboard::KEY_KP_MEMRECALL = SDL_SCANCODE_KP_MEMRECALL;
        int const Keyboard::KEY_KP_MEMSTORE = SDL_SCANCODE_KP_MEMSTORE;
        int const Keyboard::KEY_KP_MEMSUBTRACT = SDL_SCANCODE_KP_MEMSUBTRACT;
        int const Keyboard::KEY_KP_MINUS = SDL_SCANCODE_KP_MINUS;
        int const Keyboard::KEY_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY;
        int const Keyboard::KEY_KP_OCTAL = SDL_SCANCODE_KP_OCTAL;
        int const Keyboard::KEY_KP_PERCENT = SDL_SCANCODE_KP_PERCENT;
        int const Keyboard::KEY_KP_PERIOD = SDL_SCANCODE_KP_PERIOD;
        int const Keyboard::KEY_KP_PLUS = SDL_SCANCODE_KP_PLUS;
        int const Keyboard::KEY_KP_PLUSMINUS = SDL_SCANCODE_KP_PLUSMINUS;
        int const Keyboard::KEY_KP_POWER = SDL_SCANCODE_KP_POWER;
        int const Keyboard::KEY_KP_RIGHTBRACE = SDL_SCANCODE_KP_RIGHTBRACE;
        int const Keyboard::KEY_KP_RIGHTPAREN = SDL_SCANCODE_KP_RIGHTPAREN;
        int const Keyboard::KEY_KP_SPACE = SDL_SCANCODE_KP_SPACE;
        int const Keyboard::KEY_KP_TAB = SDL_SCANCODE_KP_TAB;
        int const Keyboard::KEY_KP_VERTICALBAR = SDL_SCANCODE_KP_VERTICALBAR;
        int const Keyboard::KEY_KP_XOR = SDL_SCANCODE_KP_XOR;
        int const Keyboard::KEY_L = SDL_SCANCODE_L;
        int const Keyboard::KEY_LALT = SDL_SCANCODE_LALT;
        int const Keyboard::KEY_LCTRL = SDL_SCANCODE_LCTRL;
        int const Keyboard::KEY_LEFT = SDL_SCANCODE_LEFT;
        int const Keyboard::KEY_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET;
        int const Keyboard::KEY_LGUI = SDL_SCANCODE_LGUI;
        int const Keyboard::KEY_LSHIFT = SDL_SCANCODE_LSHIFT;
        int const Keyboard::KEY_M = SDL_SCANCODE_M;
        int const Keyboard::KEY_MAIL = SDL_SCANCODE_MAIL;
        int const Keyboard::KEY_MEDIASELECT = SDL_SCANCODE_MEDIASELECT;
        int const Keyboard::KEY_MENU = SDL_SCANCODE_MENU;
        int const Keyboard::KEY_MINUS = SDL_SCANCODE_MINUS;
        int const Keyboard::KEY_MODE = SDL_SCANCODE_MODE;
        int const Keyboard::KEY_MUTE = SDL_SCANCODE_MUTE;
        int const Keyboard::KEY_N = SDL_SCANCODE_N;
        int const Keyboard::KEY_NUMLOCKCLEAR = SDL_SCANCODE_NUMLOCKCLEAR;
        int const Keyboard::KEY_O = SDL_SCANCODE_O;
        int const Keyboard::KEY_OPER = SDL_SCANCODE_OPER;
        int const Keyboard::KEY_OUT = SDL_SCANCODE_OUT;
        int const Keyboard::KEY_P = SDL_SCANCODE_P;
        int const Keyboard::KEY_PAGEDOWN = SDL_SCANCODE_PAGEDOWN;
        int const Keyboard::KEY_PAGEUP = SDL_SCANCODE_PAGEUP;
        int const Keyboard::KEY_PASTE = SDL_SCANCODE_PASTE;
        int const Keyboard::KEY_PAUSE = SDL_SCANCODE_PAUSE;
        int const Keyboard::KEY_PERIOD = SDL_SCANCODE_PERIOD;
        int const Keyboard::KEY_POWER = SDL_SCANCODE_POWER;
        int const Keyboard::KEY_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN;
        int const Keyboard::KEY_PRIOR = SDL_SCANCODE_PRIOR;
        int const Keyboard::KEY_Q = SDL_SCANCODE_Q;
        int const Keyboard::KEY_R = SDL_SCANCODE_R;
        int const Keyboard::KEY_RALT = SDL_SCANCODE_RALT;
        int const Keyboard::KEY_RCTRL = SDL_SCANCODE_RCTRL;
        int const Keyboard::KEY_RETURN = SDL_SCANCODE_RETURN;
        int const Keyboard::KEY_RETURN2 = SDL_SCANCODE_RETURN2;
        int const Keyboard::KEY_RGUI = SDL_SCANCODE_RGUI;
        int const Keyboard::KEY_RIGHT = SDL_SCANCODE_RIGHT;
        int const Keyboard::KEY_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET;
        int const Keyboard::KEY_RSHIFT = SDL_SCANCODE_RSHIFT;
        int const Keyboard::KEY_S = SDL_SCANCODE_S;
        int const Keyboard::KEY_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK;
        int const Keyboard::KEY_SELECT = SDL_SCANCODE_SELECT;
        int const Keyboard::KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON;
        int const Keyboard::KEY_SEPARATOR = SDL_SCANCODE_SEPARATOR;
        int const Keyboard::KEY_SLASH = SDL_SCANCODE_SLASH;
        int const Keyboard::KEY_SLEEP = SDL_SCANCODE_SLEEP;
        int const Keyboard::KEY_SPACE = SDL_SCANCODE_SPACE;
        int const Keyboard::KEY_STOP = SDL_SCANCODE_STOP;
        int const Keyboard::KEY_SYSREQ = SDL_SCANCODE_SYSREQ;
        int const Keyboard::KEY_T = SDL_SCANCODE_T;
        int const Keyboard::KEY_TAB = SDL_SCANCODE_TAB;
        int const Keyboard::KEY_THOUSANDSSEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR;
        int const Keyboard::KEY_U = SDL_SCANCODE_U;
        int const Keyboard::KEY_UNDO = SDL_SCANCODE_UNDO;
        int const Keyboard::KEY_UNKNOWN = SDL_SCANCODE_UNKNOWN;
        int const Keyboard::KEY_UP = SDL_SCANCODE_UP;
        int const Keyboard::KEY_V = SDL_SCANCODE_V;
        int const Keyboard::KEY_VOLUMEDOWN = SDL_SCANCODE_VOLUMEDOWN;
        int const Keyboard::KEY_VOLUMEUP = SDL_SCANCODE_VOLUMEUP;
        int const Keyboard::KEY_W = SDL_SCANCODE_W;
        int const Keyboard::KEY_WWW = SDL_SCANCODE_WWW;
        int const Keyboard::KEY_X = SDL_SCANCODE_X;
        int const Keyboard::KEY_Y = SDL_SCANCODE_Y;
        int const Keyboard::KEY_Z = SDL_SCANCODE_Z;
        int const Keyboard::KEY_INTERNATIONAL1 = SDL_SCANCODE_INTERNATIONAL1;
        int const Keyboard::KEY_INTERNATIONAL2 = SDL_SCANCODE_INTERNATIONAL2;
        int const Keyboard::KEY_INTERNATIONAL3 = SDL_SCANCODE_INTERNATIONAL3;
        int const Keyboard::KEY_INTERNATIONAL4 = SDL_SCANCODE_INTERNATIONAL4;
        int const Keyboard::KEY_INTERNATIONAL5 = SDL_SCANCODE_INTERNATIONAL5;
        int const Keyboard::KEY_INTERNATIONAL6 = SDL_SCANCODE_INTERNATIONAL6;
        int const Keyboard::KEY_INTERNATIONAL7 = SDL_SCANCODE_INTERNATIONAL7;
        int const Keyboard::KEY_INTERNATIONAL8 = SDL_SCANCODE_INTERNATIONAL8;
        int const Keyboard::KEY_INTERNATIONAL9 = SDL_SCANCODE_INTERNATIONAL9;
        int const Keyboard::KEY_LANG1 = SDL_SCANCODE_LANG1;
        int const Keyboard::KEY_LANG2 = SDL_SCANCODE_LANG2;
        int const Keyboard::KEY_LANG3 = SDL_SCANCODE_LANG3;
        int const Keyboard::KEY_LANG4 = SDL_SCANCODE_LANG4;
        int const Keyboard::KEY_LANG5 = SDL_SCANCODE_LANG5;
        int const Keyboard::KEY_LANG6 = SDL_SCANCODE_LANG6;
        int const Keyboard::KEY_LANG7 = SDL_SCANCODE_LANG7;
        int const Keyboard::KEY_LANG8 = SDL_SCANCODE_LANG8;
        int const Keyboard::KEY_LANG9 = SDL_SCANCODE_LANG9;
        int const Keyboard::KEY_NONUSBACKSLASH = SDL_SCANCODE_NONUSBACKSLASH;
    }
}
