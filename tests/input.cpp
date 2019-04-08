#include <vector>
#include <input.hpp>
#include <catch2/catch.hpp>

using namespace sivox;


TEST_CASE("Input : KeyCode", "[input]") {
    std::vector<KeyCode> keycodes = {
        KeyCode::Unknown, KeyCode::Return, KeyCode::Escape, KeyCode::Backspace, KeyCode::Tab, KeyCode::Space,
        KeyCode::Exclaim, KeyCode::DoubleQuote, KeyCode::Hash, KeyCode::Percent, KeyCode::Dollar,
        KeyCode::Ampersand, KeyCode::Quote, KeyCode::Leftparen, KeyCode::Rightparen, KeyCode::Asterisk,
        KeyCode::Plus, KeyCode::Comma, KeyCode::Minus, KeyCode::Period, KeyCode::Slash, KeyCode::Key0,
        KeyCode::Key1, KeyCode::Key2, KeyCode::Key3, KeyCode::Key4, KeyCode::Key5, KeyCode::Key6, KeyCode::Key7,
        KeyCode::Key8, KeyCode::Key9, KeyCode::Colon, KeyCode::Semicolon, KeyCode::Less, KeyCode::Equals,
        KeyCode::Greater, KeyCode::Question, KeyCode::At, KeyCode::Leftbracket, KeyCode::Backslash,
        KeyCode::Rightbracket, KeyCode::Caret, KeyCode::Underscore, KeyCode::Backquote, KeyCode::A, KeyCode::B,
        KeyCode::C, KeyCode::D, KeyCode::E, KeyCode::F, KeyCode::G, KeyCode::H, KeyCode::I, KeyCode::J, KeyCode::K,
        KeyCode::L, KeyCode::M, KeyCode::N, KeyCode::O, KeyCode::P, KeyCode::Q, KeyCode::R, KeyCode::S, KeyCode::T,
        KeyCode::U, KeyCode::V, KeyCode::W, KeyCode::X, KeyCode::Y, KeyCode::Z, KeyCode::CapsLock, KeyCode::F1,
        KeyCode::F2, KeyCode::F3, KeyCode::F4, KeyCode::F5, KeyCode::F6, KeyCode::F7, KeyCode::F8, KeyCode::F9,
        KeyCode::F10, KeyCode::F11, KeyCode::F12, KeyCode::PrintScreen, KeyCode::ScrollLock, KeyCode::Pause,
        KeyCode::Insert, KeyCode::Home, KeyCode::PageUp, KeyCode::Delete, KeyCode::End, KeyCode::PageDown,
        KeyCode::Right, KeyCode::Left, KeyCode::Down, KeyCode::Up, KeyCode::NumLockClear, KeyCode::NumDivide,
        KeyCode::NumMultiply, KeyCode::NumMinus, KeyCode::NumPlus, KeyCode::NumEnter, KeyCode::Num1, KeyCode::Num2,
        KeyCode::Num3, KeyCode::Num4, KeyCode::Num5, KeyCode::Num6, KeyCode::Num7, KeyCode::Num8, KeyCode::Num9,
        KeyCode::Num0, KeyCode::NumPeriod, KeyCode::Application, KeyCode::Power, KeyCode::NumEquals, KeyCode::F13,
        KeyCode::F14, KeyCode::F15, KeyCode::F16, KeyCode::F17, KeyCode::F18, KeyCode::F19, KeyCode::F20,
        KeyCode::F21, KeyCode::F22, KeyCode::F23, KeyCode::F24, KeyCode::Execute, KeyCode::Help, KeyCode::Menu,
        KeyCode::Select, KeyCode::Stop, KeyCode::Again, KeyCode::Undo, KeyCode::Cut, KeyCode::Copy, KeyCode::Paste,
        KeyCode::Find, KeyCode::Mute, KeyCode::VolumeUp, KeyCode::VolumeDown, KeyCode::NumComma,
        KeyCode::NumEqualsAs400, KeyCode::Alterase, KeyCode::Sysreq, KeyCode::Cancel, KeyCode::Clear,
        KeyCode::Prior, KeyCode::Return2, KeyCode::Separator, KeyCode::Out, KeyCode::Oper, KeyCode::Clearagain,
        KeyCode::Crsel, KeyCode::Exsel, KeyCode::Num00, KeyCode::Num000, KeyCode::ThousandsSeparator,
        KeyCode::DecimalSeparator, KeyCode::CurrencyUnit, KeyCode::CurrencySubunit, KeyCode::NumLeftParen,
        KeyCode::NumRightParen, KeyCode::NumLeftBrace, KeyCode::NumRightBrace, KeyCode::NumTab,
        KeyCode::NumBackspace, KeyCode::NumA, KeyCode::NumB, KeyCode::NumC, KeyCode::NumD, KeyCode::NumE,
        KeyCode::NumF, KeyCode::NumXor, KeyCode::NumPower, KeyCode::NumPercent, KeyCode::NumLess,
        KeyCode::NumGreater, KeyCode::NumAmpersand, KeyCode::NumDoubleAmpersand, KeyCode::NumVerticalBar,
        KeyCode::NumDoubleVerticalBar, KeyCode::NumColon, KeyCode::NumHash, KeyCode::NumSpace, KeyCode::NumAt,
        KeyCode::NumExclamation, KeyCode::NumMemStore, KeyCode::NumMemRecall, KeyCode::NumMemClear,
        KeyCode::NumMemAdd, KeyCode::NumMemSubtract, KeyCode::NumMemMultiply, KeyCode::NumMemDivide,
        KeyCode::NumPlusMinus, KeyCode::NumClear, KeyCode::NumClearEntry, KeyCode::NumBinary, KeyCode::NumOctal,
        KeyCode::NumDecimal, KeyCode::NumHexadecimal, KeyCode::LeftCtrl, KeyCode::LeftShift, KeyCode::LeftAlt,
        KeyCode::LeftGui, KeyCode::RightCtrl, KeyCode::RightShift, KeyCode::RightAlt, KeyCode::RightGui,
        KeyCode::Mode, KeyCode::AudioNext, KeyCode::AudioPrev, KeyCode::AudioStop, KeyCode::AudioPlay,
        KeyCode::AudioMute, KeyCode::MediaSelect, KeyCode::Www, KeyCode::Mail, KeyCode::Calculator,
        KeyCode::Computer, KeyCode::AcSearch, KeyCode::AcHome, KeyCode::AcBack, KeyCode::AcForward, KeyCode::AcStop,
        KeyCode::AcRefresh, KeyCode::AcBookmarks, KeyCode::BrightnessDown, KeyCode::BrightnessUp,
        KeyCode::DisplaySwitch, KeyCode::KeyboardIlluminationToggle, KeyCode::KeyboardIlluminationDown,
        KeyCode::KeyboardIllumniationUp, KeyCode::Eject, KeyCode::Sleep, KeyCode::App1, KeyCode::App2,
        KeyCode::AudioRewind, KeyCode::AudioFastForward
    };

    for (KeyCode keycode : keycodes) {
        ButtonInput key = keycode;
        REQUIRE(key.type() == ButtonInput::KeyboardKeyCode);
        REQUIRE(key.keycode() == keycode);
        REQUIRE(key.scancode() == ScanCode::Unknown);
    }
}

