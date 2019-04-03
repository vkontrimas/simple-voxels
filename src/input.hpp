#pragma once
#ifndef SIVOX_GAME_INPUT_HPP
#define SIVOX_GAME_INPUT_HPP
#include "common.hpp"

#include <array>
#include <vector>
/*
 * TODO: Work on getting rid of these SDL includes.
 * For keycodes and scancodes we just need to take the actual values and plop them into our enums.
 * This is a pain for the KeyCode enum as SDL_keycode uses a macro to calculate the values.
 */
#include <SDL_keycode.h>
#include <SDL_scancode.h>
#include <SDL_events.h>

namespace sivox {
    /*
     * A keycode enum.
     * More or less based on SDL_Keycode
     */
    enum class KeyCode {
        Unknown = 0,

        Return = '\r',
        Escape = '\033',
        Backspace = '\b',
        Tab = '\t',
        Space = ' ',
        Exclaim = '!',
        DoubleQuote = '"',
        Hash = '#',
        Percent = '%',
        Dollar = '$',
        Ampersand = '&',
        Quote = '\'',
        Leftparen = '(',
        Rightparen = ')',
        Asterisk = '*',
        Plus = '+',
        Comma = ',',
        Minus = '-',
        Period = '.',
        Slash = '/',
        Key0 = '0',
        Key1 = '1',
        Key2 = '2',
        Key3 = '3',
        Key4 = '4',
        Key5 = '5',
        Key6 = '6',
        Key7 = '7',
        Key8 = '8',
        Key9 = '9',
        Colon = ':',
        Semicolon = ';',
        Less = '<',
        Equals = '=',
        Greater = '>',
        Question = '?',
        At = '@',
        /*
           Skip uppercase letters
         */
        Leftbracket = '[',
        Backslash = '\\',
        Rightbracket = ']',
        Caret = '^',
        Underscore = '_',
        Backquote = '`',
        A = 'a',
        B = 'b',
        C = 'c',
        D = 'd',
        E = 'e',
        F = 'f',
        G = 'g',
        H = 'h',
        I = 'i',
        J = 'j',
        K = 'k',
        L = 'l',
        M = 'm',
        N = 'n',
        O = 'o',
        P = 'p',
        Q = 'q',
        R = 'r',
        S = 's',
        T = 't',
        U = 'u',
        V = 'v',
        W = 'w',
        X = 'x',
        Y = 'y',
        Z = 'z',

        CapsLock = SDLK_CAPSLOCK,

        F1 = SDLK_F1,
        F2 = SDLK_F2,
        F3 = SDLK_F3,
        F4 = SDLK_F4,
        F5 = SDLK_F5,
        F6 = SDLK_F6,
        F7 = SDLK_F7,
        F8 = SDLK_F8,
        F9 = SDLK_F9,
        F10 = SDLK_F10,
        F11 = SDLK_F11,
        F12 = SDLK_F12,

        PrintScreen = SDLK_PRINTSCREEN,
        ScrollLock = SDLK_SCROLLLOCK,
        Pause = SDLK_PAUSE,
        Insert = SDLK_INSERT,
        Home = SDLK_HOME,
        PageUp = SDLK_PAGEUP,
        Delete = SDLK_DELETE,
        End = SDLK_END,
        PageDown = SDLK_PAGEDOWN,
        Right = SDLK_RIGHT,
        Left = SDLK_LEFT,
        Down = SDLK_DOWN,
        Up = SDLK_UP,

        NumLockClear = SDLK_NUMLOCKCLEAR,
        NumDivide = SDLK_KP_DIVIDE,
        NumMultiply = SDLK_KP_MULTIPLY,
        NumMinus = SDLK_KP_MINUS,
        NumPlus = SDLK_KP_PLUS,
        NumEnter = SDLK_KP_ENTER,
        Num1 = SDLK_KP_1,
        Num2 = SDLK_KP_2,
        Num3 = SDLK_KP_3,
        Num4 = SDLK_KP_4,
        Num5 = SDLK_KP_5,
        Num6 = SDLK_KP_6,
        Num7 = SDLK_KP_7,
        Num8 = SDLK_KP_8,
        Num9 = SDLK_KP_9,
        Num0 = SDLK_KP_0,
        NumPeriod = SDLK_KP_PERIOD,

