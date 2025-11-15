#ifndef MG3TR_SRC_GRAPHICS_API_GRAPHICSTYPES_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_API_GRAPHICSTYPES_HPP_INCLUDED

namespace MG3TR
{
    using TTextureID = unsigned;
    using TTextureUnitID = unsigned;
    using TVAOID = unsigned;
    using TVBOID = unsigned;
    using TIBOID = unsigned;
    using TShaderID = unsigned;
    using TShaderProgramID = unsigned;

    enum class TShaderType : unsigned char
    {
        VertexShader,
        FragmentShader,
        GeometryShader
    };
}

#endif // MG3TR_SRC_GRAPHICS_API_GRAPHICSTYPES_HPP_INCLUDED