TEST_CASE("Input : ScanCode", "[input]") {
    for (int i = 0; i < static_cast<int>(ScanCode::Count); ++i) {
        ButtonInput key = static_cast<ScanCode>(i);
        REQUIRE(key.type() == ButtonInput::KeyboardScanCode);
        REQUIRE(key.keycode() == KeyCode::Unknown);
        REQUIRE(key.scancode() == static_cast<ScanCode>(i));
    }
}

TEST_CASE("InputHandler : map_button", "[input]") {
    using Catch::Equals;

    constexpr int button_index = 0;

    InputHandler input;
    REQUIRE(input.button_inputs(button_index).size() == 0);

    input.map_button(button_index, KeyCode::A);
    REQUIRE_THAT(
        input.button_inputs(button_index),
        Equals(std::vector<ButtonInput> { KeyCode::A })
    );

    input.map_button(button_index, KeyCode::B);
    REQUIRE_THAT(
        input.button_inputs(button_index),
        Equals(std::vector<ButtonInput> { KeyCode::A, KeyCode::B })
    );

    REQUIRE_FALSE(input.button_down(button_index));
    REQUIRE(input.button_up(button_index));
    REQUIRE_FALSE(input.button_pressed(button_index));
    REQUIRE_FALSE(input.button_released(button_index));
}

