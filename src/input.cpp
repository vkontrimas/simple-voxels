#include <iostream>
#include "input.hpp"
#include <algorithm>

namespace sivox {
    InputHandler::InputHandler() {
        std::fill(m_scancodes.begin(), m_scancodes.end(), false);
    }

    void InputHandler::keyboard_event(KeyCode keycode, ScanCode scancode, ButtonInput::KeyboardEvent e) {
        bool down = e == ButtonInput::Down;
        m_scancodes[static_cast<int>(scancode)] = down;
        if (down) {
            m_keycodes.push_back(keycode);
        }
        else {
            m_keycodes.erase(std::remove(m_keycodes.begin(), m_keycodes.end(), keycode), m_keycodes.end());
        }
    }

    void InputHandler::update() {
        /*
         * TODO: Reduce duplication. We search for button inputs pressed by scancode or keycode at least three times with 
         * identical behaviour. It will get worse as we add Joystick and Controller buttons.
         */
        for (ButtonMapping &button : m_buttons) {
            button.down_previously = button.down;
            bool down = false;
            for (ButtonInput const& input : button.inputs) {
                if (input.type() == ButtonInput::KeyboardScanCode) {
                    down = m_scancodes[static_cast<int>(input.scancode())];
                }
                else if (input.type() == ButtonInput::KeyboardKeyCode) {
                    /*
                     * O(mn) where m = number of KeyCode inputs
                     *             n = number of KeyCodes being held
                     * 
                     * Should be passable. Could be improved.
                     */
                    auto result = std::find(m_keycodes.begin(), m_keycodes.end(), input.keycode());
                    down = result != m_keycodes.end();
                }

                if (down) { break; }
            }
            button.down = down;
        }

        for (AxisMapping &axis : m_axes) {
            for (AxisInput const& input : axis.inputs) {
                if (input.type() == AxisInput::DualButtonInput) {
                    auto const& min_input = input.min();
                    bool min_down = false;
                    if (min_input.type() == ButtonInput::KeyboardScanCode) {
                        min_down = m_scancodes[static_cast<int>(min_input.scancode())];
                    }
                    else if (min_input.type() == ButtonInput::KeyboardKeyCode) {
                        auto result = std::find(m_keycodes.begin(), m_keycodes.end(), min_input.keycode());
                        min_down = result != m_keycodes.end();
                    }

                    auto const& max_input = input.max();
                    bool max_down = false;
                    if (max_input.type() == ButtonInput::KeyboardScanCode) {
                        max_down = m_scancodes[static_cast<int>(max_input.scancode())];
                    }
                    else if (max_input.type() == ButtonInput::KeyboardKeyCode) {
                        auto result = std::find(m_keycodes.begin(), m_keycodes.end(), max_input.keycode());
                        max_down = result != m_keycodes.end();
                    }

                    float value = 0.0f;
                    if (min_down) { value -= 1.0f; }
                    if (max_down) { value += 1.0f; }

                    axis.latest_value = value;
                }
            }
        }
    }
}
