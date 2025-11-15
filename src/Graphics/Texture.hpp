#ifndef MG3TR_SRC_GRAPHICS_TEXTURE_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_TEXTURE_HPP_INCLUDED

#include <Graphics/API/GraphicsTypes.hpp>

#include <string>

namespace MG3TR
{
    class Texture
    {
    private:
        int m_width;
        int m_height;
        int m_color_channels;

        unsigned char *m_image;

        TTextureID m_id;

        std::string m_path_to_file;

    public:
        Texture(const std::string &path_to_file);
        virtual ~Texture();

        Texture(const Texture &);
        Texture(Texture &&);
        
        Texture& operator=(const Texture &);
        Texture& operator=(Texture &&);

        void LoadImage(const std::string &path_to_file);

        void Bind(const unsigned texture_unit_id = 0U);

        const std::string& GetPathToFile() const;

    private:
        void FreeMemory();
        void CopyFrom(const Texture &other);
        void MoveFrom(Texture &&other);
    };
}

#endif // MG3TR_SRC_GRAPHICS_TEXTURE_HPP_INCLUDED
