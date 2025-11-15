#include "FragmentNormalShader.hpp"

#include <Components/Camera.hpp>
#include <Constants/GraphicsConstants.hpp>
#include <Constants/JSONConstants.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Math/Matrix4x4.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/Transform.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

namespace MG3TR
{
    FragmentNormalShader::FragmentNormalShader()
        : Shader(MG3TR::ShaderConstants::k_fragment_normal_vertex_shader,
                 MG3TR::ShaderConstants::k_fragment_normal_fragment_shader)
    {

    }

    FragmentNormalShader::FragmentNormalShader(const std::weak_ptr<Camera> &camera,
                                               const std::weak_ptr<Transform> &object_transform)
        : Shader(MG3TR::ShaderConstants::k_fragment_normal_vertex_shader,
                 MG3TR::ShaderConstants::k_fragment_normal_fragment_shader),
          m_camera(camera),
          m_object_transform(object_transform)
    {
        if (m_camera.lock() != nullptr)
        {
            m_camera_uid = camera.lock()->GetUID();
        }
        if (m_object_transform.lock() != nullptr)
        {
            m_object_transform_uid = object_transform.lock()->GetUID();
        }
    }

    void FragmentNormalShader::SetUniforms()
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();
        const auto program = GetProgram();
        const auto model = m_object_transform.lock()->GetWorldModelMatrix();
        const auto view = m_camera.lock()->GetViewMatrix();
        const auto projection = m_camera.lock()->GetProjectionMatrix();

        api.SetShaderUniformMatrix4x4(program, ShaderConstants::k_model_uniform_location, model);
        api.SetShaderUniformMatrix4x4(program, ShaderConstants::k_view_uniform_location, view);
        api.SetShaderUniformMatrix4x4(program, ShaderConstants::k_projection_uniform_location, projection);
    }
    
    nlohmann::json FragmentNormalShader::Serialize() const
    {
        namespace Constants = FragmentNormalShaderJSONConstants;

        nlohmann::json json;

        json[Constants::k_parent_node][Constants::k_camera_uid_attribute] = m_camera.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_object_transform_uid_attribute] = m_object_transform.lock()->GetUID();

        return json;
    }
    
    void FragmentNormalShader::Deserialize(const nlohmann::json &json)
    {
        namespace Constants = FragmentNormalShaderJSONConstants;

        nlohmann::json shader_json = json.at(Constants::k_parent_node);

        m_camera_uid = shader_json.at(Constants::k_camera_uid_attribute);
        m_object_transform_uid = shader_json.at(Constants::k_object_transform_uid_attribute);
    }
    
    void FragmentNormalShader::LateBindAfterDeserialization(Scene &scene)
    {
        m_camera = scene.FindCameraWithUID(m_camera_uid);
        if (m_camera.lock() == nullptr)
        {
            throw ExceptionWithStacktrace("Could not find camera with UID " + std::to_string(m_camera_uid) + " in scene.");
        }

        m_object_transform = scene.FindTransformWithUID(m_object_transform_uid);
        if (m_object_transform.lock() == nullptr)
        {
            throw ExceptionWithStacktrace("Could not find object transform with UID " + std::to_string(m_object_transform_uid) + " in scene.");
        }
    }
}
