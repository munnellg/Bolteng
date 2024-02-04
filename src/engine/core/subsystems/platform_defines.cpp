#include "../defines.h"

#include <SDL2/SDL.h>

namespace bolt {
    namespace input {
        // Map SDL's keycodes to Bolt's keycodes for the SDL build
        PlatformCode const PLATFORM_QUIT = SDL_QUIT;

        ControllerEventCode const CONTROLLER_CONNECT_EVENT    = SDL_CONTROLLERDEVICEADDED;
        ControllerEventCode const CONTROLLER_DISCONNECT_EVENT = SDL_CONTROLLERDEVICEREMOVED;

        AxisCode const AXIS_LEFT_X        = SDL_CONTROLLER_AXIS_LEFTX;
        AxisCode const AXIS_LEFT_Y        = SDL_CONTROLLER_AXIS_LEFTY;
        AxisCode const AXIS_RIGHT_X       = SDL_CONTROLLER_AXIS_RIGHTX;
        AxisCode const AXIS_RIGHT_Y       = SDL_CONTROLLER_AXIS_RIGHTY;
        AxisCode const AXIS_TRIGGER_LEFT  = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
        AxisCode const AXIS_TRIGGER_RIGHT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
        AxisCode const AXIS_MAX           = SDL_CONTROLLER_AXIS_MAX;

        ButtonCode const BUTTON_INVALID        = SDL_CONTROLLER_BUTTON_INVALID;
        ButtonCode const BUTTON_A              = SDL_CONTROLLER_BUTTON_A;
        ButtonCode const BUTTON_B              = SDL_CONTROLLER_BUTTON_B;
        ButtonCode const BUTTON_X              = SDL_CONTROLLER_BUTTON_X;
        ButtonCode const BUTTON_Y              = SDL_CONTROLLER_BUTTON_Y;
        ButtonCode const BUTTON_BACK           = SDL_CONTROLLER_BUTTON_BACK;
        ButtonCode const BUTTON_GUIDE          = SDL_CONTROLLER_BUTTON_GUIDE;
        ButtonCode const BUTTON_START          = SDL_CONTROLLER_BUTTON_START;
        ButtonCode const BUTTON_LEFT_STICK     = SDL_CONTROLLER_BUTTON_LEFTSTICK;
        ButtonCode const BUTTON_RIGHT_STICK    = SDL_CONTROLLER_BUTTON_RIGHTSTICK;
        ButtonCode const BUTTON_LEFT_SHOULDER  = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
        ButtonCode const BUTTON_RIGHT_SHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
        ButtonCode const BUTTON_DPAD_UP        = SDL_CONTROLLER_BUTTON_DPAD_UP;
        ButtonCode const BUTTON_DPAD_DOWN      = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
        ButtonCode const BUTTON_DPAD_LEFT      = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
        ButtonCode const BUTTON_DPAD_RIGHT     = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
        ButtonCode const BUTTON_MAX            = SDL_CONTROLLER_BUTTON_MAX;

        ScanCode const KEY_0 = SDL_SCANCODE_0;
        ScanCode const KEY_1 = SDL_SCANCODE_1;
        ScanCode const KEY_2 = SDL_SCANCODE_2;
        ScanCode const KEY_3 = SDL_SCANCODE_3;
        ScanCode const KEY_4 = SDL_SCANCODE_4;
        ScanCode const KEY_5 = SDL_SCANCODE_5;
        ScanCode const KEY_6 = SDL_SCANCODE_6;
        ScanCode const KEY_7 = SDL_SCANCODE_7;
        ScanCode const KEY_8 = SDL_SCANCODE_8;
        ScanCode const KEY_9 = SDL_SCANCODE_9;

