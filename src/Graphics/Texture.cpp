#include "Texture.hpp"

#include <Utils/ExceptionWithStacktrace.hpp>
#include <Utils/PrintGLErrors.hpp>

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <cstring>

static const GLint k_internal_formats[] = { 0, GL_R8, GL_RG8, GL_RGB8, GL_RGBA8 };
static const GLint k_pixel_format[] = { 0, GL_RED, GL_RG, GL_RGB, GL_RGBA };

static GLuint CreateTextureID(const int width, const int height, const int color_channels, const unsigned char *const image)
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

#   ifdef GL_EXT_texture_filter_anisotropic
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
        PRINT_GL_ERRORS_IF_ANY();
#   endif

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    PRINT_GL_ERRORS_IF_ANY();
    
    glTexImage2D(GL_TEXTURE_2D, 0, k_internal_formats[color_channels], width, height,
                 0, k_pixel_format[color_channels], GL_UNSIGNED_BYTE, image);
    PRINT_GL_ERRORS_IF_ANY();

    glGenerateMipmap(GL_TEXTURE_2D);
    PRINT_GL_ERRORS_IF_ANY();

    glBindTexture(GL_TEXTURE_2D, 0);
    PRINT_GL_ERRORS_IF_ANY();

    return id;
}

namespace MG3TR
{
    Texture::Texture(const std::string &path_to_file)
        : m_image(nullptr),
          m_id(0),
          m_path_to_file(path_to_file)
    {
        LoadImage(path_to_file);
    }
    
    Texture::~Texture()
    {
        FreeMemory();
    }
    
    Texture::Texture(const Texture &other)
    {
        CopyFrom(other);
    }

    Texture::Texture(Texture &&other)
    {
        MoveFrom(std::move(other));
    }

    Texture& Texture::operator=(const Texture &other)
    {
        CopyFrom(other);
        return *this;
    }

    Texture& Texture::operator=(Texture &&other)
    {
        MoveFrom(std::move(other));
        return *this;
    }

    void Texture::LoadImage(const std::string &path_to_file)
    {
        FreeMemory();

        m_image = stbi_load(path_to_file.c_str(), &m_width, &m_height, &m_color_channels, 0);
        if (m_image == nullptr)
        {
            throw ExceptionWithStacktrace("Could not read image at \"" + path_to_file + "\".");
        }

        m_id = CreateTextureID(m_width, m_height, m_color_channels, m_image);
    }
    
    void Texture::Bind(const unsigned texture_unit_id)
    {
        glActiveTexture(GL_TEXTURE0 + texture_unit_id);
        PRINT_GL_ERRORS_IF_ANY();

        glBindTexture(GL_TEXTURE_2D, m_id);
        PRINT_GL_ERRORS_IF_ANY();
    }

    const std::string& Texture::GetPathToFile() const
    {
        return m_path_to_file;
    }
    
    void Texture::FreeMemory()
    {
        stbi_image_free(m_image);

        if (m_id > 0)
        {
            glDeleteTextures(1, &m_id);
            PRINT_GL_ERRORS_IF_ANY();
        }

        m_image = nullptr;
        m_id = 0;
    }

    void Texture::CopyFrom(const Texture &other)
    {
        m_width = other.m_width;
        m_height = other.m_height;
        m_color_channels = other.m_color_channels;

        const std::size_t image_size = static_cast<unsigned>(m_width)
                                       * static_cast<unsigned>(m_height)
                                       * static_cast<unsigned>(m_color_channels);

        m_image = static_cast<unsigned char *>(stbi__malloc(image_size));

        (void)std::memcpy(m_image, other.m_image, image_size);

        m_id = CreateTextureID(m_width, m_height, m_color_channels, m_image);

        m_path_to_file = other.m_path_to_file;
    }

    void Texture::MoveFrom(Texture &&other)
    {
        m_width = other.m_width;
        m_height = other.m_height;
        m_color_channels = other.m_color_channels;
        m_image = other.m_image;
        m_id = other.m_id;
        m_path_to_file = std::move(other.m_path_to_file);

        other.m_width = 0;
        other.m_height = 0;
        other.m_color_channels = 0;
        other.m_image = nullptr;
        other.m_id = 0;
    }
}
