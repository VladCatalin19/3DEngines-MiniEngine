#include "Texture.hpp"

#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <cstring>

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

        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        m_id = api.CreateTexture(m_width, m_height, m_color_channels, m_image);
    }
    
    void Texture::Bind(const unsigned texture_unit_id)
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        api.BindTexture(m_id, texture_unit_id);
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
            auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

            api.DeleteTexture(m_id);
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

        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        m_id = api.CreateTexture(m_width, m_height, m_color_channels, m_image);

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
