#include "input.hpp"
#include <algorithm>

namespace sivox {
    InputHandler::InputHandler() {
        std::fill(m_scancodes.begin(), m_scancodes.end(), false);
    }

    void InputHandler::keyboard_event(KeyCode keycode, ScanCode scancode, Input::KeyboardEvent e) {
        m_scancodes[static_cast<int>(scancode)] = e == Input::Down;
    }

    void InputHandler::update() {
        for (ButtonMapping &button : m_buttons) {
            button.down_previously = button.down;
            button.down = false;

            for (Input const& input : button.inputs) {
                if (input.type() == Input::KeyboardScanCode) {
                    if (m_scancodes[static_cast<int>(input.scancode())]) {
                        button.down = true;
                        break;
                    }
                }
            }
        }
    }
}
