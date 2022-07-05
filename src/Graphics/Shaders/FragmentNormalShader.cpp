#include "FragmentNormalShader.hpp"

#include <Constants/GraphicsConstants.hpp>
#include <Constants/JSONConstants.hpp>
#include <Math/Matrix4x4.hpp>
#include <Scene/Scene.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

namespace MG3TR
{
    FragmentNormalShader::FragmentNormalShader()
        : Shader(MG3TR::ShaderConstants::k_fragment_normal_vertex_shader,
                 MG3TR::ShaderConstants::k_fragment_normal_fragment_shader)
    {

    }

    FragmentNormalShader::FragmentNormalShader(const std::weak_ptr<Camera> &camera,
                                               const std::weak_ptr<Transform> &object_transform) try
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
    CATCH_RETHROW_EXCEPTIONS

    void FragmentNormalShader::SetUniforms() try
    {
        auto model = m_object_transform.lock()->GetWorldModelMatrix();
        auto view = m_camera.lock()->GetViewMatrix();
        auto projection = m_camera.lock()->GetProjectionMatrix();

        SetUniformMatrix4x4(ShaderConstants::k_model_uniform_location, model);
        SetUniformMatrix4x4(ShaderConstants::k_view_uniform_location, view);
        SetUniformMatrix4x4(ShaderConstants::k_projection_uniform_location, projection);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json FragmentNormalShader::Serialize() const try
    {
        namespace Constants = FragmentNormalShaderJSONConstants;

        nlohmann::json json;

        json[Constants::k_parent_node][Constants::k_camera_uid_attribute] = m_camera.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_object_transform_uid_attribute] = m_object_transform.lock()->GetUID();

        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void FragmentNormalShader::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = FragmentNormalShaderJSONConstants;

        nlohmann::json shader_json = json.at(Constants::k_parent_node);

        m_camera_uid = shader_json.at(Constants::k_camera_uid_attribute);
        m_object_transform_uid = shader_json.at(Constants::k_object_transform_uid_attribute);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void FragmentNormalShader::LateBindAfterDeserialization(Scene &scene) try
    {
        m_camera = scene.FindCameraWithUID(m_camera_uid);
        if (m_camera.lock() == nullptr)
        {
            throw std::logic_error("Could not find camera with UID " + std::to_string(m_camera_uid) + " in scene.");
        }

        m_object_transform = scene.FindTransformWithUID(m_object_transform_uid);
        if (m_object_transform.lock() == nullptr)
        {
            throw std::logic_error("Could not find object transform with UID " + std::to_string(m_object_transform_uid) + " in scene.");
        }
    }
    CATCH_RETHROW_EXCEPTIONS
}