        Application = SDLK_APPLICATION,
        Power = SDLK_POWER,
        NumEquals = SDLK_KP_EQUALS,
        F13 = SDLK_F13,
        F14 = SDLK_F14,
        F15 = SDLK_F15,
        F16 = SDLK_F16,
        F17 = SDLK_F17,
        F18 = SDLK_F18,
        F19 = SDLK_F19,
        F20 = SDLK_F20,
        F21 = SDLK_F21,
        F22 = SDLK_F22,
        F23 = SDLK_F23,
        F24 = SDLK_F24,
        Execute = SDLK_EXECUTE,
        Help = SDLK_HELP,
        Menu = SDLK_MENU,
        Select = SDLK_SELECT,
        Stop = SDLK_STOP,
        Again = SDLK_AGAIN,
        Undo = SDLK_UNDO,
        Cut = SDLK_CUT,
        Copy = SDLK_COPY,
        Paste = SDLK_PASTE,
        Find = SDLK_FIND,
        Mute = SDLK_MUTE,
        VolumeUp = SDLK_VOLUMEUP,
        VolumeDown = SDLK_VOLUMEDOWN,
        NumComma = SDLK_KP_COMMA,
        NumEqualsAs400 = SDLK_KP_EQUALSAS400,

        Alterase = SDLK_ALTERASE,
        Sysreq = SDLK_SYSREQ,
        Cancel = SDLK_CANCEL,
        Clear = SDLK_CLEAR,
        Prior = SDLK_PRIOR,
        Return2 = SDLK_RETURN2,
        Separator = SDLK_SEPARATOR,
        Out = SDLK_OUT,
        Oper = SDLK_OPER,
        Clearagain = SDLK_CLEARAGAIN,
        Crsel = SDLK_CRSEL,
        Exsel = SDLK_EXSEL,

        Num00 = SDLK_KP_00,
        Num000 = SDLK_KP_000,
        ThousandsSeparator = SDLK_THOUSANDSSEPARATOR,
        DecimalSeparator = SDLK_DECIMALSEPARATOR,
        CurrencyUnit = SDLK_CURRENCYUNIT,
        CurrencySubunit = SDLK_CURRENCYSUBUNIT,
        NumLeftParen = SDLK_KP_LEFTPAREN,
        NumRightParen = SDLK_KP_RIGHTPAREN,
        NumLeftBrace = SDLK_KP_LEFTBRACE,
        NumRightBrace = SDLK_KP_RIGHTBRACE,
        NumTab = SDLK_KP_TAB,
        NumBackspace = SDLK_KP_BACKSPACE,
        NumA = SDLK_KP_A,
        NumB = SDLK_KP_B,
        NumC = SDLK_KP_C,
        NumD = SDLK_KP_D,
        NumE = SDLK_KP_E,
        NumF = SDLK_KP_F,
        NumXor = SDLK_KP_XOR,
        NumPower = SDLK_KP_POWER,
        NumPercent = SDLK_KP_PERCENT,
        NumLess = SDLK_KP_LESS,
        NumGreater = SDLK_KP_GREATER,
        NumAmpersand = SDLK_KP_AMPERSAND,
        NumDoubleAmpersand = SDLK_KP_DBLAMPERSAND,
        NumVerticalBar = SDLK_KP_VERTICALBAR,
        NumDoubleVerticalBar = SDLK_KP_DBLVERTICALBAR,
        NumColon = SDLK_KP_COLON,
        NumHash = SDLK_KP_HASH,
        NumSpace = SDLK_KP_SPACE,
        NumAt = SDLK_KP_AT,
        NumExclamation = SDLK_KP_EXCLAM,
        NumMemStore = SDLK_KP_MEMSTORE,
        NumMemRecall = SDLK_KP_MEMRECALL,
        NumMemClear = SDLK_KP_MEMCLEAR,
        NumMemAdd = SDLK_KP_MEMADD,
        NumMemSubtract = SDLK_KP_MEMSUBTRACT,
        NumMemMultiply = SDLK_KP_MEMMULTIPLY,
        NumMemDivide = SDLK_KP_MEMDIVIDE,
        NumPlusMinus = SDLK_KP_PLUSMINUS,
        NumClear = SDLK_KP_CLEAR,
        NumClearEntry = SDLK_KP_CLEARENTRY,
        NumBinary = SDLK_KP_BINARY,
        NumOctal = SDLK_KP_OCTAL,
        NumDecimal = SDLK_KP_DECIMAL,
        NumHexadecimal = SDLK_KP_HEXADECIMAL,