        ScanCode const KEY_A = SDL_SCANCODE_A;
        ScanCode const KEY_B = SDL_SCANCODE_B;
        ScanCode const KEY_C = SDL_SCANCODE_C;
        ScanCode const KEY_D = SDL_SCANCODE_D;
        ScanCode const KEY_E = SDL_SCANCODE_E;
        ScanCode const KEY_F = SDL_SCANCODE_F;
        ScanCode const KEY_G = SDL_SCANCODE_G;
        ScanCode const KEY_H = SDL_SCANCODE_H;
        ScanCode const KEY_I = SDL_SCANCODE_I;
        ScanCode const KEY_J = SDL_SCANCODE_J;
        ScanCode const KEY_K = SDL_SCANCODE_K;
        ScanCode const KEY_L = SDL_SCANCODE_L;
        ScanCode const KEY_M = SDL_SCANCODE_M;
        ScanCode const KEY_N = SDL_SCANCODE_N;
        ScanCode const KEY_O = SDL_SCANCODE_O;
        ScanCode const KEY_P = SDL_SCANCODE_P;
        ScanCode const KEY_Q = SDL_SCANCODE_Q;
        ScanCode const KEY_R = SDL_SCANCODE_R;
        ScanCode const KEY_S = SDL_SCANCODE_S;
        ScanCode const KEY_T = SDL_SCANCODE_T;
        ScanCode const KEY_U = SDL_SCANCODE_U;
        ScanCode const KEY_V = SDL_SCANCODE_V;
        ScanCode const KEY_W = SDL_SCANCODE_W;
        ScanCode const KEY_X = SDL_SCANCODE_X;
        ScanCode const KEY_Y = SDL_SCANCODE_Y;
        ScanCode const KEY_Z = SDL_SCANCODE_Z;

        ScanCode const KEY_F1  = SDL_SCANCODE_F1;
        ScanCode const KEY_F2  = SDL_SCANCODE_F2;
        ScanCode const KEY_F3  = SDL_SCANCODE_F3;
        ScanCode const KEY_F4  = SDL_SCANCODE_F4;
        ScanCode const KEY_F5  = SDL_SCANCODE_F5;
        ScanCode const KEY_F6  = SDL_SCANCODE_F6;
        ScanCode const KEY_F7  = SDL_SCANCODE_F7;
        ScanCode const KEY_F8  = SDL_SCANCODE_F8;
        ScanCode const KEY_F9  = SDL_SCANCODE_F9;
        ScanCode const KEY_F10 = SDL_SCANCODE_F10;
        ScanCode const KEY_F11 = SDL_SCANCODE_F11;
        ScanCode const KEY_F12 = SDL_SCANCODE_F12;
        ScanCode const KEY_F13 = SDL_SCANCODE_F13;
        ScanCode const KEY_F14 = SDL_SCANCODE_F14;
        ScanCode const KEY_F15 = SDL_SCANCODE_F15;
        ScanCode const KEY_F16 = SDL_SCANCODE_F16;
        ScanCode const KEY_F17 = SDL_SCANCODE_F17;
        ScanCode const KEY_F18 = SDL_SCANCODE_F18;
        ScanCode const KEY_F19 = SDL_SCANCODE_F19;
        ScanCode const KEY_F20 = SDL_SCANCODE_F20;
        ScanCode const KEY_F21 = SDL_SCANCODE_F21;
        ScanCode const KEY_F22 = SDL_SCANCODE_F22;
        ScanCode const KEY_F23 = SDL_SCANCODE_F23;
        ScanCode const KEY_F24 = SDL_SCANCODE_F24;

