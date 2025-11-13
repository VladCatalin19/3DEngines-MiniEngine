#ifndef MG3TR_SRC_WINDOW_INPUT_HPP_INCLUDED
#define MG3TR_SRC_WINDOW_INPUT_HPP_INCLUDED

#include "Key.hpp"
#include "MouseButton.hpp"

#include <Constants/InputConstants.hpp>

#include <Math/Vector2.hpp>

#include <bitset>

namespace MG3TR
{
    class Input
    {
    private:
        std::bitset<InputConstants::k_keys_number> m_previous_keys_state;
        std::bitset<InputConstants::k_mouse_buttons_number> m_previous_mouse_buttons_state;

        std::bitset<InputConstants::k_keys_number> m_current_keys_state;
        std::bitset<InputConstants::k_mouse_buttons_number> m_current_mouse_buttons_state;

        Vector2 m_mouse_position;

        float m_scroll_offset;

    public:
        Input()= default;
        virtual ~Input() = default;

        Input(const Input &) = delete;
        Input& operator=(const Input &) = delete;

        Input(Input &&) = default;
        Input& operator=(Input &&) = default;

        bool IsKeyPressed(const Key key) const;
        bool IsMouseButtonPressed(const MouseButton mouse_button) const;

        bool IsKeyReleased(const Key key) const;
        bool IsMouseButtonReleased(const MouseButton mouse_button) const;

        bool IsKeyHold(const Key key) const;
        bool IsMouseButtonHold(const MouseButton mouse_button) const;

        Vector2 GetMousePosition() const;

        void UpdateKeyState(const Key key, const bool state);
        void UpdateMouseButtonState(const MouseButton mouse_button, const bool state);
        void UpdateMousePosition(const Vector2 position);
        void UpdateScrollOffset(const float offset);
    };
}

#endif // MG3TR_SRC_WINDOW_INPUT_HPP_INCLUDED
