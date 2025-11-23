#include "Shader.hpp"

#include <Constants/SerialisationConstants.hpp>
#include <Constants/ShaderConstants.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>
#include <Utils/ProjDirOperations.hpp>

#include <fstream>
#include <iterator>

static std::string ReadFileInString(const std::string &file_name)
{
    std::ifstream input_stream(file_name);

    if (input_stream.fail())
    {
        throw MG3TR::ExceptionWithStacktrace("Could not open \"" + file_name + "\".");
    }

    const std::string file_content(std::istreambuf_iterator<char>{input_stream}, {});
    return file_content;
}

namespace MG3TR
{
    Shader::Shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path)
    {
        Construct(vertex_shader_path, fragment_shader_path);
    }
    
    Shader::Shader(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
                   const std::string &fragment_shader_path)
    {
        Construct(vertex_shader_path, geometry_shader_path, fragment_shader_path);
    }
    
    Shader::~Shader()
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        if (m_vertex_shader > 0)
        {
            api.DeleteShader(m_program, m_vertex_shader);
        }

        if (m_geometry_shader > 0)
        {
            api.DeleteShader(m_program, m_geometry_shader);
        }

        if (m_fragment_shader > 0)
        {
            api.DeleteShader(m_program, m_fragment_shader);

        }

        if (m_program > 0)
        {
            api.DeleteShaderProgram(m_program);
        }
    }

    Shader::Shader(const Shader &other)
    {
        CopyFrom(other);
    }

    Shader::Shader(Shader &&other)
    {
        MoveFrom(std::move(other));
    }

    Shader& Shader::operator=(const Shader &other)
    {
        CopyFrom(other);
        return *this;
    }

    Shader& Shader::operator=(Shader &&other)
    {
        MoveFrom(std::move(other));
        return *this;
    }

    TShaderID Shader::GetVertexShader() const
    {
        return m_vertex_shader;
    }

    TShaderID Shader::GetGeometryShader() const
    {
        return m_geometry_shader;
    }

    TShaderID Shader::GetFragmentShader() const
    {
        return m_fragment_shader;
    }

    TShaderProgramID Shader::GetProgram() const
    {
        return m_program;
    }
    
    void Shader::Use() const
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();
        api.UseShader(m_program);
    }

    void Shader::SetUniforms()
    {

    }

    void Shader::BindAdditionals()
    {

    }

    void Shader::Serialise(ISerialiser &serialiser)
    {
        namespace Constants = ShaderSerialisationConstants;

        const ShaderType type = ShaderConstants::k_type_to_shader.at(typeid(*this));
        const std::string relative_vertex_shader_path = RemoveProjDirFromPath(m_vertex_shader_path);
        const std::string relative_fragment_shader_path = RemoveProjDirFromPath(m_fragment_shader_path);

        serialiser.SerialiseUnsigned(ShaderSerialisationConstants::k_type_attribute, static_cast<unsigned long long>(type));
        serialiser.SerialiseString(ShaderSerialisationConstants::k_type_name_attribute, Constants::k_type_name_value);

        serialiser.SerialiseString(Constants::k_vertex_shader_attribute, relative_vertex_shader_path);
        serialiser.SerialiseString(Constants::k_fragment_shader_attribute, relative_fragment_shader_path);

        const bool has_geometry_shader = !m_geometry_shader_path.empty();
        if (has_geometry_shader)
        {
            const std::string relative_geometry_shader_path = RemoveProjDirFromPath(m_geometry_shader_path);
            serialiser.SerialiseString(Constants::k_geometry_shader_attribute, relative_geometry_shader_path);
        }
    }

    void Shader::Deserialise(IDeserialiser &deserialiser)
    {
        namespace Constants = ShaderSerialisationConstants;

        const std::string relative_vertex_shader_path = deserialiser.DeserialiseString(Constants::k_vertex_shader_attribute);
        const std::string relative_fragment_shader_path = deserialiser.DeserialiseString(Constants::k_fragment_shader_attribute);

        const std::string vertex_shader_path = AddProjDirToPath(relative_vertex_shader_path);
        const std::string fragment_shader_path = AddProjDirToPath(relative_fragment_shader_path);

        const bool has_geometry_shader = deserialiser.ContainsField(Constants::k_geometry_shader_attribute);
        if (has_geometry_shader)
        {
            const std::string relative_geometry_shader_path = deserialiser.DeserialiseString(Constants::k_geometry_shader_attribute);
            const std::string geometry_shader_path = AddProjDirToPath(relative_geometry_shader_path);

            Construct(vertex_shader_path, geometry_shader_path, fragment_shader_path);
        }
        else
        {
            Construct(vertex_shader_path, fragment_shader_path);
        }
    }

    void Shader::LateBind([[maybe_unused]] Scene &scene)
    {

    }
    
    void Shader::Construct(const std::string &vertex_shader_path, const std::string &fragment_shader_path)
    {
        if (vertex_shader_path.empty() && fragment_shader_path.empty())
        {
            return;
        }

        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        m_vertex_shader_path = vertex_shader_path;
        m_geometry_shader_path = "";
        m_fragment_shader_path = fragment_shader_path;
        m_vertex_shader = api.CreateShader(GPUShaderType::VertexShader, ReadFileInString(vertex_shader_path), vertex_shader_path);
        m_geometry_shader = 0;
        m_fragment_shader = api.CreateShader(GPUShaderType::FragmentShader, ReadFileInString(fragment_shader_path), fragment_shader_path);
        m_program = api.CreateShaderProgram(m_vertex_shader, m_fragment_shader);
    }
    
    void Shader::Construct(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
                           const std::string &fragment_shader_path)
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        m_vertex_shader_path = vertex_shader_path;
        m_geometry_shader_path = geometry_shader_path;
        m_fragment_shader_path = fragment_shader_path;
        m_vertex_shader = api.CreateShader(GPUShaderType::VertexShader, ReadFileInString(vertex_shader_path), vertex_shader_path);
        m_geometry_shader = api.CreateShader(GPUShaderType::GeometryShader, ReadFileInString(geometry_shader_path), geometry_shader_path);
        m_fragment_shader = api.CreateShader(GPUShaderType::FragmentShader, ReadFileInString(fragment_shader_path), fragment_shader_path);
        m_program = api.CreateShaderProgram(m_vertex_shader, m_geometry_shader, m_fragment_shader);
    }

    void Shader::CopyFrom(const Shader &other)
    {
        Construct(other.m_vertex_shader_path, other.m_geometry_shader_path, other.m_fragment_shader_path);
    }

    void Shader::MoveFrom(Shader &&other)
    {
        m_vertex_shader = other.m_vertex_shader;
        m_geometry_shader = other.m_geometry_shader;
        m_fragment_shader = other.m_fragment_shader;
        m_program = other.m_program;

        m_vertex_shader_path = std::move(other.m_vertex_shader_path);
        m_geometry_shader_path = std::move(other.m_geometry_shader_path);
        m_fragment_shader_path = std::move(other.m_fragment_shader_path);

        other.m_vertex_shader = 0;
        other.m_geometry_shader = 0;
        other.m_fragment_shader = 0;
        other.m_program = 0;
    }
}