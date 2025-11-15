#include "TextureAndLightingShader.hpp"

#include <Components/Camera.hpp>
#include <Constants/GraphicsConstants.hpp>
#include <Constants/JSONConstants.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Graphics/Texture.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/Transform.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

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
                                                       const Vector3 &light_position)
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
    
    void TextureAndLightingShader::SetUniforms()
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();
        const auto program = GetProgram();
        const auto model = m_object_transform.lock()->GetWorldModelMatrix();
        const auto view = m_camera.lock()->GetViewMatrix();
        const auto projection = m_camera.lock()->GetProjectionMatrix();
        const auto camera_world_position = m_camera.lock()->GetTransform().lock()->GetWorldPosition();

        api.SetShaderUniformMatrix4x4(program, ShaderConstants::k_model_uniform_location, model);
        api.SetShaderUniformMatrix4x4(program, ShaderConstants::k_view_uniform_location, view);
        api.SetShaderUniformMatrix4x4(program, ShaderConstants::k_projection_uniform_location, projection);

        api.SetShaderUniformVector3(program, ShaderConstants::k_camera_position_uniform_location, camera_world_position);
        api.SetShaderUniformVector3(program, ShaderConstants::k_light_position_uniform_location, m_light_position);
    }
    
    void TextureAndLightingShader::BindAdditionals()
    {
        m_texture->Bind();
    }
    
    nlohmann::json TextureAndLightingShader::Serialize() const
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
    
    void TextureAndLightingShader::Deserialize(const nlohmann::json &json)
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
    
    void TextureAndLightingShader::LateBindAfterDeserialization(Scene &scene)
    {
        m_camera = scene.FindCameraWithUID(m_camera_uid);
        if (m_camera.lock() == nullptr)
        {
            throw ExceptionWithStacktrace("Could not find camera with UID " + std::to_string(m_camera_uid) + " in scene.");
        }

        m_object_transform = scene.FindTransformWithUID(m_object_transform_uid);
        if (m_object_transform.lock() == nullptr)
        {
            throw ExceptionWithStacktrace("Could not find object transform with UID " + std::to_string(m_camera_uid) + " in scene.");
        }
    }
}
