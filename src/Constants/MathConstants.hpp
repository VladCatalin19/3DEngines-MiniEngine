#ifndef MG3TR_SRC_CONSTANTS_MATHCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_MATHCONSTANTS_HPP_INCLUDED

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Quaternion.hpp>

namespace MG3TR
{
    namespace Vector2Constants
    {
        constexpr Vector2 k_zero(  0.0F,  0.0F);
        constexpr Vector2 k_one(   1.0F,  1.0F);
        constexpr Vector2 k_up(    0.0F,  1.0F);
        constexpr Vector2 k_down(  0.0F, -1.0F);
        constexpr Vector2 k_left(  1.0F,  0.0F);
        constexpr Vector2 k_right(-1.0F,  0.0F);
    }

    namespace Vector3Constants
    {
        constexpr Vector3 k_zero(      0.0F,  0.0F,  0.0F);
        constexpr Vector3 k_one(       1.0F,  1.0F,  1.0F);
        constexpr Vector3 k_up(        0.0F,  1.0F,  0.0F);
        constexpr Vector3 k_down(      0.0F, -1.0F,  0.0F);
        constexpr Vector3 k_left(      1.0F,  0.0F,  0.0F);
        constexpr Vector3 k_right(    -1.0F,  0.0F,  0.0F);
        constexpr Vector3 k_forwards(  0.0F,  0.0F,  1.0F);
        constexpr Vector3 k_backwards( 0.0F,  0.0F, -1.0F);
    }

    namespace Vector4Constants
    {
        constexpr Vector4 k_zero(0.0F,  0.0F,  0.0F, 0.0F);
        constexpr Vector4 k_one( 1.0F,  1.0F,  1.0F, 1.0F);
    }

    namespace QuaternionConstants
    {
        constexpr Quaternion k_identity(1.0F, 0.0F, 0.0F, 0.0F);
    }
}

#endif // MG3TR_SRC_CONSTANTS_MATHCONSTANTS_HPP_INCLUDED
