#ifndef MG3TR_SRC_WINDOW_KEY_HPP_INCLUDED
#define MG3TR_SRC_WINDOW_KEY_HPP_INCLUDED

namespace MG3TR
{
    enum class Key : unsigned char
    {
        Unknown,               
        Space,                 
        Aposthrophe,    /* ' */
        Comma,          /* , */
        Minus,          /* - */
        Period,         /* . */
        Slash,          /* / */
                            
        Zero,                  
        One,                   
        Two,                   
        Three,                 
        Four,                  
        Five,                  
        Six,                   
        Seven,                 
        Eight,                 
        Nine,                  
                            
        Semicolon,      /* ; */
        Equal,          /* = */
                            
        A,                     
        B,                     
        C,                     
        D,                     
        E,                     
        F,                     
        G,                     
        H,                     
        I,                     
        J,                     
        K,                     
        L,                     
        M,                     
        N,                     
        O,                     
        P,                     
        Q,                     
        R,                     
        S,                     
        T,                     
        U,                     
        V,                     
        W,                     
        X,                     
        Y,                     
        Z,                     
                            
        LeftBracket,    /* [ */
        RightBracket,   /* ] */
        Backslash,      /* \ */
        GraveAccent,    /* ` */
                            
        Escape,                
        Enter,                 
        Tab,                   
        Backspace,             
        Insert,                
        Delete,                
                            
        Right,                 
        Left,                  
        Down,                  
        Up,                    
                            
        PageUp,                
        PageDown,              
        Home,                  
        End,                   
        CapsLock,              
        ScrollLock,            
        NumLock,               
        PrintScreen,           
        Pause,                 
                            
        F1,                    
        F2,                    
        F3,                    
        F4,                    
        F5,                    
        F6,                    
        F7,                    
        F8,                    
        F9,                    
        F10,                   
        F11,                   
        F12,                   
                            
        KeyPadZero,            
        KeyPadOne,             
        KeyPadTwo,             
        KeyPadThree,           
        KeyPadFour,            
        KeyPadFive,            
        KeyPadSix,             
        KeyPadSeven,           
        KeyPadEight,           
        KeyPadNine,            
                            
        KeyPadDecimal,  /* . */
        KeyPadDivide,   /* / */
        KeyPadMultiply, /* * */
        KeyPadSubstract,/* - */
        KeyPadAdd,      /* + */
        KeyPadEnter,           
        KeyPadEqual,           
                            
        LeftShift,             
        LeftControl,           
        LeftAlt,               
        LeftSuper,             
                            
        RightShift,            
        RightControl,          
        RightAlt,              
        RightSuper             
    };
}
#endif // MG3TR_SRC_WINDOW_KEY_HPP_INCLUDED
