#ifndef MG3TR_SRC_GRAPHICS_SHADERS_FRAGMENTNORMALSHADER_HPP_INCLUDED
#define MG3TR_SRC_GRAPHICS_SHADERS_FRAGMENTNORMALSHADER_HPP_INCLUDED

#include <Components/Camera.hpp>
#include <Graphics/Shader.hpp>
#include <Scripting/Transform.hpp>

#include <Constants/GraphicsConstants.hpp>

#include <memory>               // std::weak_ptr

namespace MG3TR
{
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
        virtual ~FragmentNormalShader() noexcept = default;

        FragmentNormalShader(const FragmentNormalShader &) = default;
        FragmentNormalShader& operator=(const FragmentNormalShader &) = default;

        FragmentNormalShader(FragmentNormalShader &&) = default;
        FragmentNormalShader& operator=(FragmentNormalShader &&) = default;

        virtual void SetUniforms() override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_GRAPHICS_SHADERS_FRAGMENTNORMALSHADER_HPP_INCLUDED
