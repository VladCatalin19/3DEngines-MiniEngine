#include "TextureAndLightingShader.hpp"

#include <Constants/GraphicsConstants.hpp>
#include <Constants/JSONConstants.hpp>
#include <Scene/Scene.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <memory>           // std::make_shared

namespace MG3TR
{
    TextureAndLightingShader::TextureAndLightingShader()
        : Shader(ShaderConstants::k_texture_and_lighting_vertex_shader, 
                 ShaderConstants::k_texture_and_lighting_fragment_shader)
    {

    }

    TextureAndLightingShader::TextureAndLightingShader(const std::weak_ptr<Camera> &camera,
                                                       const std::weak_ptr<Transform> &object_transform,
                                                       const std::shared_ptr<Texture> &texture,
                                                       const Vector3 &light_position) try
        : Shader(ShaderConstants::k_texture_and_lighting_vertex_shader, 
                 ShaderConstants::k_texture_and_lighting_fragment_shader),
          m_camera(camera),
          m_object_transform(object_transform),
          m_texture(texture),
          m_light_position(light_position)
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
    
    void TextureAndLightingShader::SetUniforms() try
    {
        auto model = m_object_transform.lock()->GetWorldModelMatrix();
        auto view = m_camera.lock()->GetViewMatrix();
        auto projection = m_camera.lock()->GetProjectionMatrix();

        SetUniformMatrix4x4(ShaderConstants::k_model_uniform_location, model);
        SetUniformMatrix4x4(ShaderConstants::k_view_uniform_location, view);
        SetUniformMatrix4x4(ShaderConstants::k_projection_uniform_location, projection);

        SetUniformVector3(ShaderConstants::k_camera_position_uniform_location, m_camera.lock()->GetTransform().lock()->GetWorldPosition());
        SetUniformVector3(ShaderConstants::k_light_position_uniform_location, m_light_position);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TextureAndLightingShader::BindAdditionals() try
    {
        m_texture->Bind();
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json TextureAndLightingShader::Serialize() const try
    {
        namespace Constants = TextureAndLightingShaderJSONConstants;
        
        nlohmann::json json;

        json[Constants::k_parent_node][Constants::k_camera_uid_attribute] = m_camera.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_object_transform_uid_attribute] = m_object_transform.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_texture_path_attribute] = m_texture->GetPathToFile();
        json[Constants::k_parent_node][Constants::k_light_position_attribute] = {
            m_light_position.x(), m_light_position.y(), m_light_position.z()
        };

        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TextureAndLightingShader::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = TextureAndLightingShaderJSONConstants;
        
        nlohmann::json shader_json = json.at(Constants::k_parent_node);
        nlohmann::json light_position_json = shader_json.at(Constants::k_light_position_attribute);

        m_camera_uid = shader_json.at(Constants::k_camera_uid_attribute);
        m_object_transform_uid = shader_json.at(Constants::k_object_transform_uid_attribute);
        m_texture = std::make_shared<Texture>(shader_json.at(Constants::k_texture_path_attribute));

        m_light_position.x() = light_position_json.at(0);
        m_light_position.y() = light_position_json.at(1);
        m_light_position.z() = light_position_json.at(2);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TextureAndLightingShader::LateBindAfterDeserialization(Scene &scene) try
    {
        m_camera= scene.FindCameraWithUID(m_camera_uid);
        if (m_camera.lock() == nullptr)
        {
            throw std::logic_error("Could not find camera with UID " + std::to_string(m_camera_uid) + " in scene.");
        }

        m_object_transform = scene.FindTransformWithUID(m_object_transform_uid);
        if (m_object_transform.lock() == nullptr)
        {
            throw std::logic_error("Could not find object transform with UID " + std::to_string(m_camera_uid) + " in scene.");
        }
    }
    CATCH_RETHROW_EXCEPTIONS
}
