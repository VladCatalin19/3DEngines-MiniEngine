#include "TextureShader.hpp"

#include <Components/Camera.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Graphics/GraphicsConstants.hpp>
#include <Graphics/Shaders/ShaderConstants.hpp>
#include <Graphics/Texture.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/Transform.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>
#include <Serialisation/SerialisationConstants.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>
#include <Utils/ResourceManager.hpp>

namespace MG3TR
{
    TextureShader::TextureShader()
        : Shader()
    {
        auto& resource_manager = MG3TR::ResourceManager::GetInstance();

        const std::string vertex_shader_path = resource_manager.AddResourceDirectoryToPath(MG3TR::ShaderConstants::k_texture_vertex_shader);
        const std::string fragment_shader_path = resource_manager.AddResourceDirectoryToPath(MG3TR::ShaderConstants::k_texture_fragment_shader);

        Shader::Construct(vertex_shader_path, fragment_shader_path);
    }

    TextureShader::TextureShader(const std::weak_ptr<Camera> &camera, const std::weak_ptr<Transform> &object_transform,
                                 const std::shared_ptr<Texture> &texture)
        : Shader()
    {
        auto& resource_manager = MG3TR::ResourceManager::GetInstance();

        const std::string vertex_shader_path = resource_manager.AddResourceDirectoryToPath(MG3TR::ShaderConstants::k_texture_vertex_shader);
        const std::string fragment_shader_path = resource_manager.AddResourceDirectoryToPath(MG3TR::ShaderConstants::k_texture_fragment_shader);

        Shader::Construct(vertex_shader_path, fragment_shader_path);
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

    void TextureShader::Serialise(ISerialiser &serialiser)
    {
        Shader::Serialise(serialiser);

        namespace Constants = TextureShaderSerialisationConstants;

        auto& resource_manager = MG3TR::ResourceManager::GetInstance();
        const ShaderType type = ShaderConstants::k_type_to_shader.at(typeid(*this));
        const std::string &texture_path = m_texture->GetPathToFile();
        const std::string relative_texture_path = resource_manager.RemoveResourceDirectoryFromPath(texture_path);

        serialiser.SerialiseUnsigned(ShaderSerialisationConstants::k_type_attribute, static_cast<unsigned long long>(type));
        serialiser.SerialiseString(ShaderSerialisationConstants::k_type_name_attribute, Constants::k_type_name_value);

        serialiser.SerialiseUnsigned(Constants::k_camera_uid_attribute, m_camera_uid);
        serialiser.SerialiseUnsigned(Constants::k_object_transform_uid_attribute, m_object_transform_uid);
        serialiser.SerialiseString(Constants::k_texture_path_attribute, relative_texture_path);
    }

    void TextureShader::Deserialise(IDeserialiser &deserialiser)
    {
        Shader::Deserialise(deserialiser);

        namespace Constants = TextureShaderSerialisationConstants;

        auto& resource_manager = MG3TR::ResourceManager::GetInstance();
        m_camera_uid = deserialiser.DeserialiseUnsigned(Constants::k_camera_uid_attribute);
        m_object_transform_uid = deserialiser.DeserialiseUnsigned(Constants::k_object_transform_uid_attribute);

        const std::string relative_texture_path = deserialiser.DeserialiseString(Constants::k_texture_path_attribute);
        const std::string texture_path = resource_manager.AddResourceDirectoryToPath(relative_texture_path);
        m_texture = std::make_shared<Texture>(texture_path);
    }

    void TextureShader::LateBind(Scene &scene)
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
