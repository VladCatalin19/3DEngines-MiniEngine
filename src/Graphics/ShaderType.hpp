#ifndef M3GTR_SRC_GRAPHICS_SHADERTYPE_HPP_INCLUDED
#define M3GTR_SRC_GRAPHICS_SHADERTYPE_HPP_INCLUDED

namespace MG3TR
{
    enum class ShaderType : unsigned char
    {
        General = 0,
        FragmentNormal = 1,
        TextureAndLighting = 2,
        Texture = 3
    };
}

#endif // M3GTR_SRC_GRAPHICS_SHADERTYPE_HPP_INCLUDED
