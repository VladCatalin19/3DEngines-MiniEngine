#ifndef MG3TR_SRC_GRAPHICS_MATERIAL_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_MATERIAL_HPP_INCLUDED

#include <Graphics/Texture.hpp>

#include <memory>

namespace MG3TR
{
    struct Material
    {
        std::shared_ptr<Texture> m_diffuse_texture;

        Material(const std::shared_ptr<Texture> &diffuse_texture = nullptr)
            : m_diffuse_texture(diffuse_texture)
        {}
        ~Material() = default;

        Material(const Material &) = default;
        Material(Material &&) = default;
        
        Material& operator=(const Material &) = default;
        Material& operator=(Material &&) = default;
    };
}

#endif // MG3TR_SRC_GRAPHICS_MATERIAL_HPP_INCLUDED
