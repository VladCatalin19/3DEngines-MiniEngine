#ifndef MG3TR_SRC_GRAPHICS_SHADER_TEXTURESHADER_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SHADER_TEXTURESHADER_HPP_INCLUDED

#include <Graphics/Shader.hpp>
#include <Utils/TUID.hpp>

#include <memory>

namespace MG3TR
{
    class Camera;
    class Texture;
    class Transform;

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
        virtual ~TextureShader() = default;

        TextureShader(const TextureShader &) = default;
        TextureShader(TextureShader &&) = default;
        
        TextureShader& operator=(const TextureShader &) = default;
        TextureShader& operator=(TextureShader &&) = default;

        virtual void SetUniforms() override;
        virtual void BindAdditionals() override;

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;
        virtual void LateBind(Scene &scene) override;

    private:
        void Construct(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                       const std::shared_ptr<Texture> &texture);
    };
}

#endif // MG3TR_SRC_GRAPHICS_SHADER_TEXTURESHADER_HPP_INCLUDED
