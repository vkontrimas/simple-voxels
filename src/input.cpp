#include "input.hpp"

namespace sivox {
    void Input::process_sdl_event(SDL_Event const& event) {
        switch (event.type) {
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            m_scancode_state[event.key.keysym.scancode] = event.type == SDL_KEYDOWN;
            break;
        default:
            break;
        }
    }

    void Input::update() {
        for (ButtonMapping &button : m_buttons) {
            button.prev_down = button.down;

            int code = button.code;
            if (!button.use_scancode) {
                code = SDL_GetScancodeFromKey(code);
            }
            button.down = m_scancode_state[code];

            button.pressed = !button.prev_down && button.down;
            button.released = button.prev_down && !button.down;
        }
    }

    void Input::map_button(int value, int code, bool use_scancode) {
        if (m_buttons.size() < value + 1) {
            m_buttons.resize(value + 1);
        }

        // TODO: Error if the button is already in use? Need to report this somehow. Maybe return result?
        if (!m_buttons[value].in_use) {
            ButtonMapping button = {};
            button.value = value;
            button.code = code;
            button.use_scancode = use_scancode;
            button.in_use = true;

            m_buttons[value] = button;
        }
    }

    bool Input::button_up(int value) {
        // TODO: Error when button is not mapped.
        return value >= 0 && value < m_buttons.size() && !m_buttons[value].down;
    }

    bool Input::button_down(int value) {
        // TODO: Error when button is not mapped.
        return value >= 0 && value < m_buttons.size() && m_buttons[value].down;
    }

    bool Input::button_pressed(int value) {
        // TODO: Error when button is not mapped.
        return value >= 0 && value < m_buttons.size() && m_buttons[value].pressed;
    }

    bool Input::button_released(int value) {
        // TODO: Error when button is not mapped.
        return value >= 0 && value < m_buttons.size() && m_buttons[value].released;
    }
}