        LeftCtrl = SDLK_LCTRL,
        LeftShift = SDLK_LSHIFT,
        LeftAlt = SDLK_LALT,
        LeftGui = SDLK_LGUI,
        RightCtrl = SDLK_RCTRL,
        RightShift = SDLK_RSHIFT,
        RightAlt = SDLK_RALT,
        RightGui = SDLK_RGUI,

        Mode = SDLK_MODE,

        AudioNext = SDLK_AUDIONEXT,
        AudioPrev = SDLK_AUDIOPREV,
        AudioStop = SDLK_AUDIOSTOP,
        AudioPlay = SDLK_AUDIOPLAY,
        AudioMute = SDLK_AUDIOMUTE,
        MediaSelect = SDLK_MEDIASELECT,
        Www = SDLK_WWW,
        Mail = SDLK_MAIL,
        Calculator = SDLK_CALCULATOR,
        Computer = SDLK_COMPUTER,
        AcSearch = SDLK_AC_SEARCH,
        AcHome = SDLK_AC_HOME,
        AcBack = SDLK_AC_BACK,
        AcForward = SDLK_AC_FORWARD,
        AcStop = SDLK_AC_STOP,
        AcRefresh = SDLK_AC_REFRESH,
        AcBookmarks = SDLK_AC_BOOKMARKS,

        BrightnessDown = SDLK_BRIGHTNESSDOWN,
        BrightnessUp = SDLK_BRIGHTNESSUP,
        DisplaySwitch = SDLK_DISPLAYSWITCH,
        KeyboardIlluminationToggle = SDLK_KBDILLUMTOGGLE,
        KeyboardIlluminationDown = SDLK_KBDILLUMDOWN,
        KeyboardIllumniationUp = SDLK_KBDILLUMUP,
        Eject = SDLK_EJECT,
        Sleep = SDLK_SLEEP,
        App1 = SDLK_APP1,
        App2 = SDLK_APP2,

        AudioRewind = SDLK_AUDIOREWIND,
        AudioFastForward = SDLK_AUDIOFASTFORWARD,

        /*
         * Not an actual keycode.
         * Just a value used to get the upper bound of the KeyCode count.
         * (The actual number of keycodes may be lower. This is just the last value + 1.)
         */
        Count 
    };

    /*
     * A scancode enum.
     * More or less based on SDL_ScanCode
     */
    enum class ScanCode {
        Unknown = 0, // SDL_SCANCODE_UNKNOWN 

        A = 4,  // SDL_SCANCODE_A 
        B = 5,  // SDL_SCANCODE_B 
        C = 6,  // SDL_SCANCODE_C
        D = 7,  // SDL_SCANCODE_D
        E = 8,  // SDL_SCANCODE_E
        F = 9,  // SDL_SCANCODE_F
        G = 10, // SDL_SCANCODE_G
        H = 11, // SDL_SCANCODE_H
        I = 12, // SDL_SCANCODE_I
        J = 13, // SDL_SCANCODE_J
        K = 14, // SDL_SCANCODE_K
        L = 15, // SDL_SCANCODE_L
        M = 16, // SDL_SCANCODE_M
        N = 17, // SDL_SCANCODE_N
        O = 18, // SDL_SCANCODE_O
        P = 19, // SDL_SCANCODE_P
        Q = 20, // SDL_SCANCODE_Q
        R = 21, // SDL_SCANCODE_R
        S = 22, // SDL_SCANCODE_S
        T = 23, // SDL_SCANCODE_T
        U = 24, // SDL_SCANCODE_U
        V = 25, // SDL_SCANCODE_V
        W = 26, // SDL_SCANCODE_W
        X = 27, // SDL_SCANCODE_X
        Y = 28, // SDL_SCANCODE_Y
        Z = 29, // SDL_SCANCODE_Z

        Key1 = 30, // SDL_SCANCODE_1
        Key2 = 31, // SDL_SCANCODE_2
        Key3 = 32, // SDL_SCANCODE_3
        Key4 = 33, // SDL_SCANCODE_4
        Key5 = 34, // SDL_SCANCODE_5
        Key6 = 35, // SDL_SCANCODE_6
        Key7 = 36, // SDL_SCANCODE_7
        Key8 = 37, // SDL_SCANCODE_8
        Key9 = 38, // SDL_SCANCODE_9
        Key0 = 39, // SDL_SCANCODE_0