TEST_CASE("InputHandler : keyboard input (scancode)", "[input]") {
    using Catch::Equals;

    /*
     * Register buttons
     */
    enum class Button {
        A,
        B,
        C
    };

    InputHandler input;
    input.map_button(Button::A, ScanCode::A);
    input.map_button(Button::B, ScanCode::B);
    input.map_button(Button::C, ScanCode::C);

    INFO("All buttons up initially...");
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("All buttons still up after update with no inputs.");
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("All buttons still up after update with unrelated inputs.");
    input.keyboard_event(KeyCode::D, ScanCode::D, ButtonInput::Down);
    input.keyboard_event(KeyCode::G, ScanCode::G, ButtonInput::Down);
    input.keyboard_event(KeyCode::Num4, ScanCode::Num4, ButtonInput::Down);
    input.keyboard_event(KeyCode::Up, ScanCode::Up, ButtonInput::Down);
    input.keyboard_event(KeyCode::F, ScanCode::F, ButtonInput::Down);
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Release unrelated inputs and press A");
    input.keyboard_event(KeyCode::D, ScanCode::D, ButtonInput::Up);
    input.keyboard_event(KeyCode::G, ScanCode::G, ButtonInput::Up);
    input.keyboard_event(KeyCode::Num4, ScanCode::Num4, ButtonInput::Up);
    input.keyboard_event(KeyCode::Up, ScanCode::Up, ButtonInput::Up);
    input.keyboard_event(KeyCode::F, ScanCode::F, ButtonInput::Up);
    input.keyboard_event(KeyCode::A, ScanCode::A, ButtonInput::Down);
    input.update();
    REQUIRE(input.button_down(Button::A)); REQUIRE_FALSE(input.button_up(Button::A)); REQUIRE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Press B. (A is still being held down.)");
    input.keyboard_event(KeyCode::B, ScanCode::B, ButtonInput::Down);
    input.update();
    REQUIRE(input.button_down(Button::A)); REQUIRE_FALSE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE(input.button_down(Button::B)); REQUIRE_FALSE(input.button_up(Button::B)); REQUIRE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Update with no changes. A and B both still held.");
    input.update();
    REQUIRE(input.button_down(Button::A)); REQUIRE_FALSE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE(input.button_down(Button::B)); REQUIRE_FALSE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Release A. B is still being held.");
    input.keyboard_event(KeyCode::A, ScanCode::A, ButtonInput::Up);
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE(input.button_released(Button::A));
    REQUIRE(input.button_down(Button::B)); REQUIRE_FALSE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Release B.");
    input.keyboard_event(KeyCode::B, ScanCode::B, ButtonInput::Up);
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Do nothing. All buttons should be up.");
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));
}

TEST_CASE("InputHandler : keyboard input (keycode)", "[input]") {
    using Catch::Equals;

    /*
     * Register buttons
     */
    enum class Button {
        A,
        B,
        C
    };

    InputHandler input;
    input.map_button(Button::A, KeyCode::A);
    input.map_button(Button::B, KeyCode::B);
    input.map_button(Button::C, KeyCode::C);

    INFO("All buttons up initially...");
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("All buttons still up after update with no inputs.");
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("All buttons still up after update with unrelated inputs.");
    input.keyboard_event(KeyCode::D, ScanCode::D, ButtonInput::Down);
    input.keyboard_event(KeyCode::G, ScanCode::G, ButtonInput::Down);
    input.keyboard_event(KeyCode::Num4, ScanCode::Num4, ButtonInput::Down);
    input.keyboard_event(KeyCode::Up, ScanCode::Up, ButtonInput::Down);
    input.keyboard_event(KeyCode::F, ScanCode::F, ButtonInput::Down);
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Release unrelated inputs and press A");
    input.keyboard_event(KeyCode::D, ScanCode::D, ButtonInput::Up);
    input.keyboard_event(KeyCode::G, ScanCode::G, ButtonInput::Up);
    input.keyboard_event(KeyCode::Num4, ScanCode::Num4, ButtonInput::Up);
    input.keyboard_event(KeyCode::Up, ScanCode::Up, ButtonInput::Up);
    input.keyboard_event(KeyCode::F, ScanCode::F, ButtonInput::Up);
    input.keyboard_event(KeyCode::A, ScanCode::A, ButtonInput::Down);
    input.update();
    REQUIRE(input.button_down(Button::A)); REQUIRE_FALSE(input.button_up(Button::A)); REQUIRE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Press B. (A is still being held down.)");
    input.keyboard_event(KeyCode::B, ScanCode::B, ButtonInput::Down);
    input.update();
    REQUIRE(input.button_down(Button::A)); REQUIRE_FALSE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE(input.button_down(Button::B)); REQUIRE_FALSE(input.button_up(Button::B)); REQUIRE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Update with no changes. A and B both still held.");
    input.update();
    REQUIRE(input.button_down(Button::A)); REQUIRE_FALSE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE(input.button_down(Button::B)); REQUIRE_FALSE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Release A. B is still being held.");
    input.keyboard_event(KeyCode::A, ScanCode::A, ButtonInput::Up);
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE(input.button_released(Button::A));
    REQUIRE(input.button_down(Button::B)); REQUIRE_FALSE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Release B.");
    input.keyboard_event(KeyCode::B, ScanCode::B, ButtonInput::Up);
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));

    INFO("Do nothing. All buttons should be up.");
    input.update();
    REQUIRE_FALSE(input.button_down(Button::A)); REQUIRE(input.button_up(Button::A)); REQUIRE_FALSE(input.button_pressed(Button::A)); REQUIRE_FALSE(input.button_released(Button::A));
    REQUIRE_FALSE(input.button_down(Button::B)); REQUIRE(input.button_up(Button::B)); REQUIRE_FALSE(input.button_pressed(Button::B)); REQUIRE_FALSE(input.button_released(Button::B));
    REQUIRE_FALSE(input.button_down(Button::C)); REQUIRE(input.button_up(Button::C)); REQUIRE_FALSE(input.button_pressed(Button::C)); REQUIRE_FALSE(input.button_released(Button::C));
}