        ScanCode const KEY_KP_0   = SDL_SCANCODE_KP_0;
        ScanCode const KEY_KP_00  = SDL_SCANCODE_KP_00;
        ScanCode const KEY_KP_000 = SDL_SCANCODE_KP_000;
        ScanCode const KEY_KP_1   = SDL_SCANCODE_KP_1;
        ScanCode const KEY_KP_2   = SDL_SCANCODE_KP_2;
        ScanCode const KEY_KP_3   = SDL_SCANCODE_KP_3;
        ScanCode const KEY_KP_4   = SDL_SCANCODE_KP_4;
        ScanCode const KEY_KP_5   = SDL_SCANCODE_KP_5;
        ScanCode const KEY_KP_6   = SDL_SCANCODE_KP_6;
        ScanCode const KEY_KP_7   = SDL_SCANCODE_KP_7;
        ScanCode const KEY_KP_8   = SDL_SCANCODE_KP_8;
        ScanCode const KEY_KP_9   = SDL_SCANCODE_KP_9;
        ScanCode const KEY_KP_A   = SDL_SCANCODE_KP_A;
        ScanCode const KEY_KP_B   = SDL_SCANCODE_KP_B;
        ScanCode const KEY_KP_C   = SDL_SCANCODE_KP_C;
        ScanCode const KEY_KP_D   = SDL_SCANCODE_KP_D;
        ScanCode const KEY_KP_E   = SDL_SCANCODE_KP_E;
        ScanCode const KEY_KP_F   = SDL_SCANCODE_KP_F;