        Return = 40, // SDL_SCANCODE_RETURN
        Escape = 41, // SDL_SCANCODE_ESCAPE
        Backspace = 42, // SDL_SCANCODE_BACKSPACE
        Tab = 43, // SDL_SCANCODE_TAB
        Space = 44, // SDL_SCANCODE_SPACE

        Minus = 45, // SDL_SCANCODE_MINUS
        Equals = 46, // SDL_SCANCODE_EQUALS
        LeftBracket = 47, // SDL_SCANCODE_LEFTBRACKET
        RightBracket = 48, // SDL_SCANCODE_RIGHTBRACKET
        Backslash = 49,  // SDL_SCANCODE_BACKSLASH
        Nonushash = 50,  // SDL_SCANCODE_NONUSHASH
        Semicolon = 51, // SDL_SCANCODE_SEMICOLON
        Apostrophe = 52, // SDL_SCANCODE_APOSTROPHE
        Grave = 53,  // SDL_SCANCODE_GRAVE
        Comma = 54, // SDL_SCANCODE_COMMA
        Period = 55, // SDL_SCANCODE_PERIOD
        Slash = 56, // SDL_SCANCODE_SLASH

        CapsLock = 57, // SDL_SCANCODE_CAPSLOCK

        F1 = 58, // SDL_SCANCODE_F1
        F2 = 59, // SDL_SCANCODE_F2
        F3 = 60, // SDL_SCANCODE_F3
        F4 = 61, // SDL_SCANCODE_F4
        F5 = 62, // SDL_SCANCODE_F5
        F6 = 63, // SDL_SCANCODE_F6
        F7 = 64, // SDL_SCANCODE_F7
        F8 = 65, // SDL_SCANCODE_F8
        F9 = 66, // SDL_SCANCODE_F9
        F10 = 67, // SDL_SCANCODE_F10
        F11 = 68, // SDL_SCANCODE_F11
        F12 = 69, // SDL_SCANCODE_F12

        PrintScreen = 70, // SDL_SCANCODE_PRINTSCREEN
        ScrollLock = 71, // SDL_SCANCODE_SCROLLLOCK
        Pause = 72, // SDL_SCANCODE_PAUSE
        Insert = 73,  // SDL_SCANCODE_INSERT
        Home = 74, // SDL_SCANCODE_HOME
        PageUp = 75, // SDL_SCANCODE_PAGEUP
        Delete = 76, // SDL_SCANCODE_DELETE
        End = 77, // SDL_SCANCODE_END
        PageDown = 78, // SDL_SCANCODE_PAGEDOWN
        Right = 79, // SDL_SCANCODE_RIGHT
        Left = 80, // SDL_SCANCODE_LEFT
        Down = 81, // SDL_SCANCODE_DOWN
        Up = 82, // SDL_SCANCODE_UP

        NumLockClear = 83,  // SDL_SCANCODE_NUMLOCKCLEAR
        NumDivide = 84, // SDL_SCANCODE_KP_DIVIDE
        NumMultiply = 85, // SDL_SCANCODE_KP_MULTIPLY
        NumMinus = 86, // SDL_SCANCODE_KP_MINUS
        NumPlus = 87, // SDL_SCANCODE_KP_PLUS
        NumEnter = 88, // SDL_SCANCODE_KP_ENTER
        Num1 = 89, // SDL_SCANCODE_KP_1
        Num2 = 90, // SDL_SCANCODE_KP_2
        Num3 = 91, // SDL_SCANCODE_KP_3
        Num4 = 92, // SDL_SCANCODE_KP_4
        Num5 = 93, // SDL_SCANCODE_KP_5
        Num6 = 94, // SDL_SCANCODE_KP_6
        Num7 = 95, // SDL_SCANCODE_KP_7
        Num8 = 96, // SDL_SCANCODE_KP_8
        Num9 = 97, // SDL_SCANCODE_KP_9
        Num0 = 98, // SDL_SCANCODE_KP_0
        NumPeriod = 99, // SDL_SCANCODE_KP_PERIOD

