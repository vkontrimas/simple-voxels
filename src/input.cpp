#include <iostream>
#include "input.hpp"
#include <algorithm>

namespace sivox {
    InputHandler::InputHandler() {
        std::fill(m_scancodes.begin(), m_scancodes.end(), false);
    }

    void InputHandler::keyboard_event(KeyCode keycode, ScanCode scancode, Input::KeyboardEvent e) {
        bool down = e == Input::Down;
        m_scancodes[static_cast<int>(scancode)] = down;
        if (down) {
            m_keycodes.push_back(keycode);
        }
        else {
            m_keycodes.erase(std::remove(m_keycodes.begin(), m_keycodes.end(), keycode), m_keycodes.end());
        }
    }

    void InputHandler::update() {
        for (ButtonMapping &button : m_buttons) {
            button.down_previously = button.down;
            bool down = false;
            for (Input const& input : button.inputs) {
                if (input.type() == Input::KeyboardScanCode) {
                    if (m_scancodes[static_cast<int>(input.scancode())]) {
                        down = true;
                    }
                }
                else if (input.type() == Input::KeyboardKeyCode) {
                    /*
                     * O(mn) where m = number of KeyCode inputs
                     *             n = number of KeyCodes being held
                     * 
                     * Should be passable. Could be improved.
                     */
                    auto result = std::find(m_keycodes.begin(), m_keycodes.end(), input.keycode());
                    if (result != m_keycodes.end()) {
                        down = true;
                    }
                }

                if (down) { break; }
            }
            button.down = down;
        }
    }
}
