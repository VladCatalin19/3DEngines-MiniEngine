#ifndef MG3TR_SRC_GRAPHICS_SHADER_TEXTUREANDLIGHTINGSHADER_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SHADER_TEXTUREANDLIGHTINGSHADER_HPP_INCLUDED

#include <Graphics/Shader.hpp>
#include <Utils/TUID.hpp>
#include <Math/Vector3.hpp>

#include <memory>

namespace MG3TR
{
    class Camera;
    class Transform;
    class Texture;

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
        virtual ~TextureAndLightingShader() = default;

        TextureAndLightingShader(const TextureAndLightingShader &) = default;
        TextureAndLightingShader(TextureAndLightingShader &&) = default;
        
        TextureAndLightingShader& operator=(const TextureAndLightingShader &) = default;
        TextureAndLightingShader& operator=(TextureAndLightingShader &&) = default;

        virtual void SetUniforms() override;
        virtual void BindAdditionals() override;

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;
        virtual void LateBind(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_GRAPHICS_SHADER_TEXTUREANDLIGHTINGSHADER_HPP_INCLUDED
