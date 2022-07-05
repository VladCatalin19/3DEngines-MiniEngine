#include "Input.hpp"

#include <Math/Vector2.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <cstddef>              // std::size_t

namespace MG3TR
{
    bool Input::IsKeyPressed(Key key) const noexcept
    {
        auto key_index = static_cast<std::size_t>(key);
        return !m_previous_keys_state[key_index] && m_current_keys_state[key_index];
    }
    
    bool Input::IsMouseButtonPressed(MouseButton mouse_button) const noexcept
    {
        auto mouse_button_index = static_cast<std::size_t>(mouse_button);
        return !m_previous_mouse_buttons_state[mouse_button_index] && m_current_mouse_buttons_state[mouse_button_index];
    }
    
    bool Input::IsKeyReleased(Key key) const noexcept
    {
        auto key_index = static_cast<std::size_t>(key);
        return m_previous_keys_state[key_index] && !m_current_keys_state[key_index];
    }
    
    bool Input::IsMouseButtonReleased(MouseButton mouse_button) const noexcept
    {
        auto mouse_button_index = static_cast<std::size_t>(mouse_button);
        return m_previous_mouse_buttons_state[mouse_button_index] && !m_current_mouse_buttons_state[mouse_button_index];
    }
    
    bool Input::IsKeyHold(Key key) const noexcept
    {
        auto key_index = static_cast<std::size_t>(key);
        return m_current_keys_state[key_index];
    }
    
    bool Input::IsMouseButtonHold(MouseButton mouse_button) const noexcept
    {
        auto mouse_button_index = static_cast<std::size_t>(mouse_button);
        return m_current_mouse_buttons_state[mouse_button_index];
    }
    
    Vector2 Input::GetMousePosition() const noexcept
    {
        return m_mouse_position;
    }
    
    void Input::UpdateKeyState(Key key, bool state) try
    {
        auto key_index = static_cast<std::size_t>(key);

        // This is just to test if key_index is not out of bounds
        (void)(m_previous_keys_state.test(key_index));
        (void)(m_current_keys_state.test(key_index));

        m_previous_keys_state[key_index] = m_current_keys_state[key_index];
        m_current_keys_state[key_index] = state;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void Input::UpdateMouseButtonState(MouseButton mouse_button, bool state) try
    {
        auto mouse_button_index = static_cast<std::size_t>(mouse_button);

        // This is just to test if mouse_button_index is not out of bounds
        (void)(m_previous_mouse_buttons_state.test(mouse_button_index));
        (void)(m_current_mouse_buttons_state.test(mouse_button_index));

        m_previous_mouse_buttons_state[mouse_button_index] = m_current_mouse_buttons_state[mouse_button_index];
        m_current_mouse_buttons_state[mouse_button_index] = state;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void Input::UpdateMousePosition(Vector2 position) noexcept
    {
        m_mouse_position = position;
    }
    
    void Input::UpdateScrollOffset(float offset) noexcept
    {
        m_scroll_offset = offset;
    }
}
