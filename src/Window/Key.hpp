#ifndef MG3TR_SRC_WINDOW_KEY_HPP_INCLUDED
#define MG3TR_SRC_WINDOW_KEY_HPP_INCLUDED

#define ALL_KEY_CODES(identifier)      \
    identifier Unkown,                 \
    identifier Space,                  \
    identifier Aposthrophe,    /* ' */ \
    identifier Comma,          /* , */ \
    identifier Minus,          /* - */ \
    identifier Period,         /* . */ \
    identifier Slash,          /* / */ \
                                       \
    identifier Zero,                   \
    identifier One,                    \
    identifier Two,                    \
    identifier Three,                  \
    identifier Four,                   \
    identifier Five,                   \
    identifier Six,                    \
    identifier Seven,                  \
    identifier Eight,                  \
    identifier Nine,                   \
                                       \
    identifier Semicolon,      /* ; */ \
    identifier Equal,          /* = */ \
                                       \
    identifier A,                      \
    identifier B,                      \
    identifier C,                      \
    identifier D,                      \
    identifier E,                      \
    identifier F,                      \
    identifier G,                      \
    identifier H,                      \
    identifier I,                      \
    identifier J,                      \
    identifier K,                      \
    identifier L,                      \
    identifier M,                      \
    identifier N,                      \
    identifier O,                      \
    identifier P,                      \
    identifier Q,                      \
    identifier R,                      \
    identifier S,                      \
    identifier T,                      \
    identifier U,                      \
    identifier V,                      \
    identifier W,                      \
    identifier X,                      \
    identifier Y,                      \
    identifier Z,                      \
                                       \
    identifier LeftBracket,    /* [ */ \
    identifier RightBracket,   /* ] */ \
    identifier Backslash,      /* \ */ \
    identifier GraveAccent,    /* ` */ \
                                       \
    identifier Escape,                 \
    identifier Enter,                  \
    identifier Tab,                    \
    identifier Backspace,              \
    identifier Insert,                 \
    identifier Delete,                 \
                                       \
    identifier Right,                  \
    identifier Left,                   \
    identifier Down,                   \
    identifier Up,                     \
                                       \
    identifier PageUp,                 \
    identifier PageDown,               \
    identifier Home,                   \
    identifier End,                    \
    identifier CapsLock,               \
    identifier ScrollLock,             \
    identifier NumLock,                \
    identifier PrintScreen,            \
    identifier Pause,                  \
                                       \
    identifier F1,                     \
    identifier F2,                     \
    identifier F3,                     \
    identifier F4,                     \
    identifier F5,                     \
    identifier F6,                     \
    identifier F7,                     \
    identifier F8,                     \
    identifier F9,                     \
    identifier F10,                    \
    identifier F11,                    \
    identifier F12,                    \
                                       \
    identifier KeyPadZero,             \
    identifier KeyPadOne,              \
    identifier KeyPadTwo,              \
    identifier KeyPadThree,            \
    identifier KeyPadFour,             \
    identifier KeyPadFive,             \
    identifier KeyPadSix,              \
    identifier KeyPadSeven,            \
    identifier KeyPadEight,            \
    identifier KeyPadNine,             \
                                       \
    identifier KeyPadDecimal,  /* . */ \
    identifier KeyPadDivide,   /* / */ \
    identifier KeyPadMultiply, /* * */ \
    identifier KeyPadSubstract,/* - */ \
    identifier KeyPadAdd,      /* + */ \
    identifier KeyPadEnter,            \
    identifier KeyPadEqual,            \
                                       \
    identifier LeftShift,              \
    identifier LeftControl,            \
    identifier LeftAlt,                \
    identifier LeftSuper,              \
                                       \
    identifier RightShift,             \
    identifier RightControl,           \
    identifier RightAlt,               \
    identifier RightSuper              

namespace MG3TR
{
    enum class Key : unsigned char
    {
        ALL_KEY_CODES()
    };
}
#endif // MG3TR_SRC_WINDOW_KEY_HPP_INCLUDED
