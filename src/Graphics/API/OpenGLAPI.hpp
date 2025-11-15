#ifndef MG3TR_SRC_GRAPHICS_API_OPENGLAPI_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_API_OPENGLAPI_HPP_INCLUDED

#include "IGraphicsAPI.hpp"

namespace MG3TR
{
    class OpenGLAPI : public IGraphicsAPI
    {
    public:
        OpenGLAPI() = default;
        virtual ~OpenGLAPI() = default;

        OpenGLAPI(const OpenGLAPI &) = delete;
        OpenGLAPI(OpenGLAPI &&) = delete;

        OpenGLAPI& operator=(const OpenGLAPI &) = delete;
        OpenGLAPI& operator=(OpenGLAPI &&) = delete;

        virtual void Initialise(void *const load_process) override;
        virtual void Finalise() override;

        virtual void SetDepthTest(const bool enable) override;
        virtual void SetBackFaceCulling(const bool enable) override;
        virtual void ClearScreen() override;
        
        virtual TTextureID CreateTexture(const int image_width,
                                         const int image_height,
                                         const int color_channels,
                                         const unsigned char *const image) override;
        virtual void DeleteTexture(const TTextureID texture_id) override;
        virtual void BindTexture(const TTextureID texture_id, const TTextureUnitID texture_unit_id) override;

        virtual TVAOID CreateVAO() override;
        virtual TVBOID CreateVBO(const void *const data,
                                 const std::size_t memory_size,
                                 const std::size_t vertex_size,
                                 const unsigned location) override;
        virtual TIBOID CreateIBO(const void *const data,
                                 const std::size_t memory_size) override;
        
        virtual void DeleteVAO(const TVAOID vao) override;
        virtual void DeleteVBO(const TVBOID vbo) override;
        virtual void DeleteIBO(const TIBOID ibo) override;

        virtual TShaderID CreateShader(const TShaderType type, const std::string &code, const std::string &path) override;
        virtual TShaderProgramID CreateShaderProgram(const TShaderID vertex_shader,
                                                     const TShaderID fragment_shader) override;
        virtual TShaderProgramID CreateShaderProgram(const TShaderID vertex_shader,
                                                     const TShaderID geometry_shader,
                                                     const TShaderID fragment_shader) override;
        virtual void DeleteShader(const TShaderProgramID shader_program, const TShaderID shader) override;
        virtual void DeleteShaderProgram(const TShaderProgramID shader_program) override;
        virtual void UseShader(const TShaderProgramID shader_program) override;
        virtual void SetShaderUniformFloat(const TShaderProgramID shader_program,
                                           const std::string &uniform_name,
                                           const float uniform_value) override;
        virtual void SetShaderUniformInt(const TShaderProgramID shader_program,
                                         const std::string &uniform_name,
                                         const int uniform_value) override;
        virtual void SetShaderUniformUnsigned(const TShaderProgramID shader_program,
                                              const std::string &uniform_name,
                                              const unsigned uniform_value) override;
        virtual void SetShaderUniformVector2(const TShaderProgramID shader_program,
                                             const std::string &uniform_name,
                                             const Vector2 uniform_value) override;
        virtual void SetShaderUniformVector3(const TShaderProgramID shader_program,
                                             const std::string &uniform_name,
                                             const Vector3 uniform_value) override;
        virtual void SetShaderUniformVector4(const TShaderProgramID shader_program,
                                             const std::string &uniform_name,
                                             const Vector4 uniform_value) override;
        virtual void SetShaderUniformMatrix4x4(const TShaderProgramID shader_program,
                                               const std::string &uniform_name,
                                               const Matrix4x4 uniform_value) override;

        virtual void DrawSubMesh(const SubMesh &submesh) override;
    };
}

#endif // MG3TR_SRC_GRAPHICS_API_OPENGLAPI_HPP_INCLUDED
