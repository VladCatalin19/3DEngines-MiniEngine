#ifndef MG3TR_SRC_GRAPHICS_SHADER_TEXTUREANDLIGHTINGSHADER_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SHADER_TEXTUREANDLIGHTINGSHADER_HPP_INCLUDED

#include <Components/Camera.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Texture.hpp>
#include <Scripting/Transform.hpp>
#include <Math/Vector3.hpp>

#include <memory>           // std::shared_ptr, std::weak_ptr

namespace MG3TR
{
    class TextureAndLightingShader : public Shader
    {
    private:
        std::weak_ptr<Camera> m_camera;
        std::weak_ptr<Transform> m_object_transform;
        std::shared_ptr<Texture> m_texture;
        Vector3 m_light_position;

        TUID m_camera_uid;
        TUID m_object_transform_uid;

    public:
        TextureAndLightingShader();

        TextureAndLightingShader(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                                 const std::shared_ptr<Texture> &texture, const Vector3 &light_position);
        virtual ~TextureAndLightingShader() noexcept = default;

        TextureAndLightingShader(const TextureAndLightingShader &) = default;
        TextureAndLightingShader& operator=(const TextureAndLightingShader &) = default;

        TextureAndLightingShader(TextureAndLightingShader &&) = default;
        TextureAndLightingShader& operator=(TextureAndLightingShader &&) = default;

        virtual void SetUniforms() override;
        virtual void BindAdditionals() override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_GRAPHICS_SHADER_TEXTUREANDLIGHTINGSHADER_HPP_INCLUDED
