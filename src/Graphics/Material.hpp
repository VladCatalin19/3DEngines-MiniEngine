#ifndef MG3TR_SRC_GRAPHICS_MATERIAL_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_MATERIAL_HPP_INCLUDED

#include <Constants/MathConstants.hpp>
#include <Graphics/Texture.hpp>
#include <Math/Vector4.hpp>

#include <memory>                   // std::shared_ptr

namespace MG3TR
{
    struct Material
    {
        std::shared_ptr<Texture> m_diffuse_texture;

        Material(const std::shared_ptr<Texture> &diffuse_texture = nullptr) noexcept
            : m_diffuse_texture(diffuse_texture)
        {}
        ~Material() noexcept = default;

        Material(const Material &) noexcept = default;
        Material& operator=(const Material &) noexcept = default;

        Material(Material &&) noexcept = default;
        Material& operator=(Material &&) noexcept = default;
    };
}

#endif // MG3TR_SRC_GRAPHICS_MATERIAL_HPP_INCLUDED
