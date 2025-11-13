#ifndef MG3TR_SRC_CONSTANTS_INPUTCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_INPUTCONSTANTS_HPP_INCLUDED

#include <Window/Key.hpp>
#include <Window/MouseButton.hpp>

#include <GLFW/glfw3.h>

#include <unordered_map>

namespace MG3TR::InputConstants
{
    const std::size_t k_keys_number = 105;
    const std::size_t k_mouse_buttons_number = 8;

    const std::unordered_map<int, Key> k_glfw_keys_to_input_keys = {
        { GLFW_KEY_UNKNOWN, Key::Unknown },
        { GLFW_KEY_SPACE, Key::Space },
        { GLFW_KEY_APOSTROPHE, Key::Aposthrophe },
        { GLFW_KEY_COMMA, Key::Comma },
        { GLFW_KEY_MINUS, Key::Minus },
        { GLFW_KEY_PERIOD, Key::Period },
        { GLFW_KEY_SLASH, Key::Slash },

        { GLFW_KEY_0, Key::Zero },
        { GLFW_KEY_1, Key::One },
        { GLFW_KEY_2, Key::Two},
        { GLFW_KEY_3, Key::Three },
        { GLFW_KEY_4, Key::Four },
        { GLFW_KEY_5, Key::Five },
        { GLFW_KEY_6, Key::Six },
        { GLFW_KEY_7, Key::Seven },
        { GLFW_KEY_8, Key::Eight },
        { GLFW_KEY_9, Key::Nine },

        { GLFW_KEY_SEMICOLON, Key::Semicolon },
        { GLFW_KEY_EQUAL, Key::Equal },

        { GLFW_KEY_A, Key::A },
        { GLFW_KEY_B, Key::B },
        { GLFW_KEY_C, Key::C },
        { GLFW_KEY_D, Key::D },
        { GLFW_KEY_E, Key::E },
        { GLFW_KEY_F, Key::F },
        { GLFW_KEY_G, Key::G },
        { GLFW_KEY_H, Key::H },
        { GLFW_KEY_I, Key::I },
        { GLFW_KEY_J, Key::J },
        { GLFW_KEY_K, Key::K },
        { GLFW_KEY_L, Key::L },
        { GLFW_KEY_M, Key::M },
        { GLFW_KEY_N, Key::N },
        { GLFW_KEY_O, Key::O },
        { GLFW_KEY_P, Key::P },
        { GLFW_KEY_Q, Key::Q },
        { GLFW_KEY_R, Key::R },
        { GLFW_KEY_S, Key::S },
        { GLFW_KEY_T, Key::T },
        { GLFW_KEY_U, Key::U },
        { GLFW_KEY_V, Key::V },
        { GLFW_KEY_W, Key::W },
        { GLFW_KEY_X, Key::X },
        { GLFW_KEY_Y, Key::Y },
        { GLFW_KEY_Z, Key::Z },

        { GLFW_KEY_LEFT_BRACKET, Key::LeftBracket },
        { GLFW_KEY_BACKSLASH, Key::RightBracket },
        { GLFW_KEY_RIGHT_BRACKET, Key::Backslash },
        { GLFW_KEY_GRAVE_ACCENT, Key::GraveAccent },

        { GLFW_KEY_ESCAPE, Key::Escape },
        { GLFW_KEY_ENTER, Key::Enter },
        { GLFW_KEY_TAB, Key::Tab },
        { GLFW_KEY_BACKSPACE, Key::Backspace },
        { GLFW_KEY_INSERT, Key::Insert },
        { GLFW_KEY_DELETE, Key::Delete },

        { GLFW_KEY_RIGHT, Key::Right },
        { GLFW_KEY_LEFT, Key::Left },
        { GLFW_KEY_DOWN, Key::Down },
        { GLFW_KEY_UP, Key::Up },

        { GLFW_KEY_PAGE_UP, Key::PageUp },
        { GLFW_KEY_PAGE_DOWN, Key::PageDown },
        { GLFW_KEY_HOME, Key::Home },
        { GLFW_KEY_END, Key::End },
        { GLFW_KEY_CAPS_LOCK, Key::CapsLock },
        { GLFW_KEY_SCROLL_LOCK, Key::ScrollLock },
        { GLFW_KEY_NUM_LOCK, Key::NumLock },
        { GLFW_KEY_PRINT_SCREEN, Key::PrintScreen },
        { GLFW_KEY_PAUSE, Key::Pause },

        { GLFW_KEY_F1, Key::F1 },
        { GLFW_KEY_F2, Key::F2 },
        { GLFW_KEY_F3, Key::F3 },
        { GLFW_KEY_F4, Key::F4 },
        { GLFW_KEY_F5, Key::F5 },
        { GLFW_KEY_F6, Key::F6 },
        { GLFW_KEY_F7, Key::F7 },
        { GLFW_KEY_F8, Key::F8 },
        { GLFW_KEY_F9, Key::F9 },
        { GLFW_KEY_F10, Key::F10 },
        { GLFW_KEY_F11, Key::F11 },
        { GLFW_KEY_F12, Key::F12 },

        { GLFW_KEY_KP_0, Key::KeyPadZero },
        { GLFW_KEY_KP_1, Key::KeyPadOne },
        { GLFW_KEY_KP_2, Key::KeyPadTwo },
        { GLFW_KEY_KP_3, Key::KeyPadThree },
        { GLFW_KEY_KP_4, Key::KeyPadFour },
        { GLFW_KEY_KP_5, Key::KeyPadFive },
        { GLFW_KEY_KP_6, Key::KeyPadSix },
        { GLFW_KEY_KP_7, Key::KeyPadSeven },
        { GLFW_KEY_KP_8, Key::KeyPadEight},
        { GLFW_KEY_KP_9, Key::KeyPadNine },

        { GLFW_KEY_KP_DECIMAL, Key::KeyPadDecimal},
        { GLFW_KEY_KP_DIVIDE, Key::KeyPadDivide },
        { GLFW_KEY_KP_MULTIPLY, Key::KeyPadMultiply },
        { GLFW_KEY_KP_SUBTRACT, Key::KeyPadSubstract },
        { GLFW_KEY_KP_ADD, Key::KeyPadAdd },
        { GLFW_KEY_KP_ENTER, Key::KeyPadEnter },
        { GLFW_KEY_KP_EQUAL, Key::KeyPadEqual},
    
        { GLFW_KEY_LEFT_SHIFT, Key::LeftShift },
        { GLFW_KEY_LEFT_CONTROL, Key::LeftControl },
        { GLFW_KEY_LEFT_ALT, Key::LeftAlt },
        { GLFW_KEY_LEFT_SUPER, Key::LeftSuper },

        { GLFW_KEY_RIGHT_SHIFT, Key::RightShift },
        { GLFW_KEY_RIGHT_CONTROL, Key::RightControl },
        { GLFW_KEY_RIGHT_ALT, Key::RightAlt },
        { GLFW_KEY_RIGHT_SUPER, Key::RightSuper }
    };

    const std::unordered_map<int, MouseButton> k_glfw_mouse_buttons_to_input_mouse_buttons = {
        { GLFW_MOUSE_BUTTON_LEFT, MouseButton::Left },
        { GLFW_MOUSE_BUTTON_RIGHT, MouseButton::Right },
        { GLFW_MOUSE_BUTTON_MIDDLE, MouseButton::Middle },

        { GLFW_MOUSE_BUTTON_4, MouseButton::Four },
        { GLFW_MOUSE_BUTTON_5, MouseButton::Five },
        { GLFW_MOUSE_BUTTON_6, MouseButton::Six },
        { GLFW_MOUSE_BUTTON_7, MouseButton::Seven },
        { GLFW_MOUSE_BUTTON_8, MouseButton::Eight }
    };
}

#endif // MG3TR_SRC_CONSTANTS_INPUTCONSTANTS_HPP_INCLUDED
