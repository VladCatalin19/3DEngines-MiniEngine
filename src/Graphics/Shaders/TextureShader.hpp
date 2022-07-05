#ifndef MG3TR_SRC_GRAPHICS_SHADER_TEXTURESHADER_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SHADER_TEXTURESHADER_HPP_INCLUDED

#include <Components/Camera.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Texture.hpp>
#include <Scripting/Transform.hpp>

#include <memory>           // std::shared_ptr, std::weak_ptr

namespace MG3TR
{
    class TextureShader : public Shader
    {
    private:
        std::weak_ptr<Camera> m_camera;
        std::weak_ptr<Transform> m_object_transform;
        std::shared_ptr<Texture> m_texture;

        TUID m_camera_uid;
        TUID m_object_transform_uid;

    public:
        TextureShader();

        TextureShader(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                      const std::shared_ptr<Texture> &texture);
        virtual ~TextureShader() noexcept = default;

        TextureShader(const TextureShader &) = default;
        TextureShader& operator=(const TextureShader &) = default;

        TextureShader(TextureShader &&) = default;
        TextureShader& operator=(TextureShader &&) = default;

        virtual void SetUniforms() override;
        virtual void BindAdditionals() override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;

    private:
        void Construct(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                       const std::shared_ptr<Texture> &texture);
    };
}

#endif // MG3TR_SRC_GRAPHICS_SHADER_TEXTURESHADER_HPP_INCLUDED
