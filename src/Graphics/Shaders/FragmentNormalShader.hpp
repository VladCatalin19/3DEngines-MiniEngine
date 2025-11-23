#ifndef MG3TR_SRC_GRAPHICS_SHADERS_FRAGMENTNORMALSHADER_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SHADERS_FRAGMENTNORMALSHADER_HPP_INCLUDED

#include <Graphics/Shader.hpp>
#include <Utils/TUID.hpp>

#include <memory>

namespace MG3TR
{
    class Camera;
    class Transform;

    class FragmentNormalShader : public Shader
    {
    private:
        std::weak_ptr<Camera> m_camera;
        std::weak_ptr<Transform> m_object_transform;

        TUID m_camera_uid;
        TUID m_object_transform_uid;

    public:
        FragmentNormalShader();
        FragmentNormalShader(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform);
        virtual ~FragmentNormalShader() = default;

        FragmentNormalShader(const FragmentNormalShader &) = default;
        FragmentNormalShader& operator=(const FragmentNormalShader &) = default;

        FragmentNormalShader(FragmentNormalShader &&) = default;
        FragmentNormalShader& operator=(FragmentNormalShader &&) = default;

        virtual void SetUniforms() override;

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;
        virtual void LateBind(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_GRAPHICS_SHADERS_FRAGMENTNORMALSHADER_HPP_INCLUDED