        NonUSBackslash = 100,  // SDL_SCANCODE_NONUSBACKSLASH
        Application = 101,  // SDL_SCANCODE_APPLICATION
        Power = 102,  // SDL_SCANCODE_POWER
        NumEquals = 103, // SDL_SCANCODE_KP_EQUALS
        F13 = 104, // SDL_SCANCODE_F13
        F14 = 105, // SDL_SCANCODE_F14
        F15 = 106, // SDL_SCANCODE_F15
        F16 = 107, // SDL_SCANCODE_F16
        F17 = 108, // SDL_SCANCODE_F17
        F18 = 109, // SDL_SCANCODE_F18
        F19 = 110, // SDL_SCANCODE_F19
        F20 = 111, // SDL_SCANCODE_F20
        F21 = 112, // SDL_SCANCODE_F21
        F22 = 113, // SDL_SCANCODE_F22
        F23 = 114, // SDL_SCANCODE_F23
        F24 = 115, // SDL_SCANCODE_F24
        Execute = 116, // SDL_SCANCODE_EXECUTE
        Help = 117, // SDL_SCANCODE_HELP
        Menu = 118, // SDL_SCANCODE_MENU
        Select = 119, // SDL_SCANCODE_SELECT
        Stop = 120, // SDL_SCANCODE_STOP
        Again = 121,    // SDL_SCANCODE_AGAIN
        Undo = 122, // SDL_SCANCODE_UNDO
        Cut = 123, // SDL_SCANCODE_CUT
        Copy = 124, // SDL_SCANCODE_COPY
        Paste = 125, // SDL_SCANCODE_PASTE
        Find = 126, // SDL_SCANCODE_FIND
        Mute = 127, // SDL_SCANCODE_MUTE
        VolumeUp = 128, // SDL_SCANCODE_VOLUMEUP
        VolumeDown = 129, // SDL_SCANCODE_VOLUMEDOWN
        NumComma = 133, // SDL_SCANCODE_KP_COMMA
        NumEqualsAs400 = 134, // SDL_SCANCODE_KP_EQUALSAS400

        International1 = 135,  // SDL_SCANCODE_INTERNATIONAL1
        International2 = 136, // SDL_SCANCODE_INTERNATIONAL2
        International3 = 137,  // SDL_SCANCODE_INTERNATIONAL3
        International4 = 138, // SDL_SCANCODE_INTERNATIONAL4
        International5 = 139, // SDL_SCANCODE_INTERNATIONAL5
        International6 = 140, // SDL_SCANCODE_INTERNATIONAL6
        International7 = 141, // SDL_SCANCODE_INTERNATIONAL7
        International8 = 142, // SDL_SCANCODE_INTERNATIONAL8
        International9 = 143, // SDL_SCANCODE_INTERNATIONAL9
        Lang1 = 144,  // SDL_SCANCODE_LANG1
        Lang2 = 145,  // SDL_SCANCODE_LANG2
        Lang3 = 146, // SDL_SCANCODE_LANG3
        Lang4 = 147, // SDL_SCANCODE_LANG4
        Lang5 = 148, // SDL_SCANCODE_LANG5
        Lang6 = 149, // SDL_SCANCODE_LANG6
        Lang7 = 150, // SDL_SCANCODE_LANG7
        Lang8 = 151, // SDL_SCANCODE_LANG8
        Lang9 = 152, // SDL_SCANCODE_LANG9

        Alterase = 153, // SDL_SCANCODE_ALTERASE
        Sysreq = 154, // SDL_SCANCODE_SYSREQ
        Cancel = 155, // SDL_SCANCODE_CANCEL
        Clear = 156, // SDL_SCANCODE_CLEAR
        Prior = 157, // SDL_SCANCODE_PRIOR
        Return2 = 158, // SDL_SCANCODE_RETURN2
        Separator = 159, // SDL_SCANCODE_SEPARATOR
        Out = 160, // SDL_SCANCODE_OUT
        Oper = 161, // SDL_SCANCODE_OPER
        Clearagain = 162, // SDL_SCANCODE_CLEARAGAIN
        Crsel = 163, // SDL_SCANCODE_CRSEL
        Exsel = 164, // SDL_SCANCODE_EXSEL

