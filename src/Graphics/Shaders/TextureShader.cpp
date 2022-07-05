#include "TextureShader.hpp"

#include <Constants/GraphicsConstants.hpp>
#include <Constants/JSONConstants.hpp>
#include <Graphics/Texture.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/GameObject.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <stdexcept>            // std::logic_error
#include <memory>               // std::make_shared

namespace MG3TR
{
    TextureShader::TextureShader() try
        : Shader(ShaderConstants::k_texture_vertex_shader, ShaderConstants::k_texture_fragment_shader)
    {

    }
    CATCH_RETHROW_EXCEPTIONS

    TextureShader::TextureShader(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                                 const std::shared_ptr<Texture> &texture) try
        : Shader(ShaderConstants::k_texture_vertex_shader, ShaderConstants::k_texture_fragment_shader)
    {
        Construct(camera, object_transform, texture);
    }
    CATCH_RETHROW_EXCEPTIONS

    void TextureShader::SetUniforms() try
    {
        auto model = m_object_transform.lock()->GetWorldModelMatrix();
        auto view = m_camera.lock()->GetViewMatrix();
        auto projection = m_camera.lock()->GetProjectionMatrix();

        SetUniformMatrix4x4(ShaderConstants::k_model_uniform_location, model);
        SetUniformMatrix4x4(ShaderConstants::k_view_uniform_location, view);
        SetUniformMatrix4x4(ShaderConstants::k_projection_uniform_location, projection);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TextureShader::BindAdditionals() try
    {
        m_texture->Bind();
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json TextureShader::Serialize() const try
    {
        namespace Constants = TextureShaderJSONConstants;

        nlohmann::json json;

        json[Constants::k_parent_node][Constants::k_camera_uid_attribute] = m_camera.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_object_transform_uid_attribute] = m_object_transform.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_texture_path_attribute] = m_texture->GetPathToFile();

        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TextureShader::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = TextureShaderJSONConstants;

        nlohmann::json texture_json = json.at(Constants::k_parent_node);

        m_camera_uid = texture_json.at(Constants::k_camera_uid_attribute);
        m_object_transform_uid = texture_json.at(Constants::k_object_transform_uid_attribute);
        m_texture = std::make_shared<Texture>(texture_json.at(Constants::k_texture_path_attribute));
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TextureShader::LateBindAfterDeserialization(Scene &scene) try
    {
        m_camera = scene.FindCameraWithUID(m_camera_uid);
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
    
    void TextureShader::Construct(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                                  const std::shared_ptr<Texture> &texture) try
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
    CATCH_RETHROW_EXCEPTIONS
}
