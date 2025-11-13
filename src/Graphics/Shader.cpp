#include "Shader.hpp"
#include "Utils/ExceptionWithStacktrace.hpp"

#include <Constants/JSONConstants.hpp>

#include <glad/glad.h>

#include <Utils/ExceptionWithStacktrace.hpp>
#include <Utils/PrintGLErrors.hpp>

#include <fstream>
#include <iterator>
#include <vector>

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

static GLuint CreateShader(const GLenum shader_type, const std::string &shader_code,
                           const std::string &shader_path)
{
    GLuint shader = glCreateShader(shader_type);
    PRINT_GL_ERRORS_IF_ANY();

    const char *shader_code_pointer = shader_code.c_str();
    glShaderSource(shader, static_cast<GLsizei>(1), &shader_code_pointer, nullptr);
    PRINT_GL_ERRORS_IF_ANY();
    glCompileShader(shader);
    PRINT_GL_ERRORS_IF_ANY();

    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    PRINT_GL_ERRORS_IF_ANY();

    if (is_compiled == GL_FALSE)
    {
        GLint max_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
        PRINT_GL_ERRORS_IF_ANY();

        std::vector<GLchar> error_log(max_length);
        glGetShaderInfoLog(shader, max_length, &max_length, &error_log[0]);
        PRINT_GL_ERRORS_IF_ANY();

        glDeleteShader(shader);
        PRINT_GL_ERRORS_IF_ANY();
        throw MG3TR::ExceptionWithStacktrace("Could not compile \"" + shader_path + "\": " + &error_log[0]);
    }

    return shader;
}

static GLuint CreateShaderProgram(const GLuint vertex_shader, const GLuint geometry_shader, const GLuint fragment_shader)
{
    const GLuint program = glCreateProgram();
    PRINT_GL_ERRORS_IF_ANY();

    glAttachShader(program, vertex_shader);
    PRINT_GL_ERRORS_IF_ANY();

    if (geometry_shader != 0)
    {
        glAttachShader(program, geometry_shader);
        PRINT_GL_ERRORS_IF_ANY();
    }

    glAttachShader(program, fragment_shader);
    PRINT_GL_ERRORS_IF_ANY();

    glLinkProgram(program);
    PRINT_GL_ERRORS_IF_ANY();

    return program;
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
        if (m_vertex_shader > 0)
        {
            glDetachShader(m_program, m_vertex_shader);
            PRINT_GL_ERRORS_IF_ANY();

            glDeleteShader(m_vertex_shader);
            PRINT_GL_ERRORS_IF_ANY();
        }

        if (m_geometry_shader > 0)
        {
            glDetachShader(m_program, m_geometry_shader);
            PRINT_GL_ERRORS_IF_ANY();

            glDeleteShader(m_geometry_shader);
            PRINT_GL_ERRORS_IF_ANY();
        }

        if (m_fragment_shader > 0)
        {
            glDetachShader(m_program, m_fragment_shader);
            PRINT_GL_ERRORS_IF_ANY();

            glDeleteShader(m_fragment_shader);
            PRINT_GL_ERRORS_IF_ANY();

        }

        if (m_program > 0)
        {
            glDeleteProgram(m_program);
            PRINT_GL_ERRORS_IF_ANY();
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

    GLuint Shader::GetVertexShader() const
    {
        return m_vertex_shader;
    }

    GLuint Shader::GetGeometryShader() const
    {
        return m_geometry_shader;
    }

    GLuint Shader::GetFragmentShader() const
    {
        return m_fragment_shader;
    }

    GLuint Shader::GetProgram() const
    {
        return m_program;
    }
    
    void Shader::Use() const
    {
        glUseProgram(m_program);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void Shader::SetUniforms()
    {

    }

    void Shader::BindAdditionals()
    {

    }
    
    void Shader::SetUniformFloat(const std::string &name, const float value) const
    {
        const GLint location = glGetUniformLocation(m_program, name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform1f(location, value);
        PRINT_GL_ERRORS_IF_ANY();
    }
    
    void Shader::SetUniformInt(const std::string &name, const int value) const
    {
        const GLint location = glGetUniformLocation(m_program, name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform1i(location, value);
        PRINT_GL_ERRORS_IF_ANY();
    }
    
    void Shader::SetUniformUnsigned(const std::string &name, const unsigned value) const
    {
        const GLint location = glGetUniformLocation(m_program, name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform1ui(location, value);
        PRINT_GL_ERRORS_IF_ANY();
    }
    
    void Shader::SetUniformVector2(const std::string &name, const Vector2 &value) const
    {
        const GLint location = glGetUniformLocation(m_program, name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform2fv(location, value.Size(), value.InternalDataPointer());
        PRINT_GL_ERRORS_IF_ANY();
    }
    
    void Shader::SetUniformVector3(const std::string &name, const Vector3 &value) const
    {
        const GLint location = glGetUniformLocation(m_program, name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform3f(location, value.x(), value.y(), value.z());
        PRINT_GL_ERRORS_IF_ANY();
    }
    
    void Shader::SetUniformVector4(const std::string &name, const Vector4 &value) const
    {
        const GLint location = glGetUniformLocation(m_program, name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform4fv(location, value.Size(), value.InternalDataPointer());
        PRINT_GL_ERRORS_IF_ANY();
    }
    
    void Shader::SetUniformMatrix4x4(const std::string &name, const Matrix4x4 &value) const
    {
        const GLint location = glGetUniformLocation(m_program, name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniformMatrix4fv(location, 1, GL_FALSE, value.InternalDataPointer());
        PRINT_GL_ERRORS_IF_ANY();
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

        m_vertex_shader_path = vertex_shader_path;
        m_geometry_shader_path = "";
        m_fragment_shader_path = fragment_shader_path;
        m_vertex_shader = CreateShader(GL_VERTEX_SHADER, ReadFileInString(vertex_shader_path), vertex_shader_path);
        m_geometry_shader = 0;
        m_fragment_shader = CreateShader(GL_FRAGMENT_SHADER, ReadFileInString(fragment_shader_path), fragment_shader_path);
        m_program = CreateShaderProgram(m_vertex_shader, m_geometry_shader, m_fragment_shader);
    }
    
    void Shader::Construct(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
                           const std::string &fragment_shader_path)
    {
        m_vertex_shader_path = vertex_shader_path;
        m_geometry_shader_path = geometry_shader_path;
        m_fragment_shader_path = fragment_shader_path;
        m_vertex_shader = CreateShader(GL_VERTEX_SHADER, ReadFileInString(vertex_shader_path), vertex_shader_path);
        m_geometry_shader = CreateShader(GL_GEOMETRY_SHADER, ReadFileInString(geometry_shader_path), geometry_shader_path);
        m_fragment_shader = CreateShader(GL_FRAGMENT_SHADER, ReadFileInString(fragment_shader_path), fragment_shader_path);
        m_program = CreateShaderProgram(m_vertex_shader, m_geometry_shader, m_fragment_shader);
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