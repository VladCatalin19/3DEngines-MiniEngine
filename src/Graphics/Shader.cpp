#include "Shader.hpp"

#include <Constants/JSONConstants.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

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
    
    nlohmann::json Shader::Serialize() const
    {
        namespace Constants = ShaderJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_vertex_shader_attribute] = m_vertex_shader_path;
        if (!m_geometry_shader_path.empty())
        {
            json[Constants::k_parent_node][Constants::k_geometry_shader_attribute] = m_geometry_shader_path;
        }
        json[Constants::k_parent_node][Constants::k_fragment_shader_attribute] = m_fragment_shader_path;
        return json;
    }
    
    void Shader::Deserialize(const nlohmann::json &json)
    {
        namespace Constants = ShaderJSONConstants;

        nlohmann::json shader_json = json.at(Constants::k_parent_node);

        std::string vertex_shader_path = shader_json.at(Constants::k_vertex_shader_attribute);
        std::string fragment_shader_path = shader_json.at(Constants::k_fragment_shader_attribute);

        if (shader_json.contains(Constants::k_geometry_shader_attribute))
        {
            std::string geometry_shader_path = shader_json[Constants::k_geometry_shader_attribute];
            Construct(vertex_shader_path, geometry_shader_path, fragment_shader_path);
        }
        else
        {
            Construct(vertex_shader_path, fragment_shader_path);
        }
    }
    
    void Shader::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
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
        m_vertex_shader = api.CreateShader(TShaderType::VertexShader, ReadFileInString(vertex_shader_path), vertex_shader_path);
        m_geometry_shader = 0;
        m_fragment_shader = api.CreateShader(TShaderType::FragmentShader, ReadFileInString(fragment_shader_path), fragment_shader_path);
        m_program = api.CreateShaderProgram(m_vertex_shader, m_fragment_shader);
    }
    
    void Shader::Construct(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
                           const std::string &fragment_shader_path)
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        m_vertex_shader_path = vertex_shader_path;
        m_geometry_shader_path = geometry_shader_path;
        m_fragment_shader_path = fragment_shader_path;
        m_vertex_shader = api.CreateShader(TShaderType::VertexShader, ReadFileInString(vertex_shader_path), vertex_shader_path);
        m_geometry_shader = api.CreateShader(TShaderType::GeometryShader, ReadFileInString(geometry_shader_path), geometry_shader_path);
        m_fragment_shader = api.CreateShader(TShaderType::FragmentShader, ReadFileInString(fragment_shader_path), fragment_shader_path);
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