        ScanCode const KEY_AC_BACK = SDL_SCANCODE_AC_BACK;
        ScanCode const KEY_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS;
        ScanCode const KEY_AC_FORWARD = SDL_SCANCODE_AC_FORWARD;
        ScanCode const KEY_KP_DBLAMPERSAND = SDL_SCANCODE_KP_DBLAMPERSAND;
        ScanCode const KEY_AC_HOME = SDL_SCANCODE_AC_HOME;
        ScanCode const KEY_AC_REFRESH = SDL_SCANCODE_AC_REFRESH;
        ScanCode const KEY_AC_SEARCH = SDL_SCANCODE_AC_SEARCH;
        ScanCode const KEY_AC_STOP = SDL_SCANCODE_AC_STOP;
        ScanCode const KEY_AGAIN = SDL_SCANCODE_AGAIN;
        ScanCode const KEY_ALTERASE = SDL_SCANCODE_ALTERASE;
        ScanCode const KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE;
        ScanCode const KEY_APPLICATION = SDL_SCANCODE_APPLICATION;
        ScanCode const KEY_AUDIOMUTE = SDL_SCANCODE_AUDIOMUTE;
        ScanCode const KEY_AUDIONEXT = SDL_SCANCODE_AUDIONEXT;
        ScanCode const KEY_AUDIOPLAY = SDL_SCANCODE_AUDIOPLAY;
        ScanCode const KEY_AUDIOPREV = SDL_SCANCODE_AUDIOPREV;
        ScanCode const KEY_AUDIOSTOP = SDL_SCANCODE_AUDIOSTOP;
        ScanCode const KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH;
        ScanCode const KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE;
        ScanCode const KEY_BRIGHTNESSDOWN = SDL_SCANCODE_BRIGHTNESSDOWN;
        ScanCode const KEY_BRIGHTNESSUP = SDL_SCANCODE_BRIGHTNESSUP;
        ScanCode const KEY_CALCULATOR = SDL_SCANCODE_CALCULATOR;
        ScanCode const KEY_CANCEL = SDL_SCANCODE_CANCEL;
        ScanCode const KEY_CAPSLOCK = SDL_SCANCODE_CAPSLOCK;
        ScanCode const KEY_CLEAR = SDL_SCANCODE_CLEAR;
        ScanCode const KEY_CLEARAGAIN = SDL_SCANCODE_CLEARAGAIN;
        ScanCode const KEY_COMMA = SDL_SCANCODE_COMMA;
        ScanCode const KEY_COMPUTER = SDL_SCANCODE_COMPUTER;
        ScanCode const KEY_COPY = SDL_SCANCODE_COPY;
        ScanCode const KEY_CRSEL = SDL_SCANCODE_CRSEL;
        ScanCode const KEY_CURRENCYSUBUNIT = SDL_SCANCODE_CURRENCYSUBUNIT;
        ScanCode const KEY_CURRENCYUNIT = SDL_SCANCODE_CURRENCYUNIT;
        ScanCode const KEY_CUT = SDL_SCANCODE_CUT;
        ScanCode const KEY_DECIMALSEPARATOR = SDL_SCANCODE_DECIMALSEPARATOR;
        ScanCode const KEY_DELETE = SDL_SCANCODE_DELETE;
        ScanCode const KEY_DISPLAYSWITCH = SDL_SCANCODE_DISPLAYSWITCH;
        ScanCode const KEY_DOWN = SDL_SCANCODE_DOWN;
        ScanCode const KEY_EJECT = SDL_SCANCODE_EJECT;
        ScanCode const KEY_END = SDL_SCANCODE_END;
        ScanCode const KEY_EQUALS = SDL_SCANCODE_EQUALS;
        ScanCode const KEY_ESCAPE = SDL_SCANCODE_ESCAPE;
        ScanCode const KEY_EXECUTE = SDL_SCANCODE_EXECUTE;
        ScanCode const KEY_EXSEL = SDL_SCANCODE_EXSEL;
        ScanCode const KEY_FIND = SDL_SCANCODE_FIND;
        ScanCode const KEY_GRAVE = SDL_SCANCODE_GRAVE;
        ScanCode const KEY_HELP = SDL_SCANCODE_HELP;
        ScanCode const KEY_HOME = SDL_SCANCODE_HOME;
        ScanCode const KEY_INSERT = SDL_SCANCODE_INSERT;
        ScanCode const KEY_KBDILLUMDOWN = SDL_SCANCODE_KBDILLUMDOWN;
        ScanCode const KEY_KBDILLUMTOGGLE = SDL_SCANCODE_KBDILLUMTOGGLE;
        ScanCode const KEY_KBDILLUMUP = SDL_SCANCODE_KBDILLUMUP;
        ScanCode const KEY_KP_AMPERSAND = SDL_SCANCODE_KP_AMPERSAND;
        ScanCode const KEY_KP_AT = SDL_SCANCODE_KP_AT;
        ScanCode const KEY_KP_BACKSPACE = SDL_SCANCODE_KP_BACKSPACE;
        ScanCode const KEY_KP_BINARY = SDL_SCANCODE_KP_BINARY;
        ScanCode const KEY_KP_CLEAR = SDL_SCANCODE_KP_CLEAR;
        ScanCode const KEY_KP_CLEARENTRY = SDL_SCANCODE_KP_CLEARENTRY;
        ScanCode const KEY_KP_COLON = SDL_SCANCODE_KP_COLON;
        ScanCode const KEY_KP_COMMA = SDL_SCANCODE_KP_COMMA;
        ScanCode const KEY_KP_DBLVERTICALBAR = SDL_SCANCODE_KP_DBLVERTICALBAR;
        ScanCode const KEY_KP_DECIMAL = SDL_SCANCODE_KP_DECIMAL;
        ScanCode const KEY_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE;
        ScanCode const KEY_KP_ENTER = SDL_SCANCODE_KP_ENTER;
        ScanCode const KEY_KP_EQUALS = SDL_SCANCODE_KP_EQUALS;
        ScanCode const KEY_KP_EQUALSAS400 = SDL_SCANCODE_KP_EQUALSAS400;
        ScanCode const KEY_KP_EXCLAM = SDL_SCANCODE_KP_EXCLAM;
        ScanCode const KEY_KP_GREATER = SDL_SCANCODE_KP_GREATER;
        ScanCode const KEY_KP_HASH = SDL_SCANCODE_KP_HASH;
        ScanCode const KEY_KP_HEXADECIMAL = SDL_SCANCODE_KP_HEXADECIMAL;
        ScanCode const KEY_KP_LEFTBRACE = SDL_SCANCODE_KP_LEFTBRACE;
        ScanCode const KEY_KP_LEFTPAREN = SDL_SCANCODE_KP_LEFTPAREN;
        ScanCode const KEY_KP_LESS = SDL_SCANCODE_KP_LESS;
        ScanCode const KEY_KP_MEMADD = SDL_SCANCODE_KP_MEMADD;
        ScanCode const KEY_KP_MEMCLEAR = SDL_SCANCODE_KP_MEMCLEAR;
        ScanCode const KEY_KP_MEMDIVIDE = SDL_SCANCODE_KP_MEMDIVIDE;
        ScanCode const KEY_KP_MEMMULTIPLY = SDL_SCANCODE_KP_MEMMULTIPLY;
        ScanCode const KEY_KP_MEMRECALL = SDL_SCANCODE_KP_MEMRECALL;
        ScanCode const KEY_KP_MEMSTORE = SDL_SCANCODE_KP_MEMSTORE;
        ScanCode const KEY_KP_MEMSUBTRACT = SDL_SCANCODE_KP_MEMSUBTRACT;
        ScanCode const KEY_KP_MINUS = SDL_SCANCODE_KP_MINUS;
        ScanCode const KEY_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY;
        ScanCode const KEY_KP_OCTAL = SDL_SCANCODE_KP_OCTAL;
        ScanCode const KEY_KP_PERCENT = SDL_SCANCODE_KP_PERCENT;
        ScanCode const KEY_KP_PERIOD = SDL_SCANCODE_KP_PERIOD;
        ScanCode const KEY_KP_PLUS = SDL_SCANCODE_KP_PLUS;
        ScanCode const KEY_KP_PLUSMINUS = SDL_SCANCODE_KP_PLUSMINUS;
        ScanCode const KEY_KP_POWER = SDL_SCANCODE_KP_POWER;
        ScanCode const KEY_KP_RIGHTBRACE = SDL_SCANCODE_KP_RIGHTBRACE;
        ScanCode const KEY_KP_RIGHTPAREN = SDL_SCANCODE_KP_RIGHTPAREN;
        ScanCode const KEY_KP_SPACE = SDL_SCANCODE_KP_SPACE;
        ScanCode const KEY_KP_TAB = SDL_SCANCODE_KP_TAB;
        ScanCode const KEY_KP_VERTICALBAR = SDL_SCANCODE_KP_VERTICALBAR;
        ScanCode const KEY_KP_XOR = SDL_SCANCODE_KP_XOR;
        ScanCode const KEY_LALT = SDL_SCANCODE_LALT;
        ScanCode const KEY_LCTRL = SDL_SCANCODE_LCTRL;
        ScanCode const KEY_LEFT = SDL_SCANCODE_LEFT;
        ScanCode const KEY_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET;
        ScanCode const KEY_LGUI = SDL_SCANCODE_LGUI;
        ScanCode const KEY_LSHIFT = SDL_SCANCODE_LSHIFT;
        ScanCode const KEY_MAIL = SDL_SCANCODE_MAIL;
        ScanCode const KEY_MEDIASELECT = SDL_SCANCODE_MEDIASELECT;
        ScanCode const KEY_MENU = SDL_SCANCODE_MENU;
        ScanCode const KEY_MINUS = SDL_SCANCODE_MINUS;
        ScanCode const KEY_MODE = SDL_SCANCODE_MODE;
        ScanCode const KEY_MUTE = SDL_SCANCODE_MUTE;
        ScanCode const KEY_NUMLOCKCLEAR = SDL_SCANCODE_NUMLOCKCLEAR;
        ScanCode const KEY_OPER = SDL_SCANCODE_OPER;
        ScanCode const KEY_OUT = SDL_SCANCODE_OUT;
        ScanCode const KEY_PRIOR = SDL_SCANCODE_PRIOR;
        ScanCode const KEY_PAGEDOWN = SDL_SCANCODE_PAGEDOWN;
        ScanCode const KEY_PAGEUP = SDL_SCANCODE_PAGEUP;
        ScanCode const KEY_PASTE = SDL_SCANCODE_PASTE;
        ScanCode const KEY_PAUSE = SDL_SCANCODE_PAUSE;
        ScanCode const KEY_PERIOD = SDL_SCANCODE_PERIOD;
        ScanCode const KEY_POWER = SDL_SCANCODE_POWER;
        ScanCode const KEY_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN;
        ScanCode const KEY_RALT = SDL_SCANCODE_RALT;
        ScanCode const KEY_RCTRL = SDL_SCANCODE_RCTRL;
        ScanCode const KEY_RETURN = SDL_SCANCODE_RETURN;
        ScanCode const KEY_RETURN2 = SDL_SCANCODE_RETURN2;
        ScanCode const KEY_RGUI = SDL_SCANCODE_RGUI;
        ScanCode const KEY_RIGHT = SDL_SCANCODE_RIGHT;
        ScanCode const KEY_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET;
        ScanCode const KEY_RSHIFT = SDL_SCANCODE_RSHIFT;
        ScanCode const KEY_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK;
        ScanCode const KEY_SELECT = SDL_SCANCODE_SELECT;
        ScanCode const KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON;
        ScanCode const KEY_SEPARATOR = SDL_SCANCODE_SEPARATOR;
        ScanCode const KEY_SLASH = SDL_SCANCODE_SLASH;
        ScanCode const KEY_SLEEP = SDL_SCANCODE_SLEEP;
        ScanCode const KEY_SPACE = SDL_SCANCODE_SPACE;
        ScanCode const KEY_STOP = SDL_SCANCODE_STOP;
        ScanCode const KEY_SYSREQ = SDL_SCANCODE_SYSREQ;
        ScanCode const KEY_TAB = SDL_SCANCODE_TAB;
        ScanCode const KEY_THOUSANDSSEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR;
        ScanCode const KEY_UNDO = SDL_SCANCODE_UNDO;
        ScanCode const KEY_UNKNOWN = SDL_SCANCODE_UNKNOWN;
        ScanCode const KEY_UP = SDL_SCANCODE_UP;
        ScanCode const KEY_VOLUMEDOWN = SDL_SCANCODE_VOLUMEDOWN;
        ScanCode const KEY_VOLUMEUP = SDL_SCANCODE_VOLUMEUP;
        ScanCode const KEY_WWW = SDL_SCANCODE_WWW;

