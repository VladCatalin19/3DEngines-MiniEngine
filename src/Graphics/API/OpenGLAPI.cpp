#include "OpenGLAPI.hpp"

#include <glad/glad.h>

#include <Graphics/SubMesh.hpp>
#include <Utils/PrintGLErrors.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

#include <vector>

static const GLint k_internal_formats[] = { 0, GL_R8, GL_RG8, GL_RGB8, GL_RGBA8 };
static const GLint k_pixel_format[] = { 0, GL_RED, GL_RG, GL_RGB, GL_RGBA };

namespace MG3TR
{
    void OpenGLAPI::Initialise(void *const load_process)
    {
    const GLenum ret = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(load_process));

    const bool GLAD_init_successfully = (ret != 0);
    if (!GLAD_init_successfully)
    {
        throw MG3TR::ExceptionWithStacktrace("Could not initialize GLAD.");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);  
    glCullFace(GL_BACK);
    }

    void OpenGLAPI::Finalise()
    {
        
    }

    void OpenGLAPI::SetDepthTest(const bool enable)
    {
        if (enable)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void OpenGLAPI::SetBackFaceCulling(const bool enable)
    {
        if (enable)
        {
            glEnable(GL_CULL_FACE);  
            glCullFace(GL_BACK);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }
    }

    void OpenGLAPI::ClearScreen()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        PRINT_GL_ERRORS_IF_ANY();
    }
        
    TTextureID OpenGLAPI::CreateTexture(const int image_width,
                                        const int image_height,
                                        const int color_channels,
                                        const unsigned char *const image)
    {
        GLuint id = 0;

        glGenTextures(1, &id);
        PRINT_GL_ERRORS_IF_ANY();

        glBindTexture(GL_TEXTURE_2D, id);
        PRINT_GL_ERRORS_IF_ANY();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        PRINT_GL_ERRORS_IF_ANY();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        PRINT_GL_ERRORS_IF_ANY();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        PRINT_GL_ERRORS_IF_ANY();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        PRINT_GL_ERRORS_IF_ANY();

#       ifdef GL_EXT_texture_filter_anisotropic
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
            PRINT_GL_ERRORS_IF_ANY();
#       endif

        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        PRINT_GL_ERRORS_IF_ANY();
        
        glTexImage2D(GL_TEXTURE_2D, 0, k_internal_formats[color_channels], image_width, image_height,
                     0, k_pixel_format[color_channels], GL_UNSIGNED_BYTE, image);
        PRINT_GL_ERRORS_IF_ANY();

        glGenerateMipmap(GL_TEXTURE_2D);
        PRINT_GL_ERRORS_IF_ANY();

        glBindTexture(GL_TEXTURE_2D, 0);
        PRINT_GL_ERRORS_IF_ANY();

        TTextureID texture_id = static_cast<TTextureID>(id);
        return texture_id;
    }
    
    void OpenGLAPI::DeleteTexture(const TTextureID texture_id)
    {
        glDeleteTextures(1, &texture_id);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::BindTexture(const TTextureID texture_id, const TTextureUnitID texture_unit_id)
    {
        glActiveTexture(GL_TEXTURE0 + texture_unit_id);
        PRINT_GL_ERRORS_IF_ANY();

        glBindTexture(GL_TEXTURE_2D, texture_id);
        PRINT_GL_ERRORS_IF_ANY();
    }

    TVAOID OpenGLAPI::CreateVAO()
    {
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        PRINT_GL_ERRORS_IF_ANY();

        glBindVertexArray(vao);
        PRINT_GL_ERRORS_IF_ANY();

        const TVAOID vao_id = static_cast<TVAOID>(vao);

        return vao_id;
    }

    TVBOID OpenGLAPI::CreateVBO(const void *const data,
                                const std::size_t memory_size,
                                const std::size_t vertex_size,
                                const unsigned location)
    {
        if (memory_size == 0)
        {
            return 0;
        }
        
        GLuint vbo = 0;

        glGenBuffers(1, &vbo);
        PRINT_GL_ERRORS_IF_ANY();

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        PRINT_GL_ERRORS_IF_ANY();

        glBufferData(GL_ARRAY_BUFFER, memory_size, data, GL_STATIC_DRAW);
        PRINT_GL_ERRORS_IF_ANY();

        glEnableVertexAttribArray(location);
        PRINT_GL_ERRORS_IF_ANY();

        glVertexAttribPointer(location, vertex_size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(0), nullptr);
        PRINT_GL_ERRORS_IF_ANY();

        glEnableVertexAttribArray(0);
        PRINT_GL_ERRORS_IF_ANY();

        const TVAOID vbo_id = static_cast<TVBOID>(vbo);

        return vbo_id;
    }

    TIBOID OpenGLAPI::CreateIBO(const void *const data,
                                const std::size_t memory_size)
    {
        if (memory_size == 0)
        {
            return 0;
        }
        
        GLuint ibo = 0;

        glGenBuffers(1, &ibo);
        PRINT_GL_ERRORS_IF_ANY();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        PRINT_GL_ERRORS_IF_ANY();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, memory_size, data, GL_STATIC_DRAW);
        PRINT_GL_ERRORS_IF_ANY();

        const TIBOID ibo_id = static_cast<TIBOID>(ibo);

        return ibo_id;
    }
    
    void OpenGLAPI::DeleteVAO(const TVAOID vao)
    {
        glDeleteVertexArrays(1, &vao);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::DeleteVBO(const TVBOID vbo)
    {
        glDeleteBuffers(1, &vbo);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::DeleteIBO(const TIBOID ibo)
    {
        glDeleteBuffers(1, &ibo);
        PRINT_GL_ERRORS_IF_ANY();
    }

    TShaderID OpenGLAPI::CreateShader(const TShaderType type, const std::string &code, const std::string &path)
    {
        int gl_shader_type = 0;

        switch (type)
        {
            case TShaderType::VertexShader:
            {
                gl_shader_type = GL_VERTEX_SHADER;
                break;
            }
            case TShaderType::GeometryShader:
            {
                gl_shader_type = GL_GEOMETRY_SHADER;
                break;
            }
            case TShaderType::FragmentShader:
            {
                gl_shader_type = GL_FRAGMENT_SHADER;
                break;
            }
        }

        GLuint shader = glCreateShader(gl_shader_type);
        PRINT_GL_ERRORS_IF_ANY();

        const char *shader_code_pointer = code.c_str();
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
            throw MG3TR::ExceptionWithStacktrace("Could not compile \"" + path + "\": " + &error_log[0]);
        }

        const TShaderID shader_id = static_cast<TShaderID>(shader);

        return shader_id;
    }

    TShaderProgramID OpenGLAPI::CreateShaderProgram(const TShaderID vertex_shader,
                                                    const TShaderID fragment_shader)
    {
        const GLuint program = glCreateProgram();
        PRINT_GL_ERRORS_IF_ANY();

        glAttachShader(program, vertex_shader);
        PRINT_GL_ERRORS_IF_ANY();

        glAttachShader(program, fragment_shader);
        PRINT_GL_ERRORS_IF_ANY();

        glLinkProgram(program);
        PRINT_GL_ERRORS_IF_ANY();

        const TShaderProgramID program_id = static_cast<TShaderProgramID>(program);

        return program_id;
    }

    TShaderProgramID OpenGLAPI::CreateShaderProgram(const TShaderID vertex_shader,
                                                    const TShaderID geometry_shader,
                                                    const TShaderID fragment_shader)
    {
        const GLuint program = glCreateProgram();
        PRINT_GL_ERRORS_IF_ANY();

        glAttachShader(program, vertex_shader);
        PRINT_GL_ERRORS_IF_ANY();

        glAttachShader(program, geometry_shader);
        PRINT_GL_ERRORS_IF_ANY();

        glAttachShader(program, fragment_shader);
        PRINT_GL_ERRORS_IF_ANY();

        glLinkProgram(program);
        PRINT_GL_ERRORS_IF_ANY();

        const TShaderProgramID program_id = static_cast<TShaderProgramID>(program);

        return program_id;
    }

    void OpenGLAPI::DeleteShader(const TShaderProgramID shader_program, const TShaderID shader)
    {
        glDetachShader(shader_program, shader);
        PRINT_GL_ERRORS_IF_ANY();

        glDeleteShader(shader);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::DeleteShaderProgram(const TShaderProgramID shader_program)
    {
        glDeleteProgram(shader_program);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::UseShader(const TShaderProgramID shader_program)
    {
        glUseProgram(shader_program);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::SetShaderUniformFloat(const TShaderProgramID shader_program,
                                          const std::string &uniform_name,
                                          const float uniform_value)
    {
        const GLint location = glGetUniformLocation(shader_program, uniform_name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform1f(location, uniform_value);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::SetShaderUniformInt(const TShaderProgramID shader_program,
                                        const std::string &uniform_name,
                                        const int uniform_value)
    {
        const GLint location = glGetUniformLocation(shader_program, uniform_name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform1i(location, uniform_value);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::SetShaderUniformUnsigned(const TShaderProgramID shader_program,
                                             const std::string &uniform_name,
                                             const unsigned uniform_value)
    {
        const GLint location = glGetUniformLocation(shader_program, uniform_name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform1ui(location, uniform_value);
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::SetShaderUniformVector2(const TShaderProgramID shader_program,
                                            const std::string &uniform_name,
                                            const Vector2 uniform_value)
    {
        const GLint location = glGetUniformLocation(shader_program, uniform_name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform2fv(location, uniform_value.Size(), uniform_value.InternalDataPointer());
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::SetShaderUniformVector3(const TShaderProgramID shader_program,
                                            const std::string &uniform_name,
                                            const Vector3 uniform_value)
    {
        const GLint location = glGetUniformLocation(shader_program, uniform_name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform3f(location, uniform_value.x(), uniform_value.y(), uniform_value.z());
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::SetShaderUniformVector4(const TShaderProgramID shader_program,
                                            const std::string &uniform_name,
                                            const Vector4 uniform_value)
    {
        const GLint location = glGetUniformLocation(shader_program, uniform_name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniform4fv(location, uniform_value.Size(), uniform_value.InternalDataPointer());
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::SetShaderUniformMatrix4x4(const TShaderProgramID shader_program,
                                              const std::string &uniform_name,
                                              const Matrix4x4 uniform_value)
    {
        const GLint location = glGetUniformLocation(shader_program, uniform_name.c_str());
        PRINT_GL_ERRORS_IF_ANY();

        glUniformMatrix4fv(location, 1, GL_FALSE, uniform_value.InternalDataPointer());
        PRINT_GL_ERRORS_IF_ANY();
    }

    void OpenGLAPI::DrawSubMesh(const SubMesh &submesh)
    {
        const TVAOID vao = submesh.GetVAO();
        const std::size_t indices_size = submesh.GetIndices().size();

        glBindVertexArray(vao);
        PRINT_GL_ERRORS_IF_ANY();

        glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, nullptr);
        PRINT_GL_ERRORS_IF_ANY();
    }
}