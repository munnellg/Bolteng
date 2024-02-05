#ifndef DEFINES_H
#define DEFINES_H

#include <cstdint>
#include <entt/entt.hpp>

namespace bolt {
    namespace input {
            typedef uint32_t ScanCode;
            typedef uint32_t PlatformCode;
            typedef uint32_t ButtonCode;
            typedef uint32_t AxisCode;
            typedef uint32_t GamePadEventCode;

            entt::entity const UNBOUND_ENTITY = (entt::entity) 0xFFFFFFFF;

            int const MAX_GAME_PADS = 4;

            // These values are platform dependent
            // They will be defined in the subsystems module on a per-platform basis
            
            // ===============================================================
            // Platform Signal Codes
            // ===============================================================

            extern PlatformCode const PLATFORM_QUIT;

            // ===============================================================
            // Game Controller 
            // ===============================================================
            extern GamePadEventCode const GAME_PAD_CONNECT_EVENT;
            extern GamePadEventCode const GAME_PAD_DISCONNECT_EVENT;

            extern AxisCode const AXIS_LEFT_X;
            extern AxisCode const AXIS_LEFT_Y;
            extern AxisCode const AXIS_RIGHT_X;
            extern AxisCode const AXIS_RIGHT_Y;
            extern AxisCode const AXIS_TRIGGER_LEFT;
            extern AxisCode const AXIS_TRIGGER_RIGHT;
            extern AxisCode const AXIS_MAX;

            extern ButtonCode const BUTTON_INVALID;
            extern ButtonCode const BUTTON_A;
            extern ButtonCode const BUTTON_B;
            extern ButtonCode const BUTTON_X;
            extern ButtonCode const BUTTON_Y;
            extern ButtonCode const BUTTON_BACK;
            extern ButtonCode const BUTTON_GUIDE;
            extern ButtonCode const BUTTON_START;
            extern ButtonCode const BUTTON_LEFT_STICK;
            extern ButtonCode const BUTTON_RIGHT_STICK;
            extern ButtonCode const BUTTON_LEFT_SHOULDER;
            extern ButtonCode const BUTTON_RIGHT_SHOULDER;
            extern ButtonCode const BUTTON_DPAD_UP;
            extern ButtonCode const BUTTON_DPAD_DOWN;
            extern ButtonCode const BUTTON_DPAD_LEFT;
            extern ButtonCode const BUTTON_DPAD_RIGHT;
            extern ButtonCode const BUTTON_MAX;

