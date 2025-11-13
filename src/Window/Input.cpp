#include "Input.hpp"

#include <Math/Vector2.hpp>

#include <cstddef>              // std::size_t

namespace MG3TR
{
    bool Input::IsKeyPressed(const Key key) const
    {
        const auto key_index = static_cast<std::size_t>(key);
        const bool was_released = !m_previous_keys_state[key_index];
        const bool is_hold = m_current_keys_state[key_index];

        return was_released && is_hold;
    }
    
    bool Input::IsMouseButtonPressed(const MouseButton mouse_button) const
    {
        const auto mouse_button_index = static_cast<std::size_t>(mouse_button);
        const bool was_released = !m_previous_mouse_buttons_state[mouse_button_index];
        const bool is_hold = m_current_mouse_buttons_state[mouse_button_index];

        return was_released && is_hold;
    }
    
    bool Input::IsKeyReleased(const Key key) const
    {
        const auto key_index = static_cast<std::size_t>(key);
        const bool was_hold = m_previous_keys_state[key_index];
        const bool is_released = !m_current_keys_state[key_index];

        return was_hold && is_released;
    }
    
    bool Input::IsMouseButtonReleased(const MouseButton mouse_button) const
    {
        const auto mouse_button_index = static_cast<std::size_t>(mouse_button);
        const bool was_hold = m_previous_mouse_buttons_state[mouse_button_index];
        const bool is_released = !m_current_mouse_buttons_state[mouse_button_index];

        return was_hold && is_released;
    }
    
    bool Input::IsKeyHold(const Key key) const
    {
        const auto key_index = static_cast<std::size_t>(key);
        const bool is_hold = m_current_keys_state[key_index];

        return is_hold;
    }
    
    bool Input::IsMouseButtonHold(const MouseButton mouse_button) const
    {
        const auto mouse_button_index = static_cast<std::size_t>(mouse_button);
        const bool is_hold = m_current_mouse_buttons_state[mouse_button_index];

        return is_hold;
    }
    
    Vector2 Input::GetMousePosition() const
    {
        return m_mouse_position;
    }
    
    void Input::UpdateKeyState(const Key key, const bool state)
    {
        const auto key_index = static_cast<std::size_t>(key);

        // This is just to test if key_index is not out of bounds
        (void)(m_previous_keys_state.test(key_index));
        (void)(m_current_keys_state.test(key_index));

        m_previous_keys_state[key_index] = m_current_keys_state[key_index];
        m_current_keys_state[key_index] = state;
    }
    
    void Input::UpdateMouseButtonState(const MouseButton mouse_button, const bool state)
    {
        const auto mouse_button_index = static_cast<std::size_t>(mouse_button);

        // This is just to test if mouse_button_index is not out of bounds
        (void)(m_previous_mouse_buttons_state.test(mouse_button_index));
        (void)(m_current_mouse_buttons_state.test(mouse_button_index));

        m_previous_mouse_buttons_state[mouse_button_index] = m_current_mouse_buttons_state[mouse_button_index];
        m_current_mouse_buttons_state[mouse_button_index] = state;
    }
    
    void Input::UpdateMousePosition(const Vector2 position)
    {
        m_mouse_position = position;
    }
    
    void Input::UpdateScrollOffset(const float offset)
    {
        m_scroll_offset = offset;
    }
}