        Num00 = 176, //         SDL_SCANCODE_KP_00
        Num000 = 177, //         SDL_SCANCODE_KP_000
        Thousandsseparator = 178, //         SDL_SCANCODE_THOUSANDSSEPARATOR
        Decimalseparator = 179, //         SDL_SCANCODE_DECIMALSEPARATOR
        CurrencyUnit = 180, //         SDL_SCANCODE_CURRENCYUNIT
        CurrencySubunit = 181, //         SDL_SCANCODE_CURRENCYSUBUNIT
        NumLeftParen = 182, //         SDL_SCANCODE_KP_LEFTPAREN
        NumRightParen = 183, //         SDL_SCANCODE_KP_RIGHTPAREN
        NumLeftBrace = 184, //         SDL_SCANCODE_KP_LEFTBRACE
        NumRightBrace = 185, //         SDL_SCANCODE_KP_RIGHTBRACE
        NumTab = 186, //         SDL_SCANCODE_KP_TAB
        NumBackspace = 187, //         SDL_SCANCODE_KP_BACKSPACE
        NumA = 188, //         SDL_SCANCODE_KP_A
        NumB = 189, //         SDL_SCANCODE_KP_B
        NumC = 190, //         SDL_SCANCODE_KP_C
        NumD = 191, //         SDL_SCANCODE_KP_D
        NumE = 192, //         SDL_SCANCODE_KP_E
        NumF = 193, //         SDL_SCANCODE_KP_F
        NumXor = 194, //         SDL_SCANCODE_KP_XOR
        NumPower = 195, //         SDL_SCANCODE_KP_POWER
        NumPercent = 196, //         SDL_SCANCODE_KP_PERCENT
        NumLess = 197, //         SDL_SCANCODE_KP_LESS
        NumGreater = 198, //         SDL_SCANCODE_KP_GREATER
        NumAmpersand = 199, //         SDL_SCANCODE_KP_AMPERSAND
        NumDoubleAmpersand = 200, //         SDL_SCANCODE_KP_DBLAMPERSAND
        NumVerticalBar = 201, //         SDL_SCANCODE_KP_VERTICALBAR
        NumDoubleverticalBar = 202, //         SDL_SCANCODE_KP_DBLVERTICALBAR
        NumColon = 203, //         SDL_SCANCODE_KP_COLON
        NumHash = 204, //         SDL_SCANCODE_KP_HASH
        NumSpace = 205, //         SDL_SCANCODE_KP_SPACE
        NumAt = 206, //         SDL_SCANCODE_KP_AT
        NumExclam = 207, //         SDL_SCANCODE_KP_EXCLAM
        NumMemstore = 208, //         SDL_SCANCODE_KP_MEMSTORE
        NumMemrecall = 209, //         SDL_SCANCODE_KP_MEMRECALL
        NumMemclear = 210, //         SDL_SCANCODE_KP_MEMCLEAR
        NumMemadd = 211, //         SDL_SCANCODE_KP_MEMADD
        NumMemsubtract = 212, //         SDL_SCANCODE_KP_MEMSUBTRACT
        NumMemmultiply = 213, //         SDL_SCANCODE_KP_MEMMULTIPLY
        NumMemdivide = 214, //         SDL_SCANCODE_KP_MEMDIVIDE
        NumPlusMinus = 215, //         SDL_SCANCODE_KP_PLUSMINUS
        NumClear = 216, //         SDL_SCANCODE_KP_CLEAR
        NumClearEntry = 217, //         SDL_SCANCODE_KP_CLEARENTRY
        NumBinary = 218, //         SDL_SCANCODE_KP_BINARY
        NumOctal = 219, //         SDL_SCANCODE_KP_OCTAL
        NumDecimal = 220, //         SDL_SCANCODE_KP_DECIMAL
        NumHexadecimal = 221, //         SDL_SCANCODE_KP_HEXADECIMAL

        LeftCtrl = 224, //         SDL_SCANCODE_LCTRL
        LeftShift = 225, //         SDL_SCANCODE_LSHIFT
        LeftAlt = 226,  //         SDL_SCANCODE_LALT
        LeftGui = 227,  //         SDL_SCANCODE_LGUI
        RightCtrl = 228, //         SDL_SCANCODE_RCTRL
        RightShift = 229, //         SDL_SCANCODE_RSHIFT
        RightAlt = 230,  //         SDL_SCANCODE_RALT
        RightGui = 231,  //         SDL_SCANCODE_RGUI

        Mode = 257, // SDL_SCANCODE_MODE

