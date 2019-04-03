#include <tuple>
#include <memory>
#include <iostream>
#include <SDL.h>
#include <input.hpp>

using namespace sivox;

namespace {
    bool operator==(Input::ButtonMapping const& a, Input::ButtonMapping const& b) {
        return std::tie(a.value, a.in_use, a.code, a.use_scancode, a.down, a.pressed, a.released, a.prev_down) 
               ==
               std::tie(b.value, b.in_use, b.code, b.use_scancode, b.down, b.pressed, b.released, b.prev_down);
    }
    bool operator!=(Input::ButtonMapping const& a, Input::ButtonMapping const& b) {
        return !(a == b);
    }

    enum class KeyState {
        Down,
        Up
    };

    SDL_Event key_event(int keycode, SDL_Scancode scancode, KeyState state) {
        static int s_timestamp = 0;

        SDL_KeyboardEvent keyboard = {};
        keyboard.type = state == KeyState::Down ? SDL_KEYDOWN : SDL_KEYUP;
        keyboard.timestamp = s_timestamp++;
        keyboard.windowID = 0; // TODO: Think if we need to set the [windowID] to anything meaningful.
        keyboard.state = state == KeyState::Down ? SDL_PRESSED : SDL_RELEASED; // TODO: How is [state] different from [type]?

        keyboard.keysym = {};
        keyboard.keysym.scancode = scancode;
        keyboard.keysym.sym = keycode;
        keyboard.keysym.mod = 0;

        SDL_Event event = {};
        event.type = state == KeyState::Down ? SDL_KEYDOWN : SDL_KEYUP;
        event.key = keyboard;

        return event;
    }

    SDL_Event key_event(KeyCode keycode, KeyState state) {
        int kc = static_cast<int>(keycode);
        return key_event(kc, SDL_GetScancodeFromKey(kc), state);
    }

    SDL_Event key_event(ScanCode scancode, KeyState state) {
        auto sc = static_cast<SDL_Scancode>(scancode);
        return key_event(SDL_GetKeyFromScancode(sc), sc, state);
    }
}

std::ostream &operator<<(std::ostream &stream, Input::ButtonMapping const& bm) {
    stream << "("
           << bm.value
           << " "
           << bm.code
           << " "
           << (bm.use_scancode ? "true" : "false")
           << ")";
    return stream;
}
#include <catch2/catch.hpp>


TEST_CASE("Input tests", "[input]") {
    int sdl_status = SDL_Init(SDL_INIT_EVENTS);
    REQUIRE(sdl_status == 0);

    SECTION("Map buttons (simple shooter controls)", "[input][buttons]") {
        enum class Button {
            Up,
            Down,
            Left,
            Right,
            Jump,
            Shoot,
            Inventory,
            TeamChat,
            GroupChat
        };

        std::unique_ptr<Input> input(new Input);
        input->map_button(Button::Up, ScanCode::W);
        input->map_button(Button::Down, ScanCode::S);
        input->map_button(Button::Left, ScanCode::A);
        input->map_button(Button::Right, ScanCode::D);
        input->map_button(Button::Jump, ScanCode::Space);
        input->map_button(Button::Inventory, KeyCode::I);
        input->map_button(Button::TeamChat, KeyCode::T);
        input->map_button(Button::GroupChat, KeyCode::G);

        std::vector<Input::ButtonMapping> values {
            { static_cast<int>(Button::Up), true, static_cast<int>(ScanCode::W), true, false, false, false, false },
            { static_cast<int>(Button::Down), true, static_cast<int>(ScanCode::S), true, false, false, false, false },
            { static_cast<int>(Button::Left), true, static_cast<int>(ScanCode::A), true, false, false, false, false },
            { static_cast<int>(Button::Right), true, static_cast<int>(ScanCode::D), true, false, false, false, false },
            { static_cast<int>(Button::Jump), true, static_cast<int>(ScanCode::Space), true, false, false, false, false },
            { static_cast<int>(Button::Inventory), true, static_cast<int>(KeyCode::I), false, false, false, false, false },
            { static_cast<int>(Button::TeamChat), true, static_cast<int>(KeyCode::T), false, false, false, false, false },
            { static_cast<int>(Button::GroupChat), true, static_cast<int>(KeyCode::G), false, false, false, false, false }
        };

        using Catch::Equals;
        REQUIRE_THAT(
            input->m_buttons,
            Equals(values)
        );
    }

    SECTION("Button:KeyCode tests", "[input][buttons]") {
        enum class Button {
            A,
            B,
            C
        };

        std::unique_ptr<Input> input(new Input);

        input->map_button(Button::A, KeyCode::A);
        input->map_button(Button::B, KeyCode::B);
        input->map_button(Button::C, KeyCode::C);

        SECTION("Two buttons, one input") {
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::A, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::B, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::A, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::B, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));
        }

        SECTION("Simulataneous release") {
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::A, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::B, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::A, KeyState::Up));
            input->process_sdl_event(key_event(KeyCode::B, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));
        }

        SECTION("Simulataneous press") {
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::A, KeyState::Down));
            input->process_sdl_event(key_event(KeyCode::B, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::A, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(KeyCode::B, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));
        }
    }

    SECTION("Button:ScanCode tests", "[input][buttons]") {
        enum class Button {
            A,
            B,
            C
        };

        std::unique_ptr<Input> input(new Input);

        input->map_button(Button::A, ScanCode::A);
        input->map_button(Button::B, ScanCode::B);
        input->map_button(Button::C, ScanCode::C);

        SECTION("Two buttons, one input") {
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::A, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::B, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::A, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::B, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));
        }

        SECTION("Simulataneous release") {
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::A, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::B, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::A, KeyState::Up));
            input->process_sdl_event(key_event(ScanCode::B, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));
        }

        SECTION("Simulataneous press") {
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::A, KeyState::Down));
            input->process_sdl_event(key_event(ScanCode::B, KeyState::Down));
            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(!input->button_up(Button::A)); CHECK(input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::A, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(input->button_released(Button::A));
            CHECK(!input->button_up(Button::B)); CHECK(input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->process_sdl_event(key_event(ScanCode::B, KeyState::Up));
            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));

            input->update();
            CHECK(input->button_up(Button::A)); CHECK(!input->button_down(Button::A)); CHECK(!input->button_pressed(Button::A)); CHECK(!input->button_released(Button::A));
            CHECK(input->button_up(Button::B)); CHECK(!input->button_down(Button::B)); CHECK(!input->button_pressed(Button::B)); CHECK(!input->button_released(Button::B));
            CHECK(input->button_up(Button::C)); CHECK(!input->button_down(Button::C)); CHECK(!input->button_pressed(Button::C)); CHECK(!input->button_released(Button::C));
        }
    }

    SDL_Quit();
}