        ScanCode const KEY_INTERNATIONAL1 = SDL_SCANCODE_INTERNATIONAL1;
        ScanCode const KEY_INTERNATIONAL2 = SDL_SCANCODE_INTERNATIONAL2;
        ScanCode const KEY_INTERNATIONAL3 = SDL_SCANCODE_INTERNATIONAL3;
        ScanCode const KEY_INTERNATIONAL4 = SDL_SCANCODE_INTERNATIONAL4;
        ScanCode const KEY_INTERNATIONAL5 = SDL_SCANCODE_INTERNATIONAL5;
        ScanCode const KEY_INTERNATIONAL6 = SDL_SCANCODE_INTERNATIONAL6;
        ScanCode const KEY_INTERNATIONAL7 = SDL_SCANCODE_INTERNATIONAL7;
        ScanCode const KEY_INTERNATIONAL8 = SDL_SCANCODE_INTERNATIONAL8;
        ScanCode const KEY_INTERNATIONAL9 = SDL_SCANCODE_INTERNATIONAL9;

        ScanCode const KEY_LANG1 = SDL_SCANCODE_LANG1;
        ScanCode const KEY_LANG2 = SDL_SCANCODE_LANG2;
        ScanCode const KEY_LANG3 = SDL_SCANCODE_LANG3;
        ScanCode const KEY_LANG4 = SDL_SCANCODE_LANG4;
        ScanCode const KEY_LANG5 = SDL_SCANCODE_LANG5;
        ScanCode const KEY_LANG6 = SDL_SCANCODE_LANG6;
        ScanCode const KEY_LANG7 = SDL_SCANCODE_LANG7;
        ScanCode const KEY_LANG8 = SDL_SCANCODE_LANG8;
        ScanCode const KEY_LANG9 = SDL_SCANCODE_LANG9;

        ScanCode const KEY_NONUSBACKSLASH = SDL_SCANCODE_NONUSBACKSLASH;
    }
}
