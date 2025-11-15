#ifndef MG3TR_SRC_GRAPHICS_API_IGRAPHICSAPI_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_API_IGRAPHICSAPI_HPP_INCLUDED

#include "GraphicsTypes.hpp"

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Matrix4x4.hpp>

#include <string>

namespace MG3TR
{
    class SubMesh;

    class IGraphicsAPI
    {
    public:
        virtual ~IGraphicsAPI() = default;

        virtual void Initialise(void *const load_process) = 0;
        virtual void Finalise() = 0;

        virtual void SetDepthTest(const bool enable) = 0;
        virtual void SetBackFaceCulling(const bool enable) = 0;
        virtual void ClearScreen() = 0;

        virtual TTextureID CreateTexture(const int image_width,
                                         const int image_height,
                                         const int color_channels,
                                         const unsigned char *const image) = 0;
        virtual void DeleteTexture(const TTextureID texture_id) = 0;
        virtual void BindTexture(const TTextureID texture_id, const TTextureUnitID texture_unit_id) = 0;

        virtual TVAOID CreateVAO() = 0;
        virtual TVBOID CreateVBO(const void *const data,
                                 const std::size_t memory_size,
                                 const std::size_t vertex_size,
                                 const unsigned location) = 0;
        virtual TIBOID CreateIBO(const void *const data,
                                 const std::size_t memory_size) = 0;
        
        virtual void DeleteVAO(const TVAOID vao) = 0;
        virtual void DeleteVBO(const TVBOID vbo) = 0;
        virtual void DeleteIBO(const TIBOID ibo) = 0;

        virtual TShaderID CreateShader(const TShaderType type, const std::string &code, const std::string &path) = 0;
        virtual TShaderProgramID CreateShaderProgram(const TShaderID vertex_shader,
                                                     const TShaderID fragment_shader) = 0;
        virtual TShaderProgramID CreateShaderProgram(const TShaderID vertex_shader,
                                                     const TShaderID geometry_shader,
                                                     const TShaderID fragment_shader) = 0;
        virtual void DeleteShader(const TShaderProgramID shader_program, const TShaderID shader) = 0;
        virtual void DeleteShaderProgram(const TShaderProgramID shader_program) = 0;
        virtual void SetShaderUniformFloat(const TShaderProgramID shader_program,
                                           const std::string &uniform_name,
                                           const float uniform_value) = 0;
        virtual void UseShader(const TShaderProgramID shader_program) = 0;
        virtual void SetShaderUniformInt(const TShaderProgramID shader_program,
                                         const std::string &uniform_name,
                                         const int uniform_value) = 0;
        virtual void SetShaderUniformUnsigned(const TShaderProgramID shader_program,
                                              const std::string &uniform_name,
                                              const unsigned uniform_value) = 0;
        virtual void SetShaderUniformVector2(const TShaderProgramID shader_program,
                                             const std::string &uniform_name,
                                             const Vector2 uniform_value) = 0;
        virtual void SetShaderUniformVector3(const TShaderProgramID shader_program,
                                             const std::string &uniform_name,
                                             const Vector3 uniform_value) = 0;
        virtual void SetShaderUniformVector4(const TShaderProgramID shader_program,
                                             const std::string &uniform_name,
                                             const Vector4 uniform_value) = 0;
        virtual void SetShaderUniformMatrix4x4(const TShaderProgramID shader_program,
                                               const std::string &uniform_name,
                                               const Matrix4x4 uniform_value) = 0;
        
        virtual void DrawSubMesh(const SubMesh &submesh) = 0;
    };
}

#endif // MG3TR_SRC_GRAPHICS_API_IGRAPHICSAPI_HPP_INCLUDED
