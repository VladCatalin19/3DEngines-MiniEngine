#include "TextureAndLightingShader.hpp"

#include <Components/Camera.hpp>
#include <Constants/GraphicsConstants.hpp>
#include <Constants/SerialisationConstants.hpp>
#include <Constants/ShaderConstants.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Graphics/Texture.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/Transform.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>
#include <Utils/ProjDirOperations.hpp>

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

    void TextureAndLightingShader::Serialise(ISerialiser &serialiser)
    {
        Shader::Serialise(serialiser);

        namespace Constants = TextureAndLightingShaderSerialisationConstants;

        const ShaderType type = ShaderConstants::k_type_to_shader.at(typeid(*this));
        const TUID camera_uid = m_camera.lock()->GetUID();
        const TUID object_uid = m_object_transform.lock()->GetUID();
        const std::string &texture_path = m_texture->GetPathToFile();
        const std::string relative_texture_path = RemoveProjDirFromPath(texture_path);

        serialiser.SerialiseUnsigned(ShaderSerialisationConstants::k_type_attribute, static_cast<unsigned long long>(type));
        serialiser.SerialiseString(ShaderSerialisationConstants::k_type_name_attribute, Constants::k_type_name_value);

        serialiser.SerialiseUnsigned(Constants::k_camera_uid_attribute, camera_uid);
        serialiser.SerialiseUnsigned(Constants::k_object_transform_uid_attribute, object_uid);
        serialiser.SerialiseString(Constants::k_texture_path_attribute, relative_texture_path);
        serialiser.SerialiseVector3(Constants::k_light_position_attribute, m_light_position);
    }

    void TextureAndLightingShader::Deserialise(IDeserialiser &deserialiser)
    {
        Shader::Deserialise(deserialiser);

        namespace Constants = TextureAndLightingShaderSerialisationConstants;

        m_camera_uid = deserialiser.DeserialiseUnsigned(Constants::k_camera_uid_attribute);
        m_object_transform_uid = deserialiser.DeserialiseUnsigned(Constants::k_object_transform_uid_attribute);
        m_light_position = deserialiser.DeserialiseVector3(Constants::k_light_position_attribute);

        const std::string relative_texture_path = deserialiser.DeserialiseString(Constants::k_texture_path_attribute);
        const std::string texture_path = AddProjDirToPath(relative_texture_path);
        m_texture = std::make_shared<Texture>(texture_path);
    }

    void TextureAndLightingShader::LateBind(Scene &scene)
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
