#ifndef MG3TR_SRC_WINDOW_INPUT_HPP_INCLUDED
#define MG3TR_SRC_WINDOW_INPUT_HPP_INCLUDED

#include "Key.hpp"
#include "MouseButton.hpp"

#include <Constants/InputConstants.hpp>

#include <Math/Vector2.hpp>

#include <bitset>               // std::bitset

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
        Input() noexcept = default;
        virtual ~Input() noexcept = default;

        Input(const Input &) = delete;
        Input& operator=(const Input &) = delete;

        Input(Input &&) noexcept = default;
        Input& operator=(Input &&) noexcept = default;

        bool IsKeyPressed(Key key) const noexcept;
        bool IsMouseButtonPressed(MouseButton mouse_button) const noexcept;

        bool IsKeyReleased(Key key) const noexcept;
        bool IsMouseButtonReleased(MouseButton mouse_button) const noexcept;

        bool IsKeyHold(Key key) const noexcept;
        bool IsMouseButtonHold(MouseButton mouse_button) const noexcept;

        Vector2 GetMousePosition() const noexcept;

        void UpdateKeyState(Key key, bool state);
        void UpdateMouseButtonState(MouseButton mouse_button, bool state);
        void UpdateMousePosition(Vector2 position) noexcept;
        void UpdateScrollOffset(float offset) noexcept;
    };
}

#endif // MG3TR_SRC_WINDOW_INPUT_HPP_INCLUDED