            // ===============================================================
            // Keyboard
            // ===============================================================
            extern ScanCode const KEY_0;
            extern ScanCode const KEY_1;
            extern ScanCode const KEY_2;
            extern ScanCode const KEY_3;
            extern ScanCode const KEY_4;
            extern ScanCode const KEY_5;
            extern ScanCode const KEY_6;
            extern ScanCode const KEY_7;
            extern ScanCode const KEY_8;
            extern ScanCode const KEY_9;
            extern ScanCode const KEY_A;
            extern ScanCode const KEY_AC_BACK;
            extern ScanCode const KEY_AC_BOOKMARKS;
            extern ScanCode const KEY_AC_FORWARD;
            extern ScanCode const KEY_KP_DBLAMPERSAND;
            extern ScanCode const KEY_AC_HOME;
            extern ScanCode const KEY_AC_REFRESH;
            extern ScanCode const KEY_AC_SEARCH;
            extern ScanCode const KEY_AC_STOP;
            extern ScanCode const KEY_AGAIN;
            extern ScanCode const KEY_ALTERASE;
            extern ScanCode const KEY_APOSTROPHE;
            extern ScanCode const KEY_APPLICATION;
            extern ScanCode const KEY_AUDIOMUTE;
            extern ScanCode const KEY_AUDIONEXT;
            extern ScanCode const KEY_AUDIOPLAY;
            extern ScanCode const KEY_AUDIOPREV;
            extern ScanCode const KEY_AUDIOSTOP;
            extern ScanCode const KEY_B;
            extern ScanCode const KEY_BACKSLASH;
            extern ScanCode const KEY_BACKSPACE;
            extern ScanCode const KEY_BRIGHTNESSDOWN;
            extern ScanCode const KEY_BRIGHTNESSUP;
            extern ScanCode const KEY_C;
            extern ScanCode const KEY_CALCULATOR;
            extern ScanCode const KEY_CANCEL;
            extern ScanCode const KEY_CAPSLOCK;
            extern ScanCode const KEY_CLEAR;
            extern ScanCode const KEY_CLEARAGAIN;
            extern ScanCode const KEY_COMMA;
            extern ScanCode const KEY_COMPUTER;
            extern ScanCode const KEY_COPY;
            extern ScanCode const KEY_CRSEL;
            extern ScanCode const KEY_CURRENCYSUBUNIT;
            extern ScanCode const KEY_CURRENCYUNIT;
            extern ScanCode const KEY_CUT;
            extern ScanCode const KEY_D;
            extern ScanCode const KEY_DECIMALSEPARATOR;
            extern ScanCode const KEY_DELETE;
            extern ScanCode const KEY_DISPLAYSWITCH;
            extern ScanCode const KEY_DOWN;
            extern ScanCode const KEY_E;
            extern ScanCode const KEY_EJECT;
            extern ScanCode const KEY_END;
            extern ScanCode const KEY_EQUALS;
            extern ScanCode const KEY_ESCAPE;
            extern ScanCode const KEY_EXECUTE;
            extern ScanCode const KEY_EXSEL;
            extern ScanCode const KEY_F;
            extern ScanCode const KEY_F1;
            extern ScanCode const KEY_F10;
            extern ScanCode const KEY_F11;
            extern ScanCode const KEY_F12;
            extern ScanCode const KEY_F13;
            extern ScanCode const KEY_F14;
            extern ScanCode const KEY_F15;
            extern ScanCode const KEY_F16;
            extern ScanCode const KEY_F17;
            extern ScanCode const KEY_F18;
            extern ScanCode const KEY_F19;
            extern ScanCode const KEY_F2;
            extern ScanCode const KEY_F20;
            extern ScanCode const KEY_F21;
            extern ScanCode const KEY_F22;
            extern ScanCode const KEY_F23;
            extern ScanCode const KEY_F24;
            extern ScanCode const KEY_F3;
            extern ScanCode const KEY_F4;
            extern ScanCode const KEY_F5;
            extern ScanCode const KEY_F6;
            extern ScanCode const KEY_F7;
            extern ScanCode const KEY_F8;
            extern ScanCode const KEY_F9;
            extern ScanCode const KEY_FIND;
            extern ScanCode const KEY_G;
            extern ScanCode const KEY_GRAVE;
            extern ScanCode const KEY_H;
            extern ScanCode const KEY_HELP;
            extern ScanCode const KEY_HOME;
            extern ScanCode const KEY_I;
            extern ScanCode const KEY_INSERT;
            extern ScanCode const KEY_J;
            extern ScanCode const KEY_K;
            extern ScanCode const KEY_KBDILLUMDOWN;
            extern ScanCode const KEY_KBDILLUMTOGGLE;
            extern ScanCode const KEY_KBDILLUMUP;
            extern ScanCode const KEY_KP_0;
            extern ScanCode const KEY_KP_00;
            extern ScanCode const KEY_KP_000;
            extern ScanCode const KEY_KP_1;
            extern ScanCode const KEY_KP_2;
            extern ScanCode const KEY_KP_3;
            extern ScanCode const KEY_KP_4;
            extern ScanCode const KEY_KP_5;
            extern ScanCode const KEY_KP_6;
            extern ScanCode const KEY_KP_7;
            extern ScanCode const KEY_KP_8;
            extern ScanCode const KEY_KP_9;
            extern ScanCode const KEY_KP_A;
            extern ScanCode const KEY_KP_AMPERSAND;
            extern ScanCode const KEY_KP_AT;
            extern ScanCode const KEY_KP_B;
            extern ScanCode const KEY_KP_BACKSPACE;
            extern ScanCode const KEY_KP_BINARY;
            extern ScanCode const KEY_KP_C;
            extern ScanCode const KEY_KP_CLEAR;
            extern ScanCode const KEY_KP_CLEARENTRY;
            extern ScanCode const KEY_KP_COLON;
            extern ScanCode const KEY_KP_COMMA;
            extern ScanCode const KEY_KP_D;
            extern ScanCode const KEY_KP_DBLVERTICALBAR;
            extern ScanCode const KEY_KP_DECIMAL;
            extern ScanCode const KEY_KP_DIVIDE;
            extern ScanCode const KEY_KP_E;
            extern ScanCode const KEY_KP_ENTER;
            extern ScanCode const KEY_KP_EQUALS;
            extern ScanCode const KEY_KP_EQUALSAS400;
            extern ScanCode const KEY_KP_EXCLAM;
            extern ScanCode const KEY_KP_F;
            extern ScanCode const KEY_KP_GREATER;
            extern ScanCode const KEY_KP_HASH;
            extern ScanCode const KEY_KP_HEXADECIMAL;
            extern ScanCode const KEY_KP_LEFTBRACE;
            extern ScanCode const KEY_KP_LEFTPAREN;
            extern ScanCode const KEY_KP_LESS;
            extern ScanCode const KEY_KP_MEMADD;
            extern ScanCode const KEY_KP_MEMCLEAR;
            extern ScanCode const KEY_KP_MEMDIVIDE;
            extern ScanCode const KEY_KP_MEMMULTIPLY;
            extern ScanCode const KEY_KP_MEMRECALL;
            extern ScanCode const KEY_KP_MEMSTORE;
            extern ScanCode const KEY_KP_MEMSUBTRACT;
            extern ScanCode const KEY_KP_MINUS;
            extern ScanCode const KEY_KP_MULTIPLY;
            extern ScanCode const KEY_KP_OCTAL;
            extern ScanCode const KEY_KP_PERCENT;
            extern ScanCode const KEY_KP_PERIOD;
            extern ScanCode const KEY_KP_PLUS;
            extern ScanCode const KEY_KP_PLUSMINUS;
            extern ScanCode const KEY_KP_POWER;
            extern ScanCode const KEY_KP_RIGHTBRACE;
            extern ScanCode const KEY_KP_RIGHTPAREN;
            extern ScanCode const KEY_KP_SPACE;
            extern ScanCode const KEY_KP_TAB;
            extern ScanCode const KEY_KP_VERTICALBAR;
            extern ScanCode const KEY_KP_XOR;
            extern ScanCode const KEY_L;
            extern ScanCode const KEY_LALT;
            extern ScanCode const KEY_LCTRL;
            extern ScanCode const KEY_LEFT;
            extern ScanCode const KEY_LEFTBRACKET;
            extern ScanCode const KEY_LGUI;
            extern ScanCode const KEY_LSHIFT;
            extern ScanCode const KEY_M;
            extern ScanCode const KEY_MAIL;
            extern ScanCode const KEY_MEDIASELECT;
            extern ScanCode const KEY_MENU;
            extern ScanCode const KEY_MINUS;
            extern ScanCode const KEY_MODE;
            extern ScanCode const KEY_MUTE;
            extern ScanCode const KEY_N;
            extern ScanCode const KEY_NUMLOCKCLEAR;
            extern ScanCode const KEY_O;
            extern ScanCode const KEY_OPER;
            extern ScanCode const KEY_OUT;
            extern ScanCode const KEY_P;
            extern ScanCode const KEY_PAGEDOWN;
            extern ScanCode const KEY_PAGEUP;
            extern ScanCode const KEY_PASTE;
            extern ScanCode const KEY_PAUSE;
            extern ScanCode const KEY_PERIOD;
            extern ScanCode const KEY_POWER;
            extern ScanCode const KEY_PRINTSCREEN;
            extern ScanCode const KEY_PRIOR;
            extern ScanCode const KEY_Q;
            extern ScanCode const KEY_R;
            extern ScanCode const KEY_RALT;
            extern ScanCode const KEY_RCTRL;
            extern ScanCode const KEY_RETURN;
            extern ScanCode const KEY_RETURN2;
            extern ScanCode const KEY_RGUI;
            extern ScanCode const KEY_RIGHT;
            extern ScanCode const KEY_RIGHTBRACKET;
            extern ScanCode const KEY_RSHIFT;
            extern ScanCode const KEY_S;
            extern ScanCode const KEY_SCROLLLOCK;
            extern ScanCode const KEY_SELECT;
            extern ScanCode const KEY_SEMICOLON;
            extern ScanCode const KEY_SEPARATOR;
            extern ScanCode const KEY_SLASH;
            extern ScanCode const KEY_SLEEP;
            extern ScanCode const KEY_SPACE;
            extern ScanCode const KEY_STOP;
            extern ScanCode const KEY_SYSREQ;
            extern ScanCode const KEY_T;
            extern ScanCode const KEY_TAB;
            extern ScanCode const KEY_THOUSANDSSEPARATOR;
            extern ScanCode const KEY_U;
            extern ScanCode const KEY_UNDO;
            extern ScanCode const KEY_UNKNOWN;
            extern ScanCode const KEY_UP;
            extern ScanCode const KEY_V;
            extern ScanCode const KEY_VOLUMEDOWN;
            extern ScanCode const KEY_VOLUMEUP;
            extern ScanCode const KEY_W;
            extern ScanCode const KEY_WWW;
            extern ScanCode const KEY_X;
            extern ScanCode const KEY_Y;
            extern ScanCode const KEY_Z;
            extern ScanCode const KEY_INTERNATIONAL1;
            extern ScanCode const KEY_INTERNATIONAL2;
            extern ScanCode const KEY_INTERNATIONAL3;
            extern ScanCode const KEY_INTERNATIONAL4;
            extern ScanCode const KEY_INTERNATIONAL5;
            extern ScanCode const KEY_INTERNATIONAL6;
            extern ScanCode const KEY_INTERNATIONAL7;
            extern ScanCode const KEY_INTERNATIONAL8;
            extern ScanCode const KEY_INTERNATIONAL9;
            extern ScanCode const KEY_LANG1;
            extern ScanCode const KEY_LANG2;
            extern ScanCode const KEY_LANG3;
            extern ScanCode const KEY_LANG4;
            extern ScanCode const KEY_LANG5;
            extern ScanCode const KEY_LANG6;
            extern ScanCode const KEY_LANG7;
            extern ScanCode const KEY_LANG8;
            extern ScanCode const KEY_LANG9;
            extern ScanCode const KEY_NONUSBACKSLASH;
    }
}

#endif // DEFINES_H
