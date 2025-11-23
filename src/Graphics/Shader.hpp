#ifndef MG3TR_SRC_GRAPHICS_SHADER_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SHADER_HPP_INCLUDED

#include <Graphics/API/GraphicsTypes.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Matrix4x4.hpp>
#include <Scene/ILateBindable.hpp>
#include <Serialisation/ISerialisable.hpp>

#include <string>

namespace MG3TR
{
    class Shader : public ISerialisable, public ILateBindable
    {
    private:
        TShaderID m_vertex_shader;
        TShaderID m_geometry_shader;
        TShaderID m_fragment_shader;

        TShaderProgramID m_program;

        std::string m_vertex_shader_path;
        std::string m_geometry_shader_path;
        std::string m_fragment_shader_path;

    public:
        Shader() = default;

        Shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
        Shader(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
               const std::string &fragment_shader_path);

        virtual ~Shader();

        Shader(const Shader &);
        Shader(Shader &&);
        
        Shader& operator=(const Shader &);
        Shader& operator=(Shader &&);

        TShaderID GetVertexShader() const;
        TShaderID GetGeometryShader() const;
        TShaderID GetFragmentShader() const;

        TShaderProgramID GetProgram() const;
        
        void Use() const;

        virtual void SetUniforms();
        virtual void BindAdditionals();

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;
        virtual void LateBind(Scene &scene) override;

    private:
        void Construct(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
        void Construct(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
                       const std::string &fragment_shader_path);

        void CopyFrom(const Shader &other);
        void MoveFrom(Shader &&other);
    };
}

#endif // MG3TR_SRC_GRAPHICS_SHADER_HPP_INCLUDED
