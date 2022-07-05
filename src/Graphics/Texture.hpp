#ifndef MG3TR_SRC_GRAPHICS_TEXTURE_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_TEXTURE_HPP_INCLUDED

#include <glad/glad.h>          // GLuint

#include <string>               // std::string

namespace MG3TR
{
    class Texture
    {
    private:
        int m_width;
        int m_height;
        int m_color_channels;

        unsigned char *m_image;

        GLuint m_id;

        std::string m_path_to_file;

    public:
        Texture(const std::string &path_to_file);
        virtual ~Texture() noexcept;

        Texture(const Texture &);
        Texture& operator=(const Texture &);

        Texture(Texture &&) noexcept;
        Texture& operator=(Texture &&) noexcept;

        void LoadImage(const std::string &path_to_file);

        void Bind(unsigned texture_unit_id = 0U);

        const std::string& GetPathToFile() const noexcept { return m_path_to_file; }

    private:
        void FreeMemory() noexcept;
        void CopyFrom(const Texture &other);
        void MoveFrom(Texture &&other) noexcept;
    };
}

#endif // MG3TR_SRC_GRAPHICS_TEXTURE_HPP_INCLUDED
