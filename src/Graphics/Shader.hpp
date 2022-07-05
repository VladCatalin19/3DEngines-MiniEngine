#ifndef MG3TR_SRC_GRAPHICS_SHADER_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SHADER_HPP_INCLUDED

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Matrix4x4.hpp>
#include <Scene/IJsonSerializeable.hpp>

#include <glad/glad.h>          // GLuint

#include <string>               // std::string

namespace MG3TR
{
    class Shader : public IJsonSerializeable
    {
    private:
        GLuint m_vertex_shader;
        GLuint m_geometry_shader;
        GLuint m_fragment_shader;

        GLuint m_program;

        std::string m_vertex_shader_path;
        std::string m_geometry_shader_path;
        std::string m_fragment_shader_path;

    public:
        Shader() noexcept = default;

        Shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
        Shader(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
               const std::string &fragment_shader_path);

        virtual ~Shader() noexcept;

        Shader(const Shader &);
        Shader& operator=(const Shader &);

        Shader(Shader &&);
        Shader& operator=(Shader &&);

        GLuint GetVertexShader() const noexcept { return m_vertex_shader; }
        GLuint GetGeometryShader() const noexcept { return m_geometry_shader; }
        GLuint GetFragmentShader() const noexcept { return m_fragment_shader; }

        GLuint GetProgram() const noexcept { return m_program; }
        
        void Use() const noexcept;

        virtual void SetUniforms() {}
        virtual void BindAdditionals() {}

        void SetUniformFloat(const std::string &name, float value) const noexcept;
        void SetUniformInt(const std::string &name, int value) const noexcept;
        void SetUniformUnsigned(const std::string &name, unsigned value) const noexcept;
        void SetUniformVector2(const std::string &name, const Vector2 &value) const noexcept;
        void SetUniformVector3(const std::string &name, const Vector3 &value) const noexcept;
        void SetUniformVector4(const std::string &name, const Vector4 &value) const noexcept;
        void SetUniformMatrix4x4(const std::string &name, const Matrix4x4 &value) const noexcept;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;

    private:
        void Construct(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
        void Construct(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
                       const std::string &fragment_shader_path);

        void CopyFrom(const Shader &other);
        void MoveFrom(Shader &&other);
    };
}

#endif // MG3TR_SRC_GRAPHICS_SHADER_HPP_INCLUDED
