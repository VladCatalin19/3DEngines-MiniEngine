#include "TextureShader.hpp"

#include <Constants/GraphicsConstants.hpp>
#include <Constants/JSONConstants.hpp>
#include <Components/Camera.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Graphics/Texture.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/Transform.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

namespace MG3TR
{
    TextureShader::TextureShader()
        : Shader(ShaderConstants::k_texture_vertex_shader, ShaderConstants::k_texture_fragment_shader)
    {

    }

    TextureShader::TextureShader(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                                 const std::shared_ptr<Texture> &texture)
        : Shader(ShaderConstants::k_texture_vertex_shader, ShaderConstants::k_texture_fragment_shader)
    {
        Construct(camera, object_transform, texture);
    }

    void TextureShader::SetUniforms()
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
    
    void TextureShader::BindAdditionals()
    {
        m_texture->Bind();
    }
    
    nlohmann::json TextureShader::Serialize() const
    {
        namespace Constants = TextureShaderJSONConstants;

        nlohmann::json json;

        json[Constants::k_parent_node][Constants::k_camera_uid_attribute] = m_camera.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_object_transform_uid_attribute] = m_object_transform.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_texture_path_attribute] = m_texture->GetPathToFile();

        return json;
    }
    
    void TextureShader::Deserialize(const nlohmann::json &json)
    {
        namespace Constants = TextureShaderJSONConstants;

        nlohmann::json texture_json = json.at(Constants::k_parent_node);

        m_camera_uid = texture_json.at(Constants::k_camera_uid_attribute);
        m_object_transform_uid = texture_json.at(Constants::k_object_transform_uid_attribute);
        m_texture = std::make_shared<Texture>(texture_json.at(Constants::k_texture_path_attribute));
    }
    
    void TextureShader::LateBindAfterDeserialization(Scene &scene)
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
    
    void TextureShader::Construct(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                                  const std::shared_ptr<Texture> &texture)
    {
        m_camera = camera;
        m_object_transform = object_transform;
        m_texture = texture;

        if (camera.lock() != nullptr)
        {
            m_camera_uid = camera.lock()->GetUID();
        }
        if (m_object_transform.lock() != nullptr)
        {
            m_object_transform_uid = m_object_transform.lock()->GetUID();
        }
    }
}