        AudioNext = 258, //         SDL_SCANCODE_AUDIONEXT
        AudioPrev = 259, //         SDL_SCANCODE_AUDIOPREV
        AudioStop = 260, //         SDL_SCANCODE_AUDIOSTOP
        AudioPlay = 261, //         SDL_SCANCODE_AUDIOPLAY
        AudioMute = 262, //         SDL_SCANCODE_AUDIOMUTE
        MediaSelect = 263, //         SDL_SCANCODE_MEDIASELECT
        Www = 264, //         SDL_SCANCODE_WWW
        Mail = 265, //         SDL_SCANCODE_MAIL
        Calculator = 266, //         SDL_SCANCODE_CALCULATOR
        Computer = 267, //         SDL_SCANCODE_COMPUTER
        ApplicationSearch = 268, //         SDL_SCANCODE_AC_SEARCH
        ApplicationHome = 269, //         SDL_SCANCODE_AC_HOME
        ApplicationBack = 270, //         SDL_SCANCODE_AC_BACK
        ApplicationForward = 271, //         SDL_SCANCODE_AC_FORWARD
        ApplicationStop = 272, //         SDL_SCANCODE_AC_STOP
        ApplicationRefresh = 273, //         SDL_SCANCODE_AC_REFRESH
        ApplicationBookmarks = 274, //         SDL_SCANCODE_AC_BOOKMARKS

        BrightnessDown = 275, //         SDL_SCANCODE_BRIGHTNESSDOWN
        BrightnessUp = 276, //         SDL_SCANCODE_BRIGHTNESSUP
        DisplaySwitch = 277,  //         SDL_SCANCODE_DISPLAYSWITCH
                                          
        KeyboardIlluminationToggle = 278, //         SDL_SCANCODE_KBDILLUMTOGGLE
        KeyboardIlluminationDown = 279, //         SDL_SCANCODE_KBDILLUMDOWN
        KeyboardIlluminationUp = 280, //         SDL_SCANCODE_KBDILLUMUP
        Eject = 281, //         SDL_SCANCODE_EJECT
        Sleep = 282, //         SDL_SCANCODE_SLEEP

        App1 = 283, // SDL_SCANCODE_APP1
        App2 = 284, // SDL_SCANCODE_APP2

        AudioRewind = 285, // SDL_SCANCODE_AUDIOREWIND
        AudioFastForward = 286, // SDL_SCANCODE_AUDIOFASTFORWARD

        /*
         * Not a real value.
         * Just an upper bound on the scan code count.
         * (The actual number of scancodes may be lower!)
         */
        Count = 512  
    };

    class Input {
    public:
        void process_sdl_event(SDL_Event const& event);

        void update();

        template<typename ENUMTYPE>
        inline void map_button(ENUMTYPE value, KeyCode code) {
            return map_button(static_cast<int>(value), static_cast<int>(code), false);
        }

        template<typename ENUMTYPE>
        inline void map_button(ENUMTYPE value, ScanCode code) {
            return map_button(static_cast<int>(value), static_cast<int>(code), true);
        }

        template<typename ENUMTYPE>
        inline bool button_down(ENUMTYPE value) {
            return button_down(static_cast<int>(value));
        }

        template<typename ENUMTYPE>
        inline bool button_up(ENUMTYPE value) {
            return button_up(static_cast<int>(value));
        }

        template<typename ENUMTYPE>
        inline bool button_pressed(ENUMTYPE value) {
            return button_pressed(static_cast<int>(value));
        }

        template<typename ENUMTYPE>
        inline bool button_released(ENUMTYPE value) {
            return button_released(static_cast<int>(value));
        }

    sivox_test(private):
        struct ButtonMapping {
            int buttonValue = -1;
            bool inUse = false;

            int code = -1;
            bool useScancode = false;

            bool down = false; 
            bool pressed = false;
            bool released = false;
        };
        std::vector<ButtonMapping> m_buttons;

    private:
        std::array<bool, static_cast<int>(KeyCode::Count)> m_keycode_state;
        std::array<bool, static_cast<int>(ScanCode::Count)> m_scancode_state;

        void map_button(int value, int code, bool use_scancode);
        bool button_down(int value);
        bool button_up(int value);
        bool button_pressed(int value);
        bool button_released(int value);
    };
}

#endif /*SIVOX_GAME_INPUT_HPP*/
