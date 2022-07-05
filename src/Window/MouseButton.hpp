#ifndef MG3TR_SRC_WINDOW_MOUSEBUTTON_HPP_INCLUDED
#define MG3TR_SRC_WINDOW_MOUSEBUTTON_HPP_INCLUDED

#define ALL_MOUSE_BUTTONS(identifier) \
    identifier Left,                  \
    identifier Right,                 \
    identifier Middle,                \
    identifier Four,                  \
    identifier Five,                  \
    identifier Six,                   \
    identifier Seven,                 \
    identifier Eight

namespace MG3TR
{
    enum class MouseButton : unsigned char
    {
        ALL_MOUSE_BUTTONS()
    };
}

#endif // MG3TR_SRC_WINDOW_MOUSEBUTTON_HPP_INCLUDED
