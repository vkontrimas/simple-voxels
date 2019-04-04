#pragma once
#ifndef SIVOX_GAME_INPUT_HPP
#define SIVOX_GAME_INPUT_HPP
#include "common.hpp"

#include <array>
#include <vector>
#include <cassert>
#include <algorithm>

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

		CapsLock = 1073741881,
		
		F1 = 1073741882,
		F2 = 1073741883,
		F3 = 1073741884,
		F4 = 1073741885,
		F5 = 1073741886,
		F6 = 1073741887,
		F7 = 1073741888,
		F8 = 1073741889,
		F9 = 1073741890,
		F10 = 1073741891,
		F11 = 1073741892,
		F12 = 1073741893,
		
		PrintScreen = 1073741894,
		ScrollLock = 1073741895,
		Pause = 1073741896,
		Insert = 1073741897,
		Home = 1073741898,
		PageUp = 1073741899,
		Delete = 127,
		End = 1073741901,
		PageDown = 1073741902,
		Right = 1073741903,
		Left = 1073741904,
		Down = 1073741905,
		Up = 1073741906,
		
		NumLockClear = 1073741907,
		NumDivide = 1073741908,
		NumMultiply = 1073741909,
		NumMinus = 1073741910,
		NumPlus = 1073741911,
		NumEnter = 1073741912,
		Num1 = 1073741913,
		Num2 = 1073741914,
		Num3 = 1073741915,
		Num4 = 1073741916,
		Num5 = 1073741917,
		Num6 = 1073741918,
		Num7 = 1073741919,
		Num8 = 1073741920,
		Num9 = 1073741921,
		Num0 = 1073741922,
		NumPeriod = 1073741923,
		
		Application = 1073741925,
		Power = 1073741926,
		NumEquals = 1073741927,
		
		F13 = 1073741928,
		F14 = 1073741929,
		F15 = 1073741930,
		F16 = 1073741931,
		F17 = 1073741932,
		F18 = 1073741933,
		F19 = 1073741934,
		F20 = 1073741935,
		F21 = 1073741936,
		F22 = 1073741937,
		F23 = 1073741938,
		F24 = 1073741939,
		Execute = 1073741940,
		Help = 1073741941,
		Menu = 1073741942,
		Select = 1073741943,
		Stop = 1073741944,
		Again = 1073741945,
		Undo = 1073741946,
		Cut = 1073741947,
		Copy = 1073741948,
		Paste = 1073741949,
		Find = 1073741950,
		Mute = 1073741951,
		VolumeUp = 1073741952,
		VolumeDown = 1073741953,
		NumComma = 1073741957,
		NumEqualsAs400 = 1073741958,
		
		Alterase = 1073741977,
		Sysreq = 1073741978,
		Cancel = 1073741979,
		Clear = 1073741980,
		Prior = 1073741981,
		Return2 = 1073741982,
		Separator = 1073741983,
		Out = 1073741984,
		Oper = 1073741985,
		Clearagain = 1073741986,
		Crsel = 1073741987,
		Exsel = 1073741988,
		
		Num00 = 1073742000,
		Num000 = 1073742001,
		ThousandsSeparator = 1073742002,
		DecimalSeparator = 1073742003,
		CurrencyUnit = 1073742004,
		CurrencySubunit = 1073742005,
		NumLeftParen = 1073742006,
		NumRightParen = 1073742007,
		NumLeftBrace = 1073742008,
		NumRightBrace = 1073742009,
		NumTab = 1073742010,
		NumBackspace = 1073742011,
		NumA = 1073742012,
		NumB = 1073742013,
		NumC = 1073742014,
		NumD = 1073742015,
		NumE = 1073742016,
		NumF = 1073742017,
		NumXor = 1073742018,
		NumPower = 1073742019,
		NumPercent = 1073742020,
		NumLess = 1073742021,
		NumGreater = 1073742022,
		NumAmpersand = 1073742023,
		NumDoubleAmpersand = 1073742024,
		NumVerticalBar = 1073742025,
		NumDoubleVerticalBar = 1073742026,
		NumColon = 1073742027,
		NumHash = 1073742028,
		NumSpace = 1073742029,
		NumAt = 1073742030,
		NumExclamation = 1073742031,
		NumMemStore = 1073742032,
		NumMemRecall = 1073742033,
		NumMemClear = 1073742034,
		NumMemAdd = 1073742035,
		NumMemSubtract = 1073742036,
		NumMemMultiply = 1073742037,
		NumMemDivide = 1073742038,
		NumPlusMinus = 1073742039,
		NumClear = 1073742040,
		NumClearEntry = 1073742041,
		NumBinary = 1073742042,
		NumOctal = 1073742043,
		NumDecimal = 1073742044,
		NumHexadecimal = 1073742045,
		
		LeftCtrl = 1073742048,
		LeftShift = 1073742049,
		LeftAlt = 1073742050,
		LeftGui = 1073742051,
		RightCtrl = 1073742052,
		RightShift = 1073742053,
		RightAlt = 1073742054,
		RightGui = 1073742055,
		
		Mode = 1073742081,
		
		AudioNext = 1073742082,
		AudioPrev = 1073742083,
		AudioStop = 1073742084,
		AudioPlay = 1073742085,
		AudioMute = 1073742086,
		MediaSelect = 1073742087,
		Www = 1073742088,
		Mail = 1073742089,
		Calculator = 1073742090,
		Computer = 1073742091,
		AcSearch = 1073742092,
		AcHome = 1073742093,
		AcBack = 1073742094,
		AcForward = 1073742095,
		AcStop = 1073742096,
		AcRefresh = 1073742097,
		AcBookmarks = 1073742098,
		
		BrightnessDown = 1073742099,
		BrightnessUp = 1073742100,
		DisplaySwitch = 1073742101,
		KeyboardIlluminationToggle = 1073742102,
		KeyboardIlluminationDown = 1073742103,
		KeyboardIllumniationUp = 1073742104,
		Eject = 1073742105,
		Sleep = 1073742106,
		App1 = 1073742107,
		App2 = 1073742108,
		
		AudioRewind = 1073742109,
		AudioFastForward = 1073742110
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
    
    /*
     * Represents an Input that can be mapped to a button or an axis.
     * Currently only keyboard keycodes and scancodes are supported.
     *
     * KeyCode and ScanCode values are implicitly converted to an Input.
     */
    class Input {
    public:
        enum KeyboardEvent {
            Up,
            Down
        };

        enum Type {
            KeyboardScanCode,
            KeyboardKeyCode
        };

        Input(KeyCode keycode) : m_type(KeyboardKeyCode), m_keycode(keycode) {}
        Input(ScanCode scancode) : m_type(KeyboardScanCode), m_scancode(scancode) {}

        Type type() const { return m_type; }

        ScanCode scancode() const {
            if (type() == KeyboardScanCode) { return m_scancode; }
            else { return ScanCode::Unknown; }
        }

        KeyCode keycode() const {
            if (type() == KeyboardKeyCode) { return m_keycode; }
            else { return KeyCode::Unknown; }
        }

    private:
        Type m_type;
        union {
            ScanCode m_scancode;
            KeyCode  m_keycode;
        };
    };

    static inline bool operator==(Input a, Input b) {
        if (a.type() == b.type()) {
            switch (a.type()) {
            case Input::KeyboardKeyCode:
                return a.keycode() == b.keycode();
            case Input::KeyboardScanCode:
                return a.scancode() == b.scancode();
            default:
                return false;
            }
        }
        else {
            return false;
        }
    }

    static inline bool operator!=(Input a, Input b) {
        return !(a == b);
    }


    /*
     * Processes user input.
     * Allows arbitrary buttons and axes to be mapped to inputs.
     */
    class InputHandler {
    public:
        void keyboard_event(KeyCode keycode, ScanCode scancode, Input::KeyboardEvent e);
        void update();

        template<class T> inline void map_button(T button, Input input) {
            int index = static_cast<int>(button);
            if (index >= 0) {
                if (index >= m_buttons.size()) {
                    m_buttons.resize(index + 1);
                }

                auto existing_input = std::find(
                    m_buttons[index].inputs.begin(),
                    m_buttons[index].inputs.end(),
                    input
                );

                if (existing_input == m_buttons[index].inputs.end()) {
                    m_buttons[index].inputs.push_back(input);
                }
            }
        }

        template<class T> inline bool button_down(T button) {
            int index = static_cast<int>(button);
            return index >= 0 && index < m_buttons.size() && m_buttons[index].down;
        }

        template<class T> inline bool button_up(T button) {
            int index = static_cast<int>(button);
            return index >= 0 && index < m_buttons.size() && !m_buttons[index].down;
        }

        template<class T> inline bool button_pressed(T button) {
            int index = static_cast<int>(button);
            return index >= 0 && index < m_buttons.size() && m_buttons[index].down && !m_buttons[index].down_previously;
        }

        template<class T> inline bool button_released(T button) {
            int index = static_cast<int>(button);
            return index >= 0 && index < m_buttons.size() && !m_buttons[index].down && m_buttons[index].down_previously;
        }
        
        template<class T> inline std::vector<Input> const& button_inputs(T button) { 
            int index = static_cast<int>(button);
            if (index >= 0 && index < m_buttons.size()) { return m_buttons[index].inputs; }
            else { return m_empty_input_vec; }
        }

    private:
        struct ButtonMapping {
            std::vector<Input> inputs;
            bool down = false;
            bool down_previously = false;
        };
        std::vector<ButtonMapping> m_buttons;
        const std::vector<Input> m_empty_input_vec;
    };
}

#endif /*SIVOX_GAME_INPUT_HPP*/